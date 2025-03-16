#version 440 core

layout (location = 0) in vec2 pos;

uniform float zoom;
uniform vec2 offset;

void main() {
	gl_Position = vec4((pos + offset) * zoom, 0.0f, 1.0f);
}