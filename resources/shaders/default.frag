#version 330 core

in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

uniform float randColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float transparency;

void main()
{
	fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), transparency); //* vec4(color.x * randColor, color.y * randColor * 0.8, color.z * randColor * 0.6, 1.0f);
}