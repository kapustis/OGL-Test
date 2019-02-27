struct materialProperty {
    vec3 diffuseColor;
    vec3 ambienceColor;
    vec3 specularColor;
    float shinnes;
};
struct lightProperty{
    vec3 ambienceColor;
    vec3 diffuseColor;
    vec3 specularColor;
    vec4 position;
    vec4 direction;
    float cutoff;
    int type; //  Directional = 0,Point = 1, Spot = 2
};

uniform sampler2D   u_diffuseMap;
uniform sampler2D   u_normalMap;
uniform sampler2D   u_shadowMap;

uniform highp float u_lightPower;
uniform highp float u_sizeShadow;
uniform materialProperty u_materialProperty;
uniform bool u_isUsingDiffuseMap;
uniform bool u_isUsingNormalMap;
uniform highp vec4 u_lightDirection;
uniform lightProperty u_lightProperty[3];
uniform int u_countLights;
uniform int u_indexLightForShadow;

varying highp vec4  v_position;
varying highp vec2  v_texcoord;
varying highp vec3  v_normal;
varying highp mat3  v_tbnMatrix;

varying highp vec4 v_positionLightMatrix;
varying highp mat4 v_viewMatrix;

lightProperty v_lightProperty[3];

float SapleShadowMap(sampler2D map, vec2 coords, float compare){
    vec4 v = texture2D(map,coords);
    float value = v.x *255.0 + (v.y * 255.0 + (v.z * 255.0 + v.w)/255.0)/255.0;
    return step(compare, value);
}
//линейная фильтрация
float SampleShadowMapLinear(sampler2D map, vec2 coords, float compare, vec2 texelSize){
    vec2 pixelPos = coords / texelSize + 0.5;
    vec2 fractPart = fract(pixelPos);
    vec2 startTexel = (pixelPos - fractPart) * texelSize;

    float blTexel = SapleShadowMap(map ,startTexel,compare); //bottom left
    float brTexel = SapleShadowMap(map ,startTexel + vec2(texelSize.x,0.0),compare); //bottom right
    float tlTexel = SapleShadowMap(map ,startTexel + vec2(0.0,texelSize.y),compare); //top left
    float trTexel = SapleShadowMap(map ,startTexel + texelSize.y,compare); //top right

    float mixA = mix(blTexel,tlTexel,fractPart.y);
    float mixB = mix(brTexel,trTexel,fractPart.y);

    return mix(mixA,mixB,fractPart.x);
}
// фильтрация облака точек
float SampleShadowMapPCF(sampler2D map, vec2 coords, float compare, vec2 texelSize){
    float result = 0.0;

    for (float y = -1.0;y < 1.0;y += 1.0)
        for (float x = -1.0;x < 1.0;x += 1.0){
            vec2 offset  = vec2(x,y) * texelSize;
            result += SampleShadowMapLinear(map,coords+offset,compare,texelSize);
        }

    return result /9.0;
}

float CalcShadowAmount(sampler2D map,vec4 initShadowCoords){
    vec3 tmp = v_positionLightMatrix.xyz / v_positionLightMatrix.w;
    tmp = tmp * vec3(0.5) + vec3(0.5);
    float offset = 2.0;
    offset *= dot(v_normal,v_lightProperty[u_indexLightForShadow].direction.xyz);

    return SampleShadowMapPCF(u_shadowMap, tmp.xy, tmp.z * 255.0 + offset,vec2(1.0/u_sizeShadow));
}



void main(void){
    for(int i = 0; i < u_countLights; ++i){
        v_lightProperty[i].ambienceColor   = u_lightProperty[i].ambienceColor;
        v_lightProperty[i].diffuseColor    = u_lightProperty[i].diffuseColor;
        v_lightProperty[i].specularColor   = u_lightProperty[i].specularColor;
        v_lightProperty[i].cutoff          = u_lightProperty[i].cutoff;
        v_lightProperty[i].type            = u_lightProperty[i].type;
        v_lightProperty[i].direction       = v_viewMatrix * u_lightProperty[i].direction;
        v_lightProperty[i].position        = v_viewMatrix * u_lightProperty[i].position;
    }


    highp float shadowCoefficient;
    if(v_lightProperty[u_indexLightForShadow].type == 0)
        shadowCoefficient = CalcShadowAmount(u_shadowMap, v_positionLightMatrix);
    else shadowCoefficient = 1.0;

    vec4 resultColor     = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition     = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffMatColor    = texture2D(u_diffuseMap, v_texcoord);

    vec3 usingNormal     = v_normal;
    if(u_isUsingNormalMap) usingNormal = normalize(texture2D(u_normalMap,v_texcoord).rgb * 2.0 - 1.0);

    vec3 eyeVect         = normalize(v_position.xyz - eyePosition.xyz);
    if(u_isUsingNormalMap) eyeVect = normalize(v_tbnMatrix * eyeVect);
    for(int i = 0; i < u_countLights; ++i){
        vec4 resultLightColor = vec4(0.0f,0.0f,0.0f,0.0f);
        vec3 lightVect;
        if(v_lightProperty[i].type == 0) {
            lightVect = normalize(v_lightProperty[i].direction.xyz);
        }else{
            lightVect = normalize(v_position.xyz - v_lightProperty[i].position.xyz);
            if(v_lightProperty[i].type == 2){
                float trr =  dot(v_lightProperty[i].direction.xyz, lightVect);
                float angle = acos(trr);
                if(angle > v_lightProperty[i].cutoff) lightVect = vec3(0.0f,0.0f,0.0f);
            }
        }

        if(u_isUsingNormalMap) lightVect = normalize(v_tbnMatrix * lightVect);

        vec3 reflectLight    = normalize(reflect(lightVect, usingNormal));

        float specularFactor = u_materialProperty.shinnes;
        float ambientFactor  = 0.1f;

        if(u_isUsingDiffuseMap == false) diffMatColor = vec4(u_materialProperty.diffuseColor,1.0f);
        vec4 diffColor = diffMatColor * u_lightPower * max(0.0f,dot(usingNormal, -lightVect));
        resultLightColor += diffColor * vec4(v_lightProperty[i].diffuseColor,1.0f);

        vec4 ambientColor = ambientFactor * diffMatColor;
        resultLightColor += ambientColor * vec4(u_materialProperty.ambienceColor,1.0f) * vec4(v_lightProperty[i].ambienceColor ,1.0f);

        vec4 specularColor = vec4(1.0f,1.0f,1.0f,1.0f) * u_lightPower  * pow(max(0.0f,dot(reflectLight, -eyeVect)),specularFactor);
        resultLightColor += specularColor * vec4(u_materialProperty.specularColor,1.0f) * vec4(v_lightProperty[i].specularColor ,1.0f);
        resultColor += resultLightColor;
    }
    shadowCoefficient += 0.1f;
    if(shadowCoefficient > 1.0f) shadowCoefficient = 1.0f;
    gl_FragColor = resultColor * shadowCoefficient;
}
