#type vertex

#version 330 core
layout(location = 0) in vec3 a_Coords;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_Position;

void main()
{
	gl_Position =  u_ProjectionMatrix * u_ViewMatrix * u_Position * vec4(a_Coords.xyz, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

void main(void) {
	color = vec4(0.8, 0.2, 0.5, 1.0);
}
