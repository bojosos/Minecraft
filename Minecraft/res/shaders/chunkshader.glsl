#type vertex

#version 330 core
layout(location = 0) in vec3 a_Coordinates;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_Transform;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = vec2(a_TexCoords.x, 16 - a_TexCoords.y) / 16.0;
	gl_Position =  u_ProjectionMatrix * u_ViewMatrix * u_Transform * vec4(a_Coordinates.xyz, 1.0);
}

#type fragment
#version 330 core

out vec4 color;
in  vec2 v_TexCoords;
uniform sampler2D u_Texture;

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

void main(void) {
	vec2 coord2d;
	float intensity = 1.0;
	
	color = texture(u_Texture, v_TexCoords);

}
