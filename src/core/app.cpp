#include "app.h"
#include "ecs_renderer.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

texture2D loadTexture(const char* filePath) {
    texture2D texture;

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data) {
        texture.generate(width, height, data);
        stbi_image_free(data);
    } else {
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }

    return texture;
}

//endregion
void createEntitySquares(int w, int h, int hor_Count, int vert_Count, app& context) {
    int squareWidth = w;
    int squareHeight = h;
    auto tex = loadTexture("resources/assets/face.png");

    for (int i = 0; i < hor_Count; i++)
    {
        for (int j = 0; j < vert_Count; j++)
        {
            Entity entity;
            entity.addComponent<PositionComp>(Position, i* (float)squareWidth, j*(float)squareHeight);
            entity.addComponent<SizeComp>(Size, (float)squareWidth, (float)squareHeight);
            entity.addComponent<ColorComp>(Color, vec4(1.0f, 1.0f, 1.0f, 1.0f));
            entity.addComponent<TextureComp>(Texture, tex);

            context.addEntity(entity);
        }
    }
}

int app::init()
{
    //ourShader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //ourShader.use();
    vec4 windowSize = engine.getWindowSize();
    auto* shader = new Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //Shader shader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    engine.ecs_renderer = new Renderer(*shader);
    engine.ecs_renderer->windowSize = windowSize;

    int squareWidth = 3;
    int squareHeight = 3;
    int hor_Count = windowSize.x / squareWidth;
    int vert_Count = windowSize.y / squareHeight;

    auto testPic2 = loadTexture("resources/assets/heart.jpg");
    //testPic = testPic2;
    //createEntitySquares(squareWidth, squareHeight, hor_Count, vert_Count, *this);

    //initSquare();
    //move to another method (camPos, camView, camZoom)
    //cam = Camera(vec4(), vec4(windowSize.x, windowSize.y), 100);

    return EXIT_SUCCESS;
}

bool mouseLeftClicked;
bool mouseRightClicked;
vec4 mousePos;

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
                    //todo: rendersystem square pass new window size
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    //std::cout << "Left button pressed " << e.button.x << " " <<  e.button.y << std::endl;
                    mouseLeftClicked = true;
                    mousePos = vec4(e.button.x, engine.getWindowSize().y -  e.button.y, 0.0f, 1.0f);
                }else if (e.button.button == SDL_BUTTON_RIGHT) {
                    mouseRightClicked = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouseLeftClicked = false;
                break;
        }
    }
}

double startTicks2 = 0;
int updateCount;


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

    int squareWidth = 20;
    int squareHeight = 20;
    int hor_Count = winSize.x / squareWidth;
    int vert_Count = winSize.y / squareHeight;

    float speed = 1.0f;
    float time = (startTicks2 / 1000.0f) * speed;

    if (mouseLeftClicked) {
        //todo: change here
        mouseLeftClicked = false;
        Entity entity;
        entity.addComponent<PositionComp>(Position, mousePos.x, mousePos.y);
        entity.addComponent<SizeComp>(Size, (float)squareWidth, (float)squareHeight);
        entity.addComponent<ColorComp>(Color, vec4(1.0f, 1.0f, 1.0f, 1.0f));
        // entity.addComponent<TextureComp>(Texture, loadTexture("resources/assets/heart.jpg"));
        //entity.makeDirty();

        gravitySystem.addEntity(entity);
        addEntity(entity);
    }




    for (auto& entity : entities) {
        auto* color = entity.getComponent<ColorComp>(Color);
        auto* position = entity.getComponent<PositionComp>(Position);
        auto* size = entity.getComponent<SizeComp>(Size);
        /*float gradientX = position->x / float(hor_Count);  // 0.0 → 1.0 (soldan sağa)
        float gradientY = position->y / float(vert_Count); // 0.0 → 1.0 (aşağıdan yukarıya)

        // Saat yönünde dönen renkler
        float red   = 0.5f + 0.5f * cos(time + gradientX * M_PI);        // R bileşeni
        float green = 0.5f + 0.5f * sin(time + gradientY * M_PI);        // G bileşeni
        float blue  = 0.5f + 0.5f * sin(time + gradientX * M_PI * 0.5f);*/
        vec4 color2 = vec4((255.0f / (float)hor_Count) * position->x / 255.0f, (255.0f / (float)vert_Count) * position->y / 6500.0f, fabs(sin((startTicks2 / 1000) * PI)));
        //color->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        // if (mouseClicked && mousePos.x > position->x && mousePos.x <= position->x + size->w && mousePos.y > position->y && mousePos.y <= position->y + size->h) {
        color->updateValue(color2);
        // }

        //position->updateValue(position->x, position->y - 0.1f);
    }
}


//color and updated frame draw in here 
void app::draw()
{
    SDL_GL_SwapWindow(engine.getWindow());
    glClearColor(0.2f, 0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gravitySystem.update(startTicks2);
    engine.ecs_renderer->drawEntities(entities, startTicks2);


    // if (mouseRightClicked) {
    //     mouseRightClicked = false;
    //     //todo: remove first entity added and move last entity to that place
    //     gravitySystem.update(10);
    // }


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