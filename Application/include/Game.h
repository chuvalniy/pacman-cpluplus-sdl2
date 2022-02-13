#ifndef GAME_H
#define GAME_H

#include <array>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <SDL_ttf.h>
#include "Collision.h"
#include "GhostManager.h"
#include "Global.h"
#include "SDL_Handler.h"
#include "Hero.h"
#include "Enemy.h"


class Game
{
public:

    Game();

    // Загрузка меню игры
    void LoadMenu();

    // Рендер игрового режима
    void Render();

    // Пауза игры
    void PauseGame();

    // Загружает необходимые ресурcы для игрового режима при нажатии на кнопку Play в меню
    void LoadGame();

    // Выбор игрового уровня в меню
    void SelectLevel();

    // Заполняет карту
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> PopulateBlocks(const std::array<std::string, MAP_HEIGHT>& m_mapSketch);

    // Загружает игровую карту
    void DrawMap(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& m_map);

    // Загрузка таблица лидеров в меню
    void LoadLeaderboard();

    // Передвижение персонажа
    void HandleMoveUpKey();
    void HandleMoveDownKey();
    void HandleMoveLeftKey();
    void HandleMoveRightKey();

    // Обработки левого клипа мыши
    void HandleMouseButtonKey();

    // Выход в главное меню
    void HandleEscapeKey();

    // Отображение количества очков во время игры
    void PrintScore();

    // Добавляет  и сортирует очки по окончанию игрового режима
    void AddScore(unsigned short score);

    // Сохраняет игровые очки в файл
    void SaveScoreFile();

    // Открывает файл с игровыми очками
    void OpenScoreFile();

    // Устанавливает позицию мыши
    void SetMousePosition(short i_x, short i_y);

    GameState State;

private:

    SDL_Handler handler;

    // Поверхность для отображения меню
    SDL_Surface *menu;
    // Поверхность для отображения текстур карты
    SDL_Surface *texture;
    // Поверхность для отображения экрана поражения
    SDL_Surface *gameover;
    // Поверхность для отображения экрана победы
    SDL_Surface *winscreen;

    // Поверхность для отображения сообщения о паузе игры
    SDL_Surface *pauseMessage;
    // Поверхность для отображения сообщения о количестве текущих очков
    SDL_Surface *scoreMessage;

    TTF_Font *font;
    SDL_Color textColor;

    SDL_Rect rect_menu;

    Vector2 mousePos;

    Hero pacman;
    GhostManager manager;

    // Путь к файлам с игровыми уровнями
    std::string levelPath;

    // Основная игровая карта
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> worldMap {};

    // Переменная для заполнения игровой карты клетками (enum Cell)
    std::array<std::string, MAP_HEIGHT> mapSketch {};

    std::array<Vector2, 4> ghostPosition;

    std::array<unsigned short, 11> playerScores;


    bool level;
    bool isVictory;
    bool isPaused;

};

#endif
