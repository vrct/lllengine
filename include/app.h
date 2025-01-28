#ifndef APP_H
#define APP_H

#include "lll.h"
#include "ecs/entity.h"
#include "ecs/systems/gravitySystem.h"
#include "ecs/systems/renderSystem.h"
#include "ecs/componentManager.h"
#include "ecs/entityManager.h"
//#include "camera.h"

class app
{
    private:
        SDL_Event e; //todo: rename
        lll engine;
        //maybe change maybe no need
        void pollEvents();
        std::vector<Entity> entities;
        ComponentManager componentManager; // ComponentManager örneği

        //todo: hold current ticks in here too 

//todo: protected maybe better, and seperate game.cpp class
    public:
        bool quit { false }; //todo: rename
        const float maxFPS { 10000.0f};
        const double PI  { atan(1) * 4 };
        Shader ourShader;
        gravitySystem gravitySystem;
        //EntityManager* entityManager;
        //ComponentManager* componentManager;
        //Camera cam;
    /*
        todo: appname, bundleid, maxfps vs. info about game
    */
        app();
        //create engine instance
        int start(int width = 500, int height = 500);
        //run init methods
        int init();
        //override this method
        void update();
        //override this method until sprite class changes (everything updated themselves)
        void draw();
        //pause switch (dont update and refresh the frames)
        int pause();
        //kill every process and memory allocations
        int kill();
        //
        // //todo: temporary change here to entity manager
        // void addEntity(const Entity &entity) {
        //     entities.push_back(entity);
        // }
};

#endif