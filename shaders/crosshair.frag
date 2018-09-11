#version 440

layout(binding = 0) uniform sampler2D tex;
in vec2 uvs;

out vec4 color;

void main() {
	color = texture(tex, uvs);
}