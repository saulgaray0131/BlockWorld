#version 430

layout(binding = 0) uniform sampler2DArray textureArray;

in vec3 uv;
in flat uint lightValue;

out vec4 color;

void main() {
    color = texture(textureArray, uv);
	color.rgb *= (lightValue / 15.0);
}