//
// Created by Furkan ARICAN on 18.01.2025.
//

#ifndef ENUM_H
#define ENUM_H
#include <vec4.h>

enum ComponentType {
    Position = 1 << 0,
    Size = 1 << 1,
    Color = 1 << 2,
    Texture = 1 << 3
};

enum class ComponentTypeE : unsigned int
{
    Empty = 1 << 0,
    Position = 1 << 1,
    Velocity = 1 << 2,
    Graphics = 1 << 3,
    Texture = 1 << 4
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

struct EmptyComponent {};

#endif //ENUM_H
