#version 330 core

layout (location = 0) in vec2 aPos;   // NDC'de pozisyon
layout (location = 1) in vec2 aSize;  // Boyut (zaten normalize edilmiş)
layout (location = 2) in vec4 aColor;  // Boyut (zaten normalize edilmiş)

uniform vec4 windowSize;
out vec4 outColor;

void main() {
    vec2 winSize = windowSize.xy;
    vec2 ndcTransformedPos = ((aPos / winSize) * 2) - 1;
    vec2 ndcScaledPos = (aSize / winSize) * 2;
    vec2 ndcFinal = ndcTransformedPos + ndcScaledPos;
    gl_Position = vec4(ndcTransformedPos, 0.0, 1.0);
    outColor = aColor;
}