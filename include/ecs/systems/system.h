//
// Created by Furkan ARICAN on 15.01.2025.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "ecs/entity.h"

class System {

    protected:
        std::vector<Entity> entities;

    public:
        virtual ~System() = default;

        virtual void addEntity(const Entity& entity)
        {
            entities.push_back(entity);
        }

        virtual void removeEntity(Entity* entity)
        {

        }

        //todo: brauchen wir deltaTime ?
        virtual void update(float deltaTime) = 0;
};

#endif //SYSTEM_H
