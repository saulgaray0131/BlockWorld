#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in uint textureIndex;
layout(location = 2) in vec2 uvs;
layout(location = 3) in uint lightVal;

uniform mat4 view;
uniform mat4 projection;

out vec3 uv;
out uint lightValue;

void main() {
	gl_Position = projection * view * vec4(pos, 1.0);

	uv = vec3(uvs, textureIndex);
	lightValue = lightVal;
}