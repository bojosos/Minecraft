#type vertex

#version 330 core
layout(location = 0) in vec3 a_Coordinates;
layout(location = 1) in vec2 a_TexCoords;
layout(location = 2) in float a_Tid;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec2 v_TexCoords;
out float v_Tid;

void main()
{
	v_Tid = a_Tid;
	v_TexCoords = vec2(a_TexCoords.x, 16 - a_TexCoords.y) / 16.0;
	gl_Position =  u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Coordinates.xyz, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoords;
in float v_Tid;

uniform sampler2D[8] u_Textures;

void main(void) {
	vec2 coord2d;
	float intensity = 1.0;
	int tid = int(v_Tid);
	color = texture(u_Textures[tid], v_TexCoords);
}
