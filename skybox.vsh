attribute highp vec4 a_position;
attribute highp vec2 a_textcoord;
attribute highp vec3 a_normal;

uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;

varying highp vec2 v_texcoord;

void main(void){
    mat4 viewMatrix = u_viewMatrix;
    /* занулить информацию о сдвигах */
    viewMatrix[3][0] = 0.0;
    viewMatrix[3][1] = 0.0;
    viewMatrix[3][2] = 0.0;
    /* занулить информацию о сдвигах */
    mat4 mv_matrix = viewMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * mv_matrix * a_position;
    v_texcoord = a_textcoord;
}
