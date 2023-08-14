#version 330 core

out vec4 FragColor;

in vec4 coord;
in vec2 TexCoord;


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float u_time;


void main()
{
	vec4 Color = vec4(0.1137, 0.1137, 0.4941, 1.0);
	//FragColor = mix(texture(texture1, TexCoord)* Color, texture(texture2,TexCoord), 0.2);
	//FragColor = vec4(objectColor * lightColor, Color);
	FragColor = texture(texture1, TexCoord);
}