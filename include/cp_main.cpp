#include "stdio.h"
#include "shader.h"
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include "camera.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int InitSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL VIDEO AND TIMER COULDNT BE INITIALIZED");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

SDL_Window* InitWindow()
{
    //this is need for shaders and needs to be defined before window creation otherwise shaders not compile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window* window = SDL_CreateWindow("SDL GAME TUTORIAL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(!window)
    {
        printf("COULDN'T INITIALIZE WINDOW ERROR: \n%s", SDL_GetError());
        return nullptr;
    }

    return window;
}

SDL_GLContext* InitGLContext(SDL_Window* window)
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
            /*SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);*/
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            return &glContext;
        }
    }

    return nullptr;
}

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL VIDEO AND TIMER COULDNT BE INITIALIZED");
        return EXIT_FAILURE;
    }

    SDL_Window* window = InitWindow();
    if(!window)
    {
        printf("COULDN'T INITIALIZE WINDOW ERROR: \n%s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GLContext* context = InitGLContext(window);
    if(!context)
    {
        printf("COULDN'T INITIALIZE WINDOW ERROR: \n%s", SDL_GetError());
        return EXIT_FAILURE;
    }

    //topleft and bottomleft rectangles
    float vertices[] = {
        //topright
        -0.5f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 
        0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,     0.0f, 0.0f, 0.0f,     0.0f, 1.0f
    };

    //topleft and bottomleft rectangle indices
    unsigned int indices[] =
    {
        0, 1, 3, //first triangle
        1, 2, 3
    };

    unsigned int VBO[2], VAO[2];
    unsigned int EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO[0]);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
    atexit(SDL_Quit);

    printf("EVERYTHING IS READY FOR RENDER");
    SDL_Event e;
    bool quit = false;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    const float maxFPS = 120.f;
    const double PI = atan(1) * 4;

    //glUseProgram(shaderProgram);
    Shader ourShader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");

    //load texture
    unsigned int texture[3];
    glGenTextures(3, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("resources/assets/container.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"Failed to load Texture"<<std::endl;
    }

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data2 = stbi_load("resources/assets/wall.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"Failed to load Texture"<<std::endl;
    }

    stbi_image_free(data2);

///
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data3 = stbi_load("resources/assets/face.png", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"Failed to load Texture"<<std::endl;
    }

    stbi_image_free(data3);
///

    ourShader.use();
    //ourShader.setInt("ourTexture", 0);
    ourShader.setInt("ourTexture2", 1);

    vec4 cameraPos = vec4(320, -180);
    vec4 cameraView = vec4(640, 360);
    Camera cam = Camera(cameraPos, cameraView, 100);

    while (!quit)
    {
        double startTicks = SDL_GetTicks();
        while(SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                case SDL_KEYUP:
                    /* code */
                    if(e.type == SDL_KEYUP && e.key.keysym.sym != SDLK_ESCAPE) break;
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    if(e.key.keysym.sym != SDLK_a) break;
                    break;
            }
        }

        SDL_GL_SwapWindow(window);

        float frameTicks = SDL_GetTicks() - startTicks;
        if(1000.f / maxFPS > frameTicks)
        {
            SDL_Delay(1000.f / maxFPS - frameTicks);
        }

        glClearColor(0.2f, 0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //update uniform color here
        double timeValue = SDL_GetTicks() - startTicks;
        double startTicks2 = SDL_GetTicks();
        float greenValue = static_cast<float>(sin((startTicks2 / 1000) * PI));
        float greenValue2 = static_cast<float>(cos((startTicks2 / 1000) * PI));
        //printf("TICKSORIGIN: %f TICKS: %f SIN: %f\n", startTicks2, (fabs(sin((startTicks2 / 1000) * PI))), greenValue2);

        vec4 vtest1 = vec4();
        vec4 vtest2 = vec4().identity();
        double testvecvalue = (fabs(sin((startTicks2 / 1000) * PI)));
        vec4 vtest3 = ((vtest2 * 3) * vec4(3, 5, testvecvalue * 10) + vtest2) / 10;
        vec4 vtest4 = vec4(1,2,3);
        vec4 vtest5 = vec4(3,4,5);

        matrix4 mattest = matrix4(4,2,0,0,0,8,1,0,0,1,0,0);
        matrix4 matidentity = matrix4().identity();
        matrix4 matscale = matrix4().identity() * 1;
        matscale.w3 = 1;
        matrix4 mattranslation = matrix4().identity();
        mattranslation.x3 = 0;
        mattranslation.y3 = 0;
        mattranslation.z3 = 0;
        matrix4 mattest1 = matrix4(4,2,1,0,2,0,4,0,9,4,2,0);

        //TODO: CHANGE TRANSLATION MATRIX CALCULATION TO FIX VISIBILITY PROPBLEM
        //printf("TICKSORIGIN: %f TICKS: %f SIN: %o\n", startTicks2, (fabs(sin((startTicks2 / 1000) * PI))), vtest2);
        //cam.move(vec4((fabs(sin((startTicks2 / 1000) * PI))) * 1 , 1, 1), .8f);
        cam.setZoom(sin((startTicks2 / 1000) * PI));
        cam.calculateMatrix();
        //std::cout << "TICKSORIGIN: " <<  startTicks2 << "TICKS: " << (fabs(sin((startTicks2 / 1000) * PI))) << "VECTEST: " << cam.getUpdatedMatrix() << std::endl;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (mattranslation * matscale).data());

        //bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[2]);

        glBindVertexArray(VAO[0]);
        
        ourShader.setMatrix4("transform", cam.getUpdatedMatrix());
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


        /*matrix4 matscale2 = matrix4().identity() * (float)fabs(sin((startTicks2 / 1000) * PI));
        matscale2.w3 = 1;
        matrix4 mattranslation2 = matrix4().identity();
        mattranslation2.x3 = -.5f;
        mattranslation2.y3 = -.5f;
        mattranslation2.z3 = -.5f;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (mattranslation2 * matrix4().rotationZ(((startTicks2 / 100) * PI)) * matscale2).data());
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);*/
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
    ourShader.deleteProgram();
    //stage->Destroy();
    //stage->~Stage();
    SDL_Quit();

    return 0;
}
