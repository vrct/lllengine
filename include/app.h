#ifndef APP_H
#define APP_H

#include "lll.h"
//#include "camera.h"

class app
{
    private:
        SDL_Event e; //todo: rename
        lll engine;
        //maybe change maybe no need
        void pollEvents();
        //todo: hold current ticks in here too 

//todo: protected maybe better, and seperate game.cpp class
    public:
        bool quit { false }; //todo: rename
        const float maxFPS { 900.0f};
        const double PI  { atan(1) * 4 };
        Shader ourShader;
        //Camera cam;
    /*
        todo: appname, bundleid, maxfps vs. info about game
    */
        //create engine instance
        int start(int width = 640, int height = 360);
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
};

#endif