#version 330
layout(location=0) out vec4 FragColor;
in vec2 v_UV;

uniform float u_Time; // 시간만 필요합니다.

const float c_PI = 3.141592;

void main()
{
    FragColor = vec4(v_UV,0, 1);
}