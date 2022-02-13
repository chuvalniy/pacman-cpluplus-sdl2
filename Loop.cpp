#include "Loop.h"
#include "Global.h"
#include "Game.h"

void MainLoop()
{
    Game* game = new Game();

    game->init();
    game->reset();

    const unsigned int frameDelay = 1000 / FRAMES_PER_SECOND;

    Uint32 frameStart;
    int frameTime;

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    delete game;
	SDL_Quit();
}
