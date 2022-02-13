#include <SDL.h>
#include "Loop.h"
#include "SDL_Handler.h"
#include "Game.h"
#include "Timer.h"

void Loop::Run()
{
    bool quit = false;

    SDL_Handler handler;

    // Основной класс с логикой игры
    Game game;

    Timer fps;

    int frame = 0;

    bool cap = true;

    Vector2 mousePosition;

    handler.Update();

    while (!quit)
    {
        // Просчет кадров
        fps.Start();

        while (SDL_PollEvent(&handler.event))
        {
            switch (handler.event.type)
            {
                case SDL_QUIT:
                {
                    quit = true;
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {
                    // Отслеживание нажатия мыши для взаимодействия с меню
                    mousePosition = { handler.event.button.x, handler.event.button.y };

                    game.SetMousePosition(mousePosition.x, mousePosition.y);

                    game.HandleMouseButtonKey();
                    break;
                }

                case SDL_KEYDOWN:
                {
                    // Отслеживание нажатий по клавиатуре
                    switch (handler.event.key.keysym.sym)
                    {
                        case SDLK_p: game.PauseGame(); break; // Пауза во время игры
                        case SDLK_UP: game.HandleMoveUpKey(); break;
                        case SDLK_DOWN: game.HandleMoveDownKey(); break;
                        case SDLK_LEFT: game.HandleMoveLeftKey(); break;
                        case SDLK_RIGHT: game.HandleMoveRightKey(); break;
                        case SDLK_ESCAPE: game.HandleEscapeKey(); break; // Выход в главное меню
                        default: break;
                    }
                    break;

                }
                default: break;
            }
        }

        frame++;

        // Рендер происходит только в игровом режиме
        if (game.State == InGame)
        {
            game.Render();
        }

        // Осуществление выхода из игры путем нажатия на кнопку Exit в меню.
        else if (game.State == Exit)
        {
            quit = true;
        }

        // Обвноление экрана
        handler.Update();

        if ( (cap == true) && (fps.getTicks() < 1000 / FPS) )
        {
            SDL_Delay( (1000 / FPS) - fps.getTicks());
        }

    }

    handler.cleanUp();

}

