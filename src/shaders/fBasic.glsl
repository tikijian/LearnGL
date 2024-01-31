#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textureData;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
   FragColor = texture(textureData, TexCoord) * vec4(lightColor * objectColor, 1.0);
}
