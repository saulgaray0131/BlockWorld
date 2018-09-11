#version 440

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;

uniform mat4 ortho;

out vec2 uvs;

void main() {
	gl_Position = ortho * vec4(position + vec3(927.5, 527.5, 0), 1.0);
	uvs = uv;
}