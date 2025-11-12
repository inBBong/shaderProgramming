#version 330
layout(location=0) out vec4 FragColor;
in vec2 v_UV;

uniform sampler2D u_RGBTexture;
uniform float u_Time; // 시간만 필요합니다.


const float c_PI = 3.141592;

void main()
{
    float s =0.01;
    vec2 newPos =v_UV;
    newPos +=vec2(0,v_UV.x*c_PI*2);
    vec4 newColor =texture(u_RGBTexture, newPos);
    //newColor+=texture(u_RGBTexture,vec2(v_UV.x,v_UV.y+sin(u_Time)));
    //newColor+=texture(u_RGBTexture,vec2(v_UV.x,v_UV.y+sin(u_Time)));
    //newColor+=texture(u_RGBTexture,vec2(v_UV.x,v_UV.y+sin(u_Time)));
    //newColor+=texture(u_RGBTexture,vec2(v_UV.x,v_UV.y+sin(u_Time)));
    //newColor/=5;
    FragColor=newColor;
    //FragColor = vec4(v_UV,0, 1.0);
}