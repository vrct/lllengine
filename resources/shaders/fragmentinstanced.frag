#version 330 core

in vec4 vertexColor; // Vertex shader'dan gelen renk
out vec4 FragColor;  // Ekrana çıkacak renk

void main()
{
    FragColor = vertexColor; // Gelen rengi kullanarak fragment'ı renklendir
}
