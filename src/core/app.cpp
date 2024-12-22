#include "app.h"
#include "ecs_renderer.h"

int app::start(int width, int height)
{
    printf("INIT SUCCESSSSSSSSSS 0 ");
    if(engine.InitSDL())
    {
        return EXIT_FAILURE;
    }

    printf("INIT SUCCESSSSSSSSSS 9 ");
    if(engine.InitWindow(width, height))
    {
        return EXIT_FAILURE;
    }

    if(engine.InitGLContext())
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

unsigned int VBO, VAO, EBO;

int app::init()
{
    //ourShader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //ourShader.use();
    vec4 windowSize = engine.getWindowSize();
    auto* shader = new Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //Shader shader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    engine.ecs_renderer = new Renderer(*shader);
    engine.ecs_renderer->windowSize = windowSize;
    //initSquare();
    //move to another method (camPos, camView, camZoom)
    //cam = Camera(vec4(), vec4(windowSize.x, windowSize.y), 100);

    return EXIT_SUCCESS;
}

//todo: if needed return event and process later !!!!!!!!
void app::pollEvents()
{
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
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || e.window.event == SDL_WINDOWEVENT_RESIZED )
                {
                    engine.setWindowSize(e.window.data1, e.window.data2);
                }
                break;
        }
    }
}

double startTicks2 = 0;

//physics or data updates in here
void app::update()
{
    pollEvents();
    float frameTicks = SDL_GetTicks() - startTicks2;
    startTicks2 = SDL_GetTicks();
    if(1000.f / maxFPS > frameTicks)
    {
        SDL_Delay(1000.f / maxFPS - frameTicks);
    }

    vec4 winSize = engine.getWindowSize();

    int squareWidth = 10;
    int squareHeight = 10;
    int hor_Count = winSize.x / squareWidth;
    int vert_Count = winSize.y / squareHeight;

    float speed = 1.0f;
    float time = (startTicks2 / 1000.0f) * speed;

    for (int i = 0; i < hor_Count + 1; i++)
    {
        for (int j = 0; j < vert_Count + 1; j++)
        {
            // Saat yönünde RGB rotasyonu
            float gradientX = i / float(hor_Count);  // 0.0 → 1.0 (soldan sağa)
            float gradientY = j / float(vert_Count); // 0.0 → 1.0 (aşağıdan yukarıya)

            // Saat yönünde dönen renkler
            float red   = 0.5f + 0.5f * cos(time + gradientX * M_PI);        // R bileşeni
            float green = 0.5f + 0.5f * sin(time + gradientY * M_PI);        // G bileşeni
            float blue  = 0.5f + 0.5f * sin(time + gradientX * M_PI * 0.5f);
            //vec4 color = vec4((255 / hor_Count) * i / 250.0f, (255 / vert_Count) * j / 250.0f, fabs(sin((startTicks2 / 1000) * PI)));
            //drawSquare(i*squareWidth, j*squareHeight, squareWidth, squareHeight, color);

            /*float x1 = (((i*squareWidth) / winSize.x) * 2) - 1;
            float y1 = (((j*squareHeight) / winSize.y) * 2) - 1;
            float x2 = (squareWidth / winSize.x) * 2;
            float y2 = (squareHeight / winSize.y) * 2;
            */

            //std::cout << "UPDATE HAPPENED RESIZE: " << sizeof(float[4]) << " " << sizeof(asd) << " " << asd.data() << " " << y2 << std::endl;

            //pushVertex(&engine.renderer, x1, y1, x2, y2, vec4(red,green,blue));
            //engine.ecs_renderer->pushVertex({x1, y1, x2, y2, vec4(red,green,blue)});
            engine.ecs_renderer->pushVertex({i*(float)squareWidth, j*(float)squareHeight, (float)squareWidth, (float)squareHeight, vec4(red,green,blue)});
        }
    }
    
}


//color and updated frame draw in here 
void app::draw()
{
    SDL_GL_SwapWindow(engine.getWindow());
    glClearColor(0.2f, 0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //drawRenderer(&engine.renderer);
    //for calculating fps and printing to console
    /*vec4 winSize = engine.getWindowSize();
    float x1 = (((5*20) / winSize.x) * 2) - 1;
    float y1 = (((5*20) / winSize.y) * 2) - 1;
    float x2 = (20 / winSize.x) * 2;
    float y2 = (20 / winSize.y) * 2;
    engine.ecs_renderer->pushVertex({x1, y1, x2, y2, vec4(1.0f, 0.0f, 1.0f)});*/
    engine.ecs_renderer->draw();
    engine.calculateFPS();
}

int app::pause()
{
    return EXIT_FAILURE;
}

int app::kill()
{
    //killRenderer(&engine.renderer);
    delete engine.ecs_renderer;
    SDL_Quit();
    return EXIT_FAILURE;
}