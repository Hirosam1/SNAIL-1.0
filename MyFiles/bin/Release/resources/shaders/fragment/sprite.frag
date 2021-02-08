#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D Texture1;

void main(){
    FragColor = vec4(texture(Texture1,TexCoord));
    if(FragColor.a < 0.1){
        discard;
    }
}