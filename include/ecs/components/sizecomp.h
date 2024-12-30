//
// Created by Furkan ARICAN on 25.12.2024.
//

#ifndef SIZECOMP_H
#define SIZECOMP_H

#include "ecs/entity.h"

class SizeComp : public Component{
    public:
      float w, h;

      SizeComp(float w, float h) : w(w),h(h){}
};

#endif //SIZECOMP_H
