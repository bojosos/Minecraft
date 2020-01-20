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

in vec4 v_TextureCoordinates;
uniform sampler2D texture;

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

void main(void) {
	vec2 coord2d;
	float intensity;

	if(v_TextureCoordinates.w < 0.0) {
		coord2d = vec2(v_TextureCoordinates.w / 16.0, 1.0/16.0);
		intensity = 1.0;
	} else {
		coord2d = vec2(v_TextureCoordinates.w / 16.0, 1.0/16.0);
		intensity = 0.85;
	}
	
	vec4 color = texture2D(texture, coord2d);

	if(color.a < 0.4)
		discard;
	color.xyz *= intensity;

	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fog = clamp(exp(-fogdensity * z * z), 0.2, 1.0);

	gl_FragColor = mix(fogcolor, color, fog);
}
