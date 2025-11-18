#version 330
layout(location=0) out vec4 FragColor;
in vec2 v_UV;

uniform sampler2D u_RGBTexture;
uniform float u_Time; // 시간만 필요합니다.


const float c_PI = 3.141592;

void Circle()
{
    vec2 newUV =v_UV;
    vec2 center = vec2(0.5,0.5);
    float d = distance(newUV,center);
    vec4 newColor = vec4(0);

    float value = sin(d*4*c_PI*8-u_Time);
    newColor = vec4(value);



    //for(int i=0;i<5;i++)
    //{
    //    if(d*10>i && d*10<i+1)
    //    newColor=vec4(1-i%2);
    //}
    
    FragColor =newColor;
}
void Flag()
{
    vec2 newUV = vec2(v_UV.x,(1-v_UV.y)-0.5);
    float sinValue = v_UV.x*0.2*(sin(v_UV.x*2*c_PI-u_Time*10));
    vec4 newColor = vec4(0);
    //float width =0.2 * abs(sin((1-v_UV.x)*1*c_PI)); //기교부리기
    float width =0.2 *(1-v_UV.x);

    if(sinValue + width > newUV.y &&sinValue -width < newUV.y)
    {
        newColor =vec4(1);
    }
    else
    {
        discard;
    }

    FragColor =newColor;
}

void Q1()
{
    float newX = v_UV.x;
    float newY = 1-abs((v_UV.y*2)-1);
    FragColor = texture(u_RGBTexture, vec2(newX,newY));
}
void Q2()
{
    float newX = fract(v_UV.x*3);
    float newY = (2-floor(v_UV.x*3))/3 + v_UV.y/3;
    FragColor = texture(u_RGBTexture, vec2(newX,newY));
}


void main()
{
   //Circle();
   //Flag();
   //Q1();
   Q2();
}