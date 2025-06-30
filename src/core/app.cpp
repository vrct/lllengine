#include "app.h"
#include "ecs_renderer.h"
#include <format>
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

app::app(){

}

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

//text icin eklendi

//endregion
void createEntitySquares(int w, int h, int hor_Count, int vert_Count, ComponentManager& context) {
    int squareWidth = w;
    int squareHeight = h;
    auto tex = loadTexture("resources/assets/fill3.jpg");
    auto tex2 = loadTexture("resources/assets/heart.jpg");

    for (int i = 0; i < vert_Count; i++)
    {
        for (int j = 0; j < hor_Count; j++)
        {
            // Entity entity;
            // entity.addComponent<PositionComp>(Position, i* (float)squareWidth, j*(float)squareHeight);
            // entity.addComponent<SizeComp>(Size, (float)squareWidth, (float)squareHeight);
            // entity.addComponent<ColorComp>(Color, vec4(1.0f, 1.0f, 1.0f, 1.0f));
            // entity.addComponent<TextureComp>(Texture, tex);
            //
            // context.addEntity(entity);

            auto e = context.createEntity();
            vec4 color2 = vec4((255.0f / (float)hor_Count) * (i* (float)squareWidth) / 255.0f, (255.0f / (float)vert_Count) * (j*(float)squareHeight) / 6500.0f, 1);
            context.addComponent(e, PositionComponent{i* (float)squareWidth, j*(float)squareHeight});
            context.addComponent(e, ColorComponent{color2});
            context.addComponent(e, SizeComponent{(float)squareWidth, (float)squareHeight});
            context.addComponent(e, TextureComponent {j % 2 == 0 ? tex : tex2});
        }
    }
}

int app::init()
{
    //new (&entityManager) EntityManager(componentManager);
    //ourShader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //ourShader.use();
    vec4 windowSize = engine.getWindowSize();
    auto* shader = new Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //Shader shader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    engine.ecs_renderer = new Renderer(*shader, componentManager);
    engine.ecs_renderer->windowSize = windowSize;
    // ComponentManager componentManager;
    //entityManager = new EntityManager(componentManager);
    // entityManager(componentManager);


    int squareWidth = 40;
    int squareHeight = 40;
    int hor_Count = windowSize.x / squareWidth;
    int vert_Count = windowSize.y / squareHeight;

    // auto testPic2 = loadTexture("resources/assets/heart.jpg");
    //testPic = testPic2;
    // createEntitySquares(squareWidth, squareHeight, hor_Count, vert_Count, componentManager);

    try {
        engine.ecs_renderer->loadTextAtlas("resources/font/notosans.ttf", 48);
    } catch (const std::exception& e) {
        std::cerr << "Error loading font: " << e.what() << std::endl;
        return -1;
    }

    // auto entity = componentManager.createEntity();
    // componentManager.addComponent(entity, PositionComponent{0, windowSize.y / 2});
    // componentManager.addComponent(entity, SizeComponent{(float)200, (float)200});
    // componentManager.addComponent(entity, ColorComponent{vec4(255,255,255)});
    // componentManager.addComponent(entity, TextureComponent{testPic2});

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
            // case SDL_MOUSEMOTION:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    //std::cout << "Left button pressed " << e.button.x << " " <<  e.button.y << std::endl;
                    mouseLeftClicked = true;
                    mousePos = vec4(e.button.x, engine.getWindowSize().y -  e.button.y, 0.0f, 1.0f);
                }else if (e.button.button == SDL_BUTTON_RIGHT) {
                    mouseRightClicked = true;
                    mousePos = vec4(e.button.x, engine.getWindowSize().y -  e.button.y, 0.0f, 1.0f);
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

    // vec4 winSize = engine.getWindowSize();

    // int squareWidth = 20;
    // int squareHeight = 20;
    // int hor_Count = winSize.x / squareWidth;
    // int vert_Count = winSize.y / squareHeight;
    //
    // float speed = 1.0f;
    // float time = (startTicks2 / 1000.0f) * speed;
    //
    // if (updateCount++ >= 1) {
    //     updateCount = 0;
    //     unsigned int p = rand() % componentManager.getEntityMasks().size() - 1;
    //     auto m = rand() + 1;
    //
    //     if (m % 2 == 0) {
    //         componentManager.removeEntity(p);
    //     }
    //     else {
    //         float px = rand() % (int)winSize.x - 20;
    //         float py = rand() % (int)winSize.y - 20;
    //
    //         float cx = rand() % 180 - 30;
    //         float cy = rand() % 255 - 30;
    //         float cz = rand() % 100 - 30;
    //
    //
    //         Entity e = componentManager.createEntity();
    //         // vec4 color2 = vec4((255.0f / (float)hor_Count) * (px / 255.0f), (255.0f / (float)vert_Count) * py / 6500.0f, 1);
    //         componentManager.addComponent(e, PositionComponent{px, py});
    //         componentManager.addComponent(e, ColorComponent{vec4(cx, cy, cz)});
    //         componentManager.addComponent(e, SizeComponent{20, 20});
    //     }
    // }
}


//color and updated frame draw in here
void app::draw()
{
    SDL_GL_SwapWindow(engine.getWindow());
    glClearColor(0.2f, 0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //gravitySystem.update(startTicks2);
    //engine.ecs_renderer->drawEntities(entities, startTicks2);
    std::string fpsString = "FPS: " + std::to_string(engine.getFPS());
    // engine.ecs_renderer->drawEntitiesBuffer();

    engine.ecs_renderer->drawText(fpsString, 0, engine.getWindowSize().y, 1.0f, vec4(.0f, 0.0f, 0.0f, 1.0f));
    // engine.ecs_renderer->drawText("SIRK MEYMUNU MERT !!", engine.getWindowSize().x / 2 - 150, engine.getWindowSize().y / 2, 1.0f, vec4(1.0f, 1.0f, 1.0f, 1.0f));


    // if (mouseRightClicked) {
    //     mouseRightClicked = false;
    //     //todo: remove first entity added and move last entity to that place
    //     gravitySystem.update(10);
    // }


    engine.calculateFPS(componentManager.getEntityMasks().size());
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