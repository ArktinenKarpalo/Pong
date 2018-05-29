#version 450 core
layout (location = 0) in vec3 aPos;

out vec3 loc, mid;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	loc = vec3((model*vec4(aPos, 1.0f)).xyz);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}