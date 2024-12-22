#version 330 core

layout (location = 0) in vec3 aPos;           // Statik vertex pozisyonu
layout (location = 1) in vec4 instancePos;    // Instance pozisyon ve boyut (x, y, width, height)
layout (location = 2) in vec4 instanceColor;  // Instance renk (r, g, b, a)

out vec4 vertexColor; // Fragment shader'a gönderilecek renk

void main()
{
    vec3 pos = aPos;
    pos.x = pos.x * instancePos.z + instancePos.x; // Genişlik ve X pozisyonu
    pos.y = pos.y * instancePos.w + instancePos.y; // Yükseklik ve Y pozisyonu

    gl_Position = vec4(pos, 1.0);
    vertexColor = instanceColor; // Renk bilgisini fragment shader'a gönder
}