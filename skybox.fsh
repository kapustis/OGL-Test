uniform sampler2D u_texture;
varying highp vec2 v_texcoord;

void main(void){
    gl_FragColor = texture2D(u_texture, v_texcoord);
}
