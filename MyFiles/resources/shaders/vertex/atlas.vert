#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;


out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 MVP;

uniform vec4 altas_coord;
//Remaps texture from (0,1) to (point1.x, point2.x) for x and y
vec2 RemapTex(vec2 inputTex, vec4 mapcoords){
    float x_coord = (mapcoords.z-mapcoords.x)*inputTex.x + mapcoords.x;
    float y_coord =(mapcoords.w-mapcoords.y)*inputTex.y + mapcoords.y;
    return vec2(x_coord,y_coord);
}

void main(){
    gl_Position =  MVP * vec4(aPos,1.0);
    TexCoord = RemapTex(aTexPos,altas_coord);
}