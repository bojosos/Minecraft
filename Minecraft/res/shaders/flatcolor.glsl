#type vertex

#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoordinates;

uniform mat4 u_Transform;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec2 v_TextureCoordinates;
out vec4 v_Color;

void main()
{
	v_Color = a_Color;
	v_TextureCoordinates = a_TextureCoordinates;
	gl_Position =  u_ProjectionMatrix * u_ViewMatrix * u_Transform * vec4(a_Position, 1.0);
}

#type fragment

#version 330 core
out vec4 color;

in vec4 v_Color;
in vec2 v_TextureCoordinates;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TextureCoordinates);
}