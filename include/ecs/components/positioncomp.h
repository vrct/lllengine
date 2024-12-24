//
// Created by Furkan ARICAN on 24.12.2024.
//

#ifndef POSITIONCOMP_H
#define POSITIONCOMP_H

#include "ecs/entity.h"

class PositionComp : public Component{
    public:
      float x, y;

      PositionComp(float x, float y) : x(x),y(y){}
};

#endif //POSITIONCOMP_H
