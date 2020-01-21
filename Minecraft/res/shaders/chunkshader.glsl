#type vertex

#version 330 core
layout(location = 0) in vec4 a_Coordinates;

uniform mat4 u_Transform;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec4 v_TextureCoordinates;

void main()
{
	v_TextureCoordinates = a_Coordinates;
	gl_Position =  u_ProjectionMatrix * u_ViewMatrix * u_Transform * vec4(a_Coordinates.xyz, 1.0);
}

#type fragment
#version 330 core

out vec4 color;
in  vec4 v_TextureCoordinates;
uniform sampler2D u_Texture;

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

void main(void) {
	vec2 coord2d;
	float intensity;
	float x = mod(v_TextureCoordinates.w, 16);
	float y = 16 - (int(v_TextureCoordinates.w) / 16);

	color = texture(u_Texture, vec2((fract(v_TextureCoordinates.x) + x) / 16.0, (-fract(v_TextureCoordinates.y) + y) / 16.0));

	intensity = 0.85;
}
