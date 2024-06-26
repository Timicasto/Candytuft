#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
    color = sampled.w > 0.5 ? (vec4(textColor.xyz, textColor.w * sampled.w)) : vec4(0.0, 0.0, 0.0, 0.0);
}
