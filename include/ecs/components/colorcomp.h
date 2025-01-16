//
// Created by Furkan ARICAN on 25.12.2024.
//

#ifndef COLORCOMP_H
#define COLORCOMP_H

#include "ecs/entity.h"
#include "vec4.h"

class ColorComp : public Component{
    public:
      vec4 color;

      ColorComp(vec4 color) : color(color){}

    void updateValue(vec4 updatedColor){
          if (!(updatedColor != color)){
              //std::cout << "Updating color component" << updatedColor - color <<  std::endl;
              color = updatedColor;
              incrementVersion(); // Versiyonu artır
          }
      }
};

#endif //COLORCOMP_H
