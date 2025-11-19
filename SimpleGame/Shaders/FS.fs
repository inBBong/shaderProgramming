#version 330
layout(location=0) out vec4 FragColor;
in vec2 v_UV;

uniform sampler2D u_RGBTexture;
uniform sampler2D u_NumTexture;
uniform sampler2D u_TotalNumTexture;
uniform int u_Number;
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
void Q3()
{
    float newX = fract(v_UV.x*3);
    float newY = floor(v_UV.x*3)/3 + v_UV.y/3;
    FragColor = texture(u_RGBTexture, vec2(newX,newY));
}
void Q4()
{
    float count =40;//uniform
    float shift =1-0.1*u_Time;//uniform
    float newX = fract(fract(v_UV.x*count)+(floor(v_UV.y*count)+1)*shift);
    float newY = fract(v_UV.y*count);
    FragColor = texture(u_RGBTexture, vec2(newX,newY));
}
void Q5()
{
    float count =2;//uniform
    float shift =0.5;//uniform
    float newX = fract(v_UV.x*count);
    float newY = fract(fract(v_UV.y*count)+(floor(v_UV.x*count)+1)*shift);
    FragColor = texture(u_RGBTexture, vec2(newX,newY));
}
void Number()
{
    FragColor= texture(u_NumTexture, v_UV);
}
void TotalNumber()
{
    float newX;
    float newY;
    int num=(u_Number+9)%10;
    float Xoffset=num%5;
    float Yoffset=num/5;
    newX=(v_UV.x+Xoffset)/5;
    newY=(v_UV.y+Yoffset)/2;

    FragColor= texture(u_TotalNumTexture, vec2(newX,newY));
}
void Number1000()
{
    int num1000=u_Number/1000;
    int num100=(u_Number/100)%10;
    int num10=(u_Number/10)%10;
    int num1=u_Number%10;
    
    float newX;
    float newY;
    //if(v_UV.x<1/5)
    //int num=(num1000+9)%10;
    //else if(v_UV.x<2/5)
    //int num=(num100+9)%10;
    //else if(v_UV.x<3/5)
    //int num=(num10+9)%10;
    //else if(v_UV.x<4/5)
    int num=(num1+9)%10;

    
    float Xoffset=num % 5;
    float Yoffset=num / 5;

    newX=(v_UV.x+Xoffset);
    newY=(v_UV.y+Yoffset)/2;

    FragColor= texture(u_TotalNumTexture, vec2(newX,newY));
}
void main()
{
   //Circle();
   //Flag();
   //Q1();
   //Q2();
   //Q3();
   //Q4();
   //Q5();
   //Number();
   TotalNumber();
   //Number1000();
}