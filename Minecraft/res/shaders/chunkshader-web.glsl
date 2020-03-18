#type vertex

attribute highp vec3 a_Coordinates;
attribute highp vec2 a_TexCoords;
attribute highp float a_Tid;

uniform highp vec3 u_ChunkPosition;
uniform highp mat4 u_ProjectionMatrix;
uniform highp mat4 u_ViewMatrix;

varying highp vec2 v_TexCoords;
varying highp float v_Tid;

void main()
{
	v_Tid = a_Tid;
	v_TexCoords = vec2(a_TexCoords.x, 16.0 - a_TexCoords.y) / 16.0;
	gl_Position =  u_ProjectionMatrix * u_ViewMatrix * vec4(u_ChunkPosition * 16.0 + a_Coordinates.xyz, 1.0);
}

#type fragment

varying highp vec2 v_TexCoords;
varying highp float v_Tid;

uniform sampler2D u_Texture_0;
uniform sampler2D u_Texture_1;
uniform sampler2D u_Texture_2;
uniform sampler2D u_Texture_3;
uniform sampler2D u_Texture_4;
uniform sampler2D u_Texture_5;
uniform sampler2D u_Texture_6;
uniform sampler2D u_Texture_7;

void main(void) {
	int tid = int(v_Tid);
	if (tid == 0)
		gl_FragColor = texture2D(u_Texture_0, v_TexCoords);
	else if (tid == 1)
		gl_FragColor = texture2D(u_Texture_1, v_TexCoords);
	else if (tid == 2)
		gl_FragColor = texture2D(u_Texture_2, v_TexCoords);
	else if (tid == 3)
		gl_FragColor = texture2D(u_Texture_3, v_TexCoords);
	else if (tid == 4)
		gl_FragColor = texture2D(u_Texture_4, v_TexCoords);
	else if (tid == 5)
		gl_FragColor = texture2D(u_Texture_5, v_TexCoords);
	else if (tid == 6)
		gl_FragColor = texture2D(u_Texture_6, v_TexCoords);
	else if (tid == 7)
		gl_FragColor = texture2D(u_Texture_7, v_TexCoords);
}
