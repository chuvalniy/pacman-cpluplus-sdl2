#include "SDL_Handler.h"

bool SDL_Handler::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }

    screen = SDL_SetVideoMode(MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if (screen == NULL)
    {
        return false;
    }

    SDL_WM_SetCaption("Pacman    Belyaev", NULL);

    return true;
}

bool SDL_Handler::Update()
{
    if (SDL_Flip(screen) == -1)
    {
        return false;
    }
    return true;
}

void SDL_Handler::cleanUp()
{
    SDL_FreeSurface(screen);

    TTF_Quit();

    SDL_Quit();
}

SDL_Handler::SDL_Handler()
{
    init();
}


SDL_Handler::~SDL_Handler()
{
    cleanUp();
}

void SDL_Handler::ChangeVideoMode(unsigned char videoMode)
{
    // Если находимся в меню
    if (videoMode == 0)
    {
        screen = SDL_SetVideoMode(MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    }
    // Если находимся в игровом режиме
    else if (videoMode == 1)
    {
        screen = SDL_SetVideoMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    }
}

// Функция загрузки оптимизированных картинок
SDL_Surface *SDL_Handler::loadImage(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if (loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

// Функция для отображения поверхности
void SDL_Handler::applySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    offset.h = CELL_SIZE;
    offset.w = CELL_SIZE;

    SDL_BlitSurface(source, clip, destination, &offset);
}

