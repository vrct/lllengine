#version 330 core

in VS_OUT {
    vec4 color;
    vec2 texCoord;
} fs_in;

//in vec4 outColor;
//in vec2 outTexCoord;

uniform sampler2D texture1;
uniform bool hasTexture;

out vec4 FragColor;

void main() {
    //FragColor = vec4(1.0, 0.0, 1.0, 0.5);
    //FragColor = outColor;
    float alpha = texture(texture1, fs_in.texCoord).r;
    FragColor = vec4(fs_in.color.rgb, fs_in.color.a * alpha);
    //todo: test color
//    if(hasTexture)
//    {
//        FragColor = texture(texture1, fs_in.texCoord) * fs_in.color;
//    }
//    else
//    {
//        FragColor = outColor;
//    }
}