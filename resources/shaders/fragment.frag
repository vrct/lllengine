#version 330 core

in vec4 outColor;
in vec2 outTexCoord;

uniform sampler2D texture1;
uniform bool hasTexture;

out vec4 FragColor;

void main() {
    //FragColor = vec4(1.0, 0.0, 1.0, 0.5);
    //FragColor = outColor;
    //todo: test color
    if(hasTexture)
    {
        FragColor = texture(texture1, outTexCoord) * outColor;
    }
    else
    {
        FragColor = outColor;
    }
}