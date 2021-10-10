#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;
layout (location = 2) in vec4 atlas_coord


out vec2 TexCoord;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

uniform mat4 MVP;

//Remaps texture from (0,1) to the normalized texture segment from texture atlas
//It takes as arguments the 2 Vec2 coordinates of the texture, bottom left and upper right coordinates,
// and the vertex tex position, that ranges from 0-1 indicating where the texture starts and ends.
//This function is usefull, because you can use the default square coordinates, and only changing the 
// atlas_coord uniform to get another texture position.
// If xm is the remapped texture (varying between a and b) and xa the aTexPos (varying between 0 and 1) then you can remap xa -> xm:
// xm = (b - a)/(1-0)* xa + β
// subistitute xm to b, we know xa should be 1: b = (b-a)*1 + β
//β = a
//therefore:
// xm = (b-a)*xa + β
// with this function we can get any value between a-b using the aTexPos values 0-1
vec2 RemapTex(vec2 inputTex, vec4 mapcoords){
    float x_coord = (mapcoords.z-mapcoords.x)*inputTex.x + mapcoords.x;
    float y_coord =(mapcoords.w-mapcoords.y)*inputTex.y + mapcoords.y;
    return vec2(x_coord,y_coord);
}

void main(){
    gl_Position =  MVP * vec4(aPos,1.0);
    TexCoord = RemapTex(aTexPos,altas_coord);
}