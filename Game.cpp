#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
    cleanUp();
}

void Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        isRunning = false;
    }
    else
    {
        window = SDL_CreateWindow("Pacman Belyaev", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            isRunning = false;
        }
        else
        {
            printf("Window created...\n");
            screen = SDL_GetWindowSurface(window);
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == NULL)
        {
            isRunning = false;
        }
        else
        {
            printf("Renderer created...\n");
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                isRunning = false;
            }
        }

        isRunning = true;
    }

    pacman = new Pacman(renderer);
    map = new Map("map.png", renderer);
    ghostManager = new GhostManager(renderer);
}

void Game::reset()
{
    mapLoader =
    {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};
    pacman->reset();
    worldMap = map->loadMap(mapLoader, pacman, ghostPosition);
    ghostManager->reset(0, ghostPosition);

}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                isRunning = false;
                break;
            }

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_p: break;
                    case SDLK_UP: pacman->moveUp(); break;
                    case SDLK_DOWN: pacman->moveDown(); break;
                    case SDLK_LEFT: pacman->moveLeft(); break;
                    case SDLK_RIGHT: pacman->moveRight(); break;
                    case SDLK_ESCAPE: break;
                    default: break;
                }
            }
            default:
                break;
        }
    }
}

bool Game::running()
{
    return isRunning;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    map->drawMap(worldMap);
    ghostManager->render(0);
    pacman->render(isVictory);

    SDL_RenderPresent(renderer);
}

void Game::update()
{
    pacman->update(0, worldMap);
    ghostManager->update(0, worldMap, *pacman);
}

void Game::cleanUp()
{
    delete pacman;
    delete map;
}
