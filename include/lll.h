#ifndef LLL_H
#define LLL_H

#include "stdio.h"
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include "vec4.h"
//#include "renderer.h"
#include "ecs_renderer.h"

struct lll
{
    private:
        int w_width, w_height, frameCount;
        Uint32 startTime;
        SDL_Window* window;
        SDL_GLContext* context;

    public:
        float FPS;
        //todo: change place
        //batchRenderer renderer;
        Renderer* ecs_renderer;

        //int InitSDL();
        //int InitWindow(int = 640, int = 360);
        //int InitGLContext(SDL_Window* window);
        SDL_Window* getWindow() {return window;};
        vec4 getWindowSize() {return vec4(w_width, w_height);}

        void setWindowSize(int width, int height)
        {
            w_width = width;
            w_height = height;
            vec4 asd = getWindowSize();
            std::cout << "EVENT TRIGGERED: " << asd.x << " " << asd.y << std::endl;
            ecs_renderer->windowSize = vec4(static_cast<float>(w_width), static_cast<float>(w_height));
            SDL_SetWindowSize(window, width, height);
        }

        void calculateFPS(int entityCount)
        {
            frameCount++;
            Uint32 currentTime = SDL_GetTicks();

            float elapsedSeconds = (currentTime - startTime) / 1000.0f;
            if(elapsedSeconds >= 1.0f)
            {
                FPS = frameCount / elapsedSeconds;
                std::cout << "FPS: " <<  FPS << " ECS_ENTITYCOUNT: " << entityCount << std::endl;
                //std::cout << "VERTICECOUNT: " << renderer.vertexCount << std::endl; 
                frameCount = 0;
                startTime = currentTime;
            }
        }

        int InitSDL()
        {
            printf("INIT SUCCESSSSSSSSSS 5 ");
            if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
            {
                printf("SDL VIDEO AND TIMER COULDNT BE INITIALIZED");
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }

        /*SDL_Window* InitWindow(int width = 640, int height = 360)
        {
            //this is need for shaders and needs to be defined before window creation otherwise shaders not compile
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_Window* window = SDL_CreateWindow("SDL GAME TUTORIAL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
            if(!window)
            {
                printf("COULDN'T INITIALIZE WINDOW ERROR: \n%s", SDL_GetError());
                return nullptr;
            }

            return window;
        }*/
        int InitWindow(int width = 640, int height = 360)
        {
            printf("INIT SUCCESSSSSSSSSS 4 ");
            //this is need for shaders and needs to be defined before window creation otherwise shaders not compile
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            window = SDL_CreateWindow("SDL GAME TUTORIAL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
            if(!window)
            {
                printf("COULDN'T INITIALIZE WINDOW ERROR: \n%s", SDL_GetError());
                return EXIT_FAILURE;
            }

            w_width = width;
            w_height = height;

            return EXIT_SUCCESS;
        }

        /*SDL_GLContext* InitGLContext(SDL_Window* window)
        {
            SDL_GLContext glContext = SDL_GL_CreateContext(window);
            if(!glContext)
            {
                printf("COULDN'T INITIALIZE RENDERRER ERROR: \n%s", SDL_GetError());
                return nullptr;
            }
            else
            {
                printf("RENDERERRRRRRR CREATED");

                glewExperimental = GL_TRUE;
                if (glewInit() != GLEW_OK)
                {
                    printf("Failed to initialize GLEW");
                    return nullptr;
                }
                else
                {
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                    return &glContext;
                }
            }

            return nullptr;
        }*/

        int InitGLContext()
        {
            printf("INIT SUCCESSSSSSSSSS 6 ");
            SDL_GLContext glContext = SDL_GL_CreateContext(window);
            if(!glContext)
            {
                printf("COULDN'T INITIALIZE RENDERRER ERROR: \n%s", SDL_GetError());
                return EXIT_FAILURE;
            }
            else
            {
                printf("RENDERERRRRRRR CREATED");

                glewExperimental = GL_TRUE;
                if (glewInit() != GLEW_OK)
                {
                    printf("Failed to initialize GLEW");
                    return EXIT_FAILURE;
                }
                else
                {
                    /*SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);*/
                    context = &glContext;
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                    return EXIT_SUCCESS;
                }
            }

            //todo: maybe temporary place can be changed
            startTime = SDL_GetTicks();
        }
};

#endif