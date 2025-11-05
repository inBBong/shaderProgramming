#version 330

in vec3 a_Position;
in float a_Value; //0~1
in vec4 a_Color;
in float a_STime;
in vec3 a_Vel;
in float a_LifeTime;
in float a_Mass;
in float a_Period;  

out vec4 v_Color;

uniform float u_Time;
uniform vec3 u_Force;

const float c_PI = 3.141592;
const vec2 c_G = vec2(0, -9.8); // 0923

void raining()
{
   float lifeTime = a_LifeTime;
   float newAlpha = 1.0;
   vec4 newPosition = vec4(a_Position, 1);
   float newTime = u_Time - a_STime;
    
   if(newTime > 0){
      float t = fract(newTime / lifeTime) * lifeTime;     // t: 0 ~ lifeTime
      float tt = t * t;

      float forceX = u_Force.x*2 + c_G.x*a_Mass;
      float forceY = u_Force.y*2 + c_G.y*a_Mass;

      float aX = forceX / a_Mass;
      float aY = forceY / a_Mass;

      float x = a_Vel.x * t + 0.5 * aX * tt;            
      float y = a_Vel.y * t + 0.5 * aY * tt; 

      newPosition.xy += vec2(x,y);   

      newAlpha = 1 - t/lifeTime;        // 1 ~ 0
   }
   else
   {
      newPosition.xy = vec2(-100000, 0);   
   }

   gl_Position = newPosition;
   
   vec4 newColor = a_Color;
   v_Color = vec4(a_Color.rgb, newAlpha);
}
void sinParticleAecong()
{
   vec4 centerColor = vec4(1, 0, 0, 1);
   vec4 borderColor = vec4(1, 1, 1, 1);
   vec4 newColor = a_Color;
   vec4 newPosition = vec4(a_Position, 1);
   float newAlpha = 1;

   float newTime = u_Time - a_STime;
   float lifeTime = a_LifeTime;
   float amp = a_Value * 2 - 1; // 폭
   amp*=0.5;
   float period = a_Period * 3;

   if(newTime > 0)
   {
      float t = fract(newTime/lifeTime) * lifeTime;
      float tt = t * t;
      float nTime = t/lifeTime; // 시간에 따른 스케일 값

      float x = nTime * 4 - 1; // -1~3
      float y = sin(c_PI*nTime) * amp * sin(period*c_PI*nTime*2);

      newPosition.xy += vec2(x,y);
      newAlpha = 1-t/lifeTime;

      float d = abs(y);
      newColor = mix(centerColor, borderColor, d * 2);
   }
   else
   {
      newPosition.xy += vec2(-100000, 0);
   }   

   gl_Position = newPosition;
   v_Color = vec4(newColor.rgb, newAlpha);
}
void sinParticle()
{
   vec4 newPosition = vec4(a_Position, 1);
   
   float newTime = u_Time - a_STime;
   float lifeTime = a_LifeTime;
   float t = fract(newTime/lifeTime) * lifeTime;
   float tt = t * t;

   vec4 centerC = vec4(1, 0, 0, 1);
   vec4 borderC = vec4(1, 1, 1, 0);
   vec4 newColor = a_Color;
   float newAlpha = 1.0;

   if(newTime > 0)
   {
      float period = a_Period * 3.0;

      float x = 2 * t - 1;
      float y = sin(2 * t * c_PI * period) * (a_Value - 0.5) * 2.0 * t;    //폭
      y *= sin(fract(newTime/lifeTime) * c_PI);

      newPosition.xy += vec2(x,y);

      newAlpha = 1.0 - t/lifeTime;

      // if (-0.05f < y && y < 0.05f) newColor.r = 255;        
      newColor = mix(centerC, borderC, abs(y * 4));
   }
   else
   {
      newPosition.xy = vec2(-100000, 0);   
   }

   gl_Position = newPosition;

   v_Color = vec4(newColor.rgb, newAlpha);
}

void circleParticle()
{
   vec4 newPosition = vec4(a_Position, 1);
   
   float newTime = u_Time - a_STime;
   float lifeTime = a_LifeTime;
   float t = fract(newTime/lifeTime) * lifeTime;
   float tt = t * t;
   
   vec4 newColor = a_Color;
   float newAlpha = 1.0;

   if(newTime > 0)
   {
      float x = cos(a_Value * 2 * c_PI); //
      float y = sin(a_Value * 2 * c_PI); //
      
      float newX = x + 0.5 * c_G.x * tt;
      float newY = y + 0.5 * c_G.y * tt;

      newPosition.xy += vec2(newX, newY);

      newAlpha = 1.0 - t/lifeTime;          // 1~0
   }
   else
   {
      newPosition.xy = vec2(-100000, 0);   
   }

   gl_Position = newPosition;

   v_Color = vec4(newColor.rgb, newAlpha);
}
void Q1()
{
vec4 newPosition = vec4(a_Position, 1);
float value = a_Value*c_PI*2;
float dx = 2*(a_Value-0.5);
float dy = 0.5*sin(a_Value-u_Time);
newPosition.xy+=vec2(dx,dy);
gl_Position =newPosition;
v_Color = vec4(a_Color.rgb,1);

}
void Q3() //나선환
{
vec4 newPosition = vec4(a_Position,1);

float value = a_Value * c_PI * 2;
float dx = a_Value*sin(value*4-u_Time);
float dy = a_Value*cos(value*4-u_Time);
newPosition.xy +=vec2(dx,dy);

gl_Position = newPosition;
v_Color = vec4(a_Color.rgb,1);

}
void main()
{
    //raining();
   //sinParticle();
   //sinParticleAecong();
  //circleParticle();
  Q3();
}