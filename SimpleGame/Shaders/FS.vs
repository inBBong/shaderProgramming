#version 330

in vec3 a_Position;
in vec2 a_TexPos;

// a_Position : -1~1
// --> 좌상단 : 0, 0 , 우하단 : 1, 1
// u : (a_Position.x+1)/2
// v : (1-a_Position.y)/2

out vec2 v_UV;

void main()
{
   vec4 newPosition = vec4(a_Position, 1);
   gl_Position = newPosition;

   //v_UV.x = (a_Position.x+1)/2;
   //v_UV.y = (1-a_Position.y)/2;

   v_UV = a_TexPos;
}