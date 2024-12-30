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

//region: gameoflifemethods

struct lifeStruct {
    static int m;
    static int n;
    int currState[50][50] = {0};
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

bool checkCell(lifeStruct& life, int x, int y) {
    bool isAlive = true;

    int neighbourCount = 0;

    if (x - 1 > 0 && y - 1 > 0) {
        neighbourCount +=
            life.currState[x - 1][y - 1] +
            life.currState[x][y - 1] +
            life.currState[x - 1][y];
    }

    if (x + 1 < 50 && y + 1 < 50) {
        neighbourCount +=
            life.currState[x + 1][y] +
            life.currState[x + 1][y + 1] +
            life.currState[x][y + 1];
    }

    if (x - 1 > 0 && y + 1 < 50) {
        neighbourCount +=
            life.currState[x - 1][y + 1];
    }

    if (x + 1 < 50 && y - 1 > 0) {
        neighbourCount +=
            life.currState[x + 1][y - 1];
    }

    isAlive = !(neighbourCount < 2 || neighbourCount > 3);

    return isAlive;
}

void updateLife(lifeStruct& life) {
    //todo: check current cells update state
    /*int updatedLife[50][50] = {0};
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            updatedLife[i][j] = checkCell(life, i, j) ? 1 : 0;
        }
    }

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            life.currState[i][j] = updatedLife[i][j];
        }
    }*/

    int updatedLife[50][50] = {0};

    std::vector<std::vector<int>> directions =
    {{0, 1}, {1, 0}, {0, -1},
     {-1, 0}, {1, 1}, {-1, -1},
     {1, -1}, {-1, 1}};

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {

            // Count the number of live neighbors
            int live = 0;
            for (auto dir : directions) {
                int x = i + dir[0];
                int y = j + dir[1];

                // Check if the neighbor is live
                if (x >= 0 && x < 50 && y >= 0 && y < 50 && (life.currState[x][y] == 1)) {
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

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            life.currState[i][j] = updatedLife[i][j];
        }
    }
}

lifeStruct createLife(vec4 windowSize) {
    //todo: place glider random place
    //resetLife(life);

    //std::cout << life.m << " " << life.n << std::endl;

    lifeStruct life;
    // Alive hücrelerin (O) koordinatları
    // Başlangıç noktası: Satır = 13, Sütun = 16

    // 0. Satırdan itibaren
    // life.currState[13][22] = 1;
    // life.currState[13][23] = 1;
    // life.currState[13][27] = 1;
    // life.currState[13][28] = 1;
    //
    // life.currState[14][22] = 1;
    // life.currState[14][23] = 1;
    // life.currState[14][26] = 1;
    // life.currState[14][28] = 1;
    // life.currState[14][29] = 1;
    // life.currState[14][30] = 1;
    //
    // life.currState[15][26] = 1;
    // life.currState[15][30] = 1;
    //
    // life.currState[16][22] = 1;
    // life.currState[16][23] = 1;
    // life.currState[16][24] = 1;
    // life.currState[16][25] = 1;
    // life.currState[16][27] = 1;
    // life.currState[16][28] = 1;
    // life.currState[16][30] = 1;
    //
    // life.currState[17][22] = 1;
    // life.currState[17][25] = 1;
    // life.currState[17][27] = 1;
    // life.currState[17][29] = 1;
    // life.currState[17][31] = 1;
    // life.currState[17][32] = 1;
    //
    // life.currState[18][25] = 1;
    // life.currState[18][27] = 1;
    // life.currState[18][29] = 1;
    // life.currState[18][31] = 1;
    //
    // life.currState[19][26] = 1;
    // life.currState[19][27] = 1;
    // life.currState[19][29] = 1;
    // life.currState[19][31] = 1;
    //
    // life.currState[20][30] = 1;
    //
    // life.currState[23][16] = 1;
    // life.currState[23][17] = 1;
    //
    // life.currState[24][17] = 1;
    // life.currState[24][24] = 1;
    // life.currState[24][25] = 1;
    //
    // life.currState[25][17] = 1;
    // life.currState[25][19] = 1;
    // life.currState[25][20] = 1;
    //
    // life.currState[26][18] = 1;
    // life.currState[26][20] = 1;
    // life.currState[26][21] = 1;
    // life.currState[26][23] = 1;
    //
    // life.currState[33][28] = 1;
    // life.currState[33][29] = 1;
    //
    // life.currState[34][29] = 1;
    // life.currState[34][20] = 1;
    //
    // life.currState[35][18] = 1;
    // life.currState[35][20] = 1;
    // life.currState[35][23] = 1;
    //
    // life.currState[36][19] = 1;
    // life.currState[36][20] = 1;
    // Rastgele başlangıç seti

    // Sol üstte bir glider
    life.currState[2][3] = 1;
    life.currState[3][4] = 1;
    life.currState[4][2] = 1;
    life.currState[4][3] = 1;
    life.currState[4][4] = 1;

    // OrcurrSa sol bir lightweight spaceship (LWSS)
    life.currState[10][5] = 1;
    life.currState[11][6] = 1;
    life.currState[11][7] = 1;
    life.currState[11][8] = 1;
    life.currState[10][8] = 1;
    life.currState[9][8] = 1;
    life.currState[9][7] = 1;

    // OrcurrSada bir toad osilatör
    life.currState[25][25] = 1;
    life.currState[25][26] = 1;
    life.currState[25][27] = 1;
    life.currState[26][24] = 1;
    life.currState[26][25] = 1;
    life.currState[26][26] = 1;

    // SacurrS altta bir beacon
    life.currState[40][40] = 1;
    life.currState[40][41] = 1;
    life.currState[41][40] = 1;
    life.currState[41][41] = 1;
    life.currState[42][42] = 1;
    life.currState[42][43] = 1;
    life.currState[43][42] = 1;
    life.currState[43][43] = 1;

    // SacurrS üstte rastgele bir glider gun başlangıcı
    life.currState[5][30] = 1;
    life.currState[5][31] = 1;
    life.currState[6][30] = 1;
    life.currState[6][31] = 1;
    life.currState[4][34] = 1;
    life.currState[4][35] = 1;
    life.currState[5][33] = 1;
    life.currState[6][36] = 1;
    life.currState[7][35] = 1;

    return life;
}


//endregion

void createEntitySquares(vec4 winSize, app& context) {
    int squareWidth = 10;
    int squareHeight = 10;
    int hor_Count = winSize.x / squareWidth;
    int vert_Count = winSize.y / squareHeight;

    for (int i = 0; i < hor_Count; i++)
    {
        for (int j = 0; j < vert_Count; j++)
        {
            Entity entity;
            entity.addComponent<PositionComp>(Position, i*(float)squareWidth, j*(float)squareHeight);
            entity.addComponent<SizeComp>(Size, (float)squareWidth, (float)squareHeight);
            entity.addComponent<ColorComp>(Color, vec4(1.0f, 1.0f, 1.0f, 1.0f));

            context.addEntity(entity);
        }
    }
}
lifeStruct gof;
int app::init()
{
    //ourShader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //ourShader.use();
    vec4 windowSize = engine.getWindowSize();
    auto* shader = new Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    //Shader shader = Shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    engine.ecs_renderer = new Renderer(*shader);
    engine.ecs_renderer->windowSize = windowSize;
    createEntitySquares(windowSize, *this);

    gof = createLife(windowSize);

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

    if(updateCount++ > 100)
    {
        //SDL_Delay(1000.f / maxFPS - frameTicks);
        //updateLife(gof);
        updateCount = 0;
    }

    vec4 winSize = engine.getWindowSize();

    int squareWidth = 10;
    int squareHeight = 10;
    int hor_Count = winSize.x / squareWidth;
    int vert_Count = winSize.y / squareHeight;

    float speed = 1.0f;
    float time = (startTicks2 / 1000.0f) * speed;


    /*for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            auto* color = entities[i*50 + j].getComponent<ColorComp>(Color);
            color->color = gof.currState[i][j] ? vec4(0.0f, 1.0f, 0.0f, 1.0f) : vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }*/

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