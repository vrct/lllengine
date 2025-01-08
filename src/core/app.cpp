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

//region: gameoflifemethods

struct lifeStruct {
    const int m;
    const int n;
    std::vector<std::vector<int>> currState;
    //int currState[50][50] = {0};

    lifeStruct(int row, int col) : m(row), n(col), currState(row, std::vector<int>(col, 0)) {}
};

struct mat3 {
    float m[3][3];
};

const mat3 glider = {
    0,1,0,
    0, 0,1,
    1,1, 1
};

const mat3 blinker = {
    0,1,0,
    0, 1,0,
    0,1, 0
};

void updateLife(lifeStruct& life) {
    //int updatedLife[50][50] = {0};

    std::vector<std::vector<int>> directions =
    {{0, 1}, {1, 0}, {0, -1},
     {-1, 0}, {1, 1}, {-1, -1},
     {1, -1}, {-1, 1}};

    int rowCount = life.m;
    int colCount = life.n;
    std::vector<std::vector<int>> updatedLife(rowCount, std::vector<int>(colCount, 0));

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {

            // Count the number of live neighbors
            int live = 0;
            for (auto dir : directions) {
                int x = i + dir[0];
                int y = j + dir[1];

                // Check if the neighbor is live
                if (x >= 0 && x < rowCount && y >= 0 && y < colCount && (life.currState[x][y] == 1)) {
                    live++;
                }
            }

            // If current cell is live and number of live neighbors
            // is less than 2 or greater than 3, then the cell will die
            if (life.currState[i][j] == 1 && (live < 2 || live > 3)) {
                updatedLife[i][j] = 0;
            }

            // If current cell is dead and number of live neighbors
            // is equal to 3, then the cell will become live
            else if (life.currState[i][j] == 0 && live == 3) {
                updatedLife[i][j] = 1;
            }

            // else the state of cells
            // will remain same.
            else {
                updatedLife[i][j] = life.currState[i][j];
            }
        }
    }

    /*for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            life.currState[i][j] = updatedLife[i][j];
        }
    }*/

    life.currState = updatedLife;
}

void createLife(lifeStruct* life, vec4 windowSize) {
    //todo: place glider random place
    //resetLife(life);

    //std::cout << life.m << " " << life.n << std::endl;

    // Sol üstte bir glider
    life->currState[2][3] = 1;
    life->currState[3][4] = 1;
    life->currState[4][2] = 1;
    life->currState[4][3] = 1;
    life->currState[4][4] = 1;

    // O->currSa sol bir lightweight spaceship (LWSS)
    life->currState[10][5] = 1;
    life->currState[11][6] = 1;
    life->currState[11][7] = 1;
    life->currState[11][8] = 1;
    life->currState[10][8] = 1;
    life->currState[9][8] = 1;
    life->currState[9][7] = 1;

    // O->currSada bir toad osilatör
    life->currState[25][25] = 1;
    life->currState[25][26] = 1;
    life->currState[25][27] = 1;
    life->currState[26][24] = 1;
    life->currState[26][25] = 1;
    life->currState[26][26] = 1;

    // S->currS altta bir beacon
    life->currState[40][40] = 1;
    life->currState[40][41] = 1;
    life->currState[41][40] = 1;
    life->currState[41][41] = 1;
    life->currState[42][42] = 1;
    life->currState[42][43] = 1;
    life->currState[43][42] = 1;
    life->currState[43][43] = 1;

    // S->currS üstte rastgele bir glider gun başlangıcı
    life->currState[5][30] = 1;
    life->currState[5][31] = 1;
    life->currState[6][30] = 1;
    life->currState[6][31] = 1;
    life->currState[4][34] = 1;
    life->currState[4][35] = 1;
    life->currState[5][33] = 1;
    life->currState[6][36] = 1;
    life->currState[7][35] = 1;
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
    auto tex = loadTexture("resources/assets/container.jpg");

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

lifeStruct* gof;
int app::init()
{
    //ourShader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //ourShader.use();
    vec4 windowSize = engine.getWindowSize();
    auto* shader = new Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //Shader shader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    engine.ecs_renderer = new Renderer(*shader);
    engine.ecs_renderer->windowSize = windowSize;

    int squareWidth = 40;
    int squareHeight = 40;
    int hor_Count = windowSize.x / squareWidth;
    int vert_Count = windowSize.y / squareHeight;

    gof = new lifeStruct(hor_Count, vert_Count);
    createLife(gof, windowSize);
    createEntitySquares(squareWidth, squareHeight, hor_Count, vert_Count, *this);

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
                    //todo: rendersystem square pass new window size
                }
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

    if(updateCount++ > 50)
    {
        //SDL_Delay(1000.f / maxFPS - frameTicks);
        updateLife(*gof);
        updateCount = 0;
    }

    vec4 winSize = engine.getWindowSize();

    int squareWidth = 10;
    int squareHeight = 10;
    int hor_Count = winSize.x / squareWidth;
    int vert_Count = winSize.y / squareHeight;

    float speed = 1.0f;
    float time = (startTicks2 / 1000.0f) * speed;


    for (int i = 0; i < gof->m; i++) {
        for (int j = 0; j < gof->n; j++) {
            auto* color = entities[i*gof->m + j].getComponent<ColorComp>(Color);
            color->color = gof->currState[i][j] ? vec4(1.0f, 1.0f, 1.0f, 1.0f) : vec4(0.0f, 0.0f, 0.0f, 0.7f);
        }
    }

    //for (auto& entity : entities) {
        //auto* color = entity.getComponent<ColorComp>();
        /*float gradientX = position->x / float(hor_Count);  // 0.0 → 1.0 (soldan sağa)
        float gradientY = position->y / float(vert_Count); // 0.0 → 1.0 (aşağıdan yukarıya)

        // Saat yönünde dönen renkler
        float red   = 0.5f + 0.5f * cos(time + gradientX * M_PI);        // R bileşeni
        float green = 0.5f + 0.5f * sin(time + gradientY * M_PI);        // G bileşeni
        float blue  = 0.5f + 0.5f * sin(time + gradientX * M_PI * 0.5f);*/
        //vec4 color2 = vec4((255 / hor_Count) * position->x / 250.0f, (255 / vert_Count) * position->y / 250.0f, fabs(sin((startTicks2 / 1000) * PI)));
        //color->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //}
}


//color and updated frame draw in here 
void app::draw()
{
    SDL_GL_SwapWindow(engine.getWindow());
    glClearColor(0.2f, 0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    engine.ecs_renderer->drawEntities(entities);
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