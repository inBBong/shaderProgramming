#version 330

in vec3 a_Position;
in vec4 a_Color;


out vec4 v_Color;
uniform float u_Time; 
//-0.5~0.5
//0~2PI
const float c_PI = 3.141592;
void Flag()
{
    vec4 newPosition = vec4(a_Position, 1);
    float value = (a_Position.x + 0.5) * 2 * c_PI;
    float dx = 0;
    float dy = 0.1 * sin(value + u_Time) * value / c_PI;
    float tri = (-1 * a_Position.x) + 0.5; //1~0
    newPosition.xy *= vec2(1, tri);
    newPosition.xy += vec2(dx, dy);

    gl_Position = newPosition;
    
	//v_Color = a_Color;
    if (distance(newPosition, vec4(0, 0, 0, 1)) < 0.1)
        v_Color = vec4(1, 1, 0, 1);
    else
        v_Color = vec4(1 + dy * 5);
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

void main()
{	
    //Flag();
    Wave();

}
