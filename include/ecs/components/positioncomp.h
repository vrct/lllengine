//
// Created by Furkan ARICAN on 24.12.2024.
//

#ifndef POSITIONCOMP_H
#define POSITIONCOMP_H

#include "ecs/entity.h"

class PositionComp : public Component{
    private:
        unsigned int _id = Position;
    public:
      float x, y;

      PositionComp(float x, float y) : x(x),y(y){}

    void updateValue(float newValueX, float newValueY){
          if (x != newValueX || y != newValueY) {
              x = newValueX;
              y = newValueY;
              incrementVersion(); // Versiyonu artır
          }
      }

};

#endif //POSITIONCOMP_H
