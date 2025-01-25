#include "app.h"

int main()
{
    app game_app = app();
    printf("INIT SUCCESSSSSSSSSS 2 ");
    int success = game_app.start(1000, 1000);
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