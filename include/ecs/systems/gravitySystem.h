//
// Created by Furkan ARICAN on 13.01.2025.
//

#ifndef GRAVITYSYSTEM_H
#define GRAVITYSYSTEM_H

#include "ecs/systems/system.h"
#include "ecs/components/positioncomp.h"


class gravitySystem : public System {

    public:
        void update(float deltaTime) override {
            //vec4 newPos = vec4();
            for (auto& entity : entities) {
                auto* position = entity.getComponent<PositionComp>(Position);
                //newPos.y = position->y - deltaTime * 0.01f;
                position->updateValue(position->x,position->y - deltaTime * 0.01f);
            }
        }

};



#endif //GRAVITYSYSTEM_H
