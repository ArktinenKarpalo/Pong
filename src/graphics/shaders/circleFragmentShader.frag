#version 450 core
out vec4 FragColor;

in vec3 loc;

uniform float radius;
uniform vec3 center;
uniform vec3 color;

void main() {
	if((loc.x-center.x)*(loc.x-center.x)+(loc.y-center.y)*(loc.y-center.y) > radius*radius)
		discard;
	FragColor = vec4(color, 1);
}