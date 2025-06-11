//#version 330 core
//
//layout (location = 0) in vec2 aPos;        // Entity'nin merkez pozisyonu
//layout (location = 1) in vec2 aSize;       // Entity'nin boyutu
//layout (location = 2) in vec4 aColor;
//layout (location = 3) in vec2 aTexCoord;   // UV (0,0)-(1,1) arası olmalı
//
//out VS_OUT {
//    vec4 color;
//    vec2 texCoord;
//} vs_out;
//
//uniform vec4 windowSize;
//
//void main()
//{
//    vec2 winSize = windowSize.xy;
//
//    // aTexCoord 0 veya 1 olacak, vertex'e göre
//    vec2 scaledOffset = (aTexCoord * aSize) / winSize * 2.0;
//
//    vec2 ndcPos = ((aPos / winSize) * 2.0) - 1.0;
//
//    gl_Position = vec4(ndcPos, 0.0, 1.0);
//
//    vs_out.color = aColor;
//    vs_out.texCoord = aTexCoord;
//}



#version 330 core

layout (location = 0) in vec2 aPos;   // NDC'de pozisyon
layout (location = 1) in vec2 aSize;  // Boyut (zaten normalize edilmiş)
layout (location = 2) in vec4 aColor;  // Boyut (zaten normalize edilmiş)
layout (location = 3) in vec2 aTexCoord;  // Boyut (zaten normalize edilmiş)

out VS_OUT {
    vec4 color;
    vec2 texCoord;
} vs_out;

uniform vec4 windowSize;
uniform bool gravityActive;
uniform float gravityDeltaTime;
//out vec4 outColor;
//out vec2 outTexCoord;

float gravityThreshold = 0.0001;

void main() {
    vec2 winSize = windowSize.xy;
    vec2 ndcTransformedPos = ((aPos / winSize) * 2) - 1;
    //ndcTransformedPos.y = ndcTransformedPos.y + gravityThreshold * gravityDeltaTime;
    vec2 ndcScaledPos = (aSize / winSize) * 2;
    vec2 ndcFinal = ndcTransformedPos + ndcScaledPos;
    gl_Position = vec4(ndcTransformedPos, 0.0, 1.0);
    vs_out.color = aColor;
//    outColor = aColor;
    vs_out.texCoord = aTexCoord;
}