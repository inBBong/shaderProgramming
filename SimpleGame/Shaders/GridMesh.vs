#version 330
#define MAX_POINTS 500
in vec3 a_Position;
in vec4 a_Color;
out vec2 v_UV;

out vec4 v_Color;
uniform float u_Time; 
//-0.5~0.5
//0~2PI
uniform vec4 u_Points[MAX_POINTS];
uniform int u_DropCount;

const float c_PI = 3.141592;
/*const vec4 c_Points[3] = vec4[](vec4(0,0,2,2),
                                vec4(0.5 ,0 ,3 ,3),
                                vec4(-0.5 ,0 ,4 ,4));*/


void Flag()
{        //a_Position  -> -0.5~0.5  a_Position  ->  -1~1
    vec4 newPosition = vec4(a_Position*0.5, 1);
    float value = (a_Position.x*0.5 + 0.5) * 2 * c_PI; // 0~2PI
    float dx = 0;
    float dy = 0.1 * sin(value + u_Time) * value / c_PI;
    float tri = (-1 * a_Position.x*0.5) + 0.5; //1~0
    newPosition.xy *= vec2(1, tri);
    newPosition.xy += vec2(dx, dy);

    gl_Position = newPosition;
    
	//v_Color = a_Color;
    if (distance(newPosition, vec4(0, 0, 0, 1)) < 0.1)
        v_Color = vec4(1, 1, 0, 1);
    else
        v_Color = vec4(1 + dy * 5);


        v_UV = vec2(a_Position.x*0.5+0.5,0.5 -a_Position.y*0.5);
}
void Wave()
{
    vec4 newPosition = vec4(a_Position, 1);    
    gl_Position = newPosition;    	
    float d = distance(a_Position.xy, vec2(0, 0));
    
    //if(d<0.5)
    //{
    //    v_Color = vec4(1);        
    //}
    //else
    //{
    //    v_Color = vec4(0);
    //}    
    //float value = clamp(0.5 - d, 0, 1);
    //value = ceil(value);
    //value = (0.5 - d) * 100;
    float value = sin(10 * d * 4 * c_PI- 5*u_Time);
    float p = 1 - clamp(d * 2, 0, 1);
    v_Color = vec4(vec3(value), p);
    
   
    
    //v_Color = vec4(ceil(clamp(0.5-d, 0, 1)));

}

void RainDrop()
{
  vec4 newPosition = vec4(a_Position, 1);
    gl_Position = newPosition;

   vec2 pos = a_Position.xy;
   float newColor =0;
   for(int i=0;i<u_DropCount;i++)
   {
        vec2 cen = u_Points[i].xy;   
        float sTime = u_Points[i].z;
        float lTime =u_Points[i].w;
        float newTime =u_Time-sTime;
        if(newTime>0)
        {
            float baseTime =fract(newTime/lTime);
            float oneMinus =1-baseTime;
            float t=baseTime*lTime;
            float range =baseTime*lTime/10;
            float d = distance(pos,cen);
            float value = sin(10 * d * 4 * c_PI- t*10);//상수의 의미 잘 알아두기
            float p = 30*clamp(range-d, 0, 1);

            newColor +=value*p*oneMinus;
        }
   }
    v_Color = vec4(newColor);
    
   
    
    //v_Color = vec4(ceil(clamp(0.5-d, 0, 1)));

}
void Q4()
{
 vec4 newPosition = vec4(a_Position*0.5, 1);
    float value = 2*(newPosition.y+0.5)*c_PI; // 0~2PI
    float greyScale =sin(value*8);
    gl_Position = newPosition;
    v_Color=vec4(greyScale);
	
}
void Q5()
{

 vec4 newPosition = vec4(a_Position*0.5, 1);
    float valueX = 2*(newPosition.x+0.5)*c_PI; // 0~2PI
    float valueY = 2*(newPosition.y+0.5)*c_PI; // 0~2PI
    //float greyScale =sin(valueX*8);
    float greyScale =ceil(sin(valueY*8+u_Time));
    //greyScale *=sin(valueY*8);
    gl_Position = newPosition;
    v_Color=vec4(greyScale);
 
}
void main()
{	
    Flag();
    //Wave();
    //RainDrop();
    //Q5();

}
