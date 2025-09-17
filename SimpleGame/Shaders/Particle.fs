#version 330


layout(location=0) out vec4 FragColor;

in vec4 v_Color;

uniform vec4 u_Color;
uniform float u_Time;
void main()
{
	//FragColor = vec4(u_Color.r, u_Color.g, u_Color.b, u_Color.a);
	FragColor = v_Color;
	//if(FragColor.r>0.5||FragColor.b>0.5) discard;
}
