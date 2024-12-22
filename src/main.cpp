#include "app.h"

app game_app;

int main()
{
    printf("INIT SUCCESSSSSSSSSS 2 ");
    int success = game_app.start(640, 360);
    if(success)
    {
        printf("INITIALIZE FAILED");
        return EXIT_FAILURE;
    }

    game_app.init();

    while (!game_app.quit)
    {
        game_app.update();
        game_app.draw();
    }

    game_app.kill();
    return EXIT_SUCCESS;
}