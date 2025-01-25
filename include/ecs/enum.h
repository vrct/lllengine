//
// Created by Furkan ARICAN on 18.01.2025.
//

#ifndef ENUM_H
#define ENUM_H
#include <vec4.h>

enum ComponentType {
    Position = 0,
    Size = 1,
    Color = 2,
    Texture = 3
};

struct PositionComponent {
    float x;
    float y;
};

struct SizeComponent {
    float w;
    float h;
};

struct ColorComponent {
    vec4 color;
};

#endif //ENUM_H
