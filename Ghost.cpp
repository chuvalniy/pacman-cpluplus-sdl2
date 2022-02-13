#include "Ghost.h"

Ghost::Ghost(unsigned char m_ghostId, SDL_Renderer *ren)
{
    ghostId = m_ghostId;
    renderer = ren;
}

Ghost::~Ghost()
{

}


void Ghost::reset(const Vector2 &m_Home, const Vector2 &m_HomeExit)
{
    debuffGhost = SpriteLoader::loadTexture("ghost_fear.png", renderer);
    yellowGhost = SpriteLoader::loadTexture("ghost1.png", renderer);
    redGhost = SpriteLoader::loadTexture("ghost2.png", renderer);
    blueGhost = SpriteLoader::loadTexture("ghost3.png", renderer);
    pinkGhost = SpriteLoader::loadTexture("ghost4.png", renderer);

    moveState = 0;
    moveDir = 0;
    debuffState = 0;
    debuffStateTimer = 0;
    openDoor = 0 < ghostId;
    srcRect = { 0, 0, 16, 16 };

    Home = m_Home;
    HomeExit = m_HomeExit;
    Target = m_HomeExit;
}

void Ghost::switchMode()
{
    moveState = 1 - moveState;
}

void Ghost::render(bool isVanishing)
{
    SpriteLoader::applyTexture(Position.x, Position.y, renderer, texture, &srcRect);
    // Текущий кадр анимации
    unsigned char bodyFrame = static_cast<unsigned char>(floor(animationTimer / static_cast<float>(GHOST_ANIMATION_SPEED)));

    // У призраков отдельно отслеживаются анимации головы и тела
    SDL_Rect face;
    SDL_Rect body;

    // Установка новой анимации в зависимости от текущего кадра
    body.x = CELL_SIZE * bodyFrame;
    body.y = 0;
    body.h = CELL_SIZE;
    body.w = CELL_SIZE;

    // Если призрак в обычном состоянии
    if (debuffState == 0)
    {

        face.x = CELL_SIZE * moveDir;
        face.y = CELL_SIZE;
        face.h = CELL_SIZE;
        face.w = CELL_SIZE;

        // Отрисовка всех призраков
        switch (ghostId)
        {
        case 0:
            {
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, yellowGhost, &body);
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, yellowGhost, &face);
                break;
            }
        case 1:
            {
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, redGhost, &body);
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, redGhost, &face);
                break;
            }
        case 2:
            {
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, blueGhost, &body);
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, blueGhost, &face);
                break;
            }
        case 3:
            {
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, pinkGhost, &body);
                SpriteLoader::applyTexture(Position.x, Position.y, renderer, pinkGhost, &face);
                break;
            }
        }
    }

    // Если Пакман подобрал бафф
    else if (debuffState == 1)
    {
        face.x = CELL_SIZE * 4;
        face.y = CELL_SIZE;
        face.h = CELL_SIZE;
        face.w = CELL_SIZE;


        // Когда будет близок конец баффа призраки начнут мерцать
        if (isVanishing == 1 && bodyFrame % 4)
        {
            SpriteLoader::applyTexture(Position.x, Position.y, renderer, NULL, &body);

        }
        // У всех призраков под баффом Пакмана одинаковая текстура
        else
        {
            SpriteLoader::applyTexture(Position.x, Position.y, renderer, debuffGhost, &body);
            SpriteLoader::applyTexture(Position.x, Position.y, renderer, debuffGhost, &face);
        }
    }

    // Если Пакман задел призрака под баффом
    else
    {
        // Отрисовать только лицо
        face.x = CELL_SIZE * moveDir;
        face.y = 2 * CELL_SIZE;
        face.h = CELL_SIZE;
        face.w = CELL_SIZE;
        SpriteLoader::applyTexture(Position.x, Position.y, renderer, debuffGhost, &face);
    }

    animationTimer = (1 + animationTimer) % (GHOST_ANIMATION_FRAMES * GHOST_ANIMATION_SPEED);
}

bool Ghost::pacmanCollision(const Vector2& Pacman)
{
    if (Position.x > Pacman.x - CELL_SIZE && Position.x < CELL_SIZE + Pacman.x)
    {
        if (Position.y > Pacman.y - CELL_SIZE && Position.y < CELL_SIZE + Pacman.y)
        {
            return 1;
        }
    }

    return 0;
}

float Ghost::getTargetDistance(unsigned char m_moveDir)
{
    short x = Position.x;
    short y = Position.y;

    // Мнимо передвигает призрака, чтобы получить координаты до цели
    switch (m_moveDir)
    {
        case 0: x += GHOST_SPEED; break;
        case 1: y -= GHOST_SPEED; break;
        case 2: x -= GHOST_SPEED; break;
        case 3: y += GHOST_SPEED; break;
    }

    // По теореме Пифагора считает дистанцию до цели
    return static_cast<float>(sqrt(pow(x - Target.x, 2) + pow(y - Target.y, 2)));
}

void Ghost::updateTarget(unsigned char moveDir, const Vector2 &m_Ghost, const Vector2 &Pacman)
{
    // Если призрак может использовать дверь
    if (openDoor == 1)
    {
        if (Position.x == Target.x && Position.y == Target.y)
        {
            // Если прзрак достиг выхода
            if (Target.x == HomeExit.x && Target.y == HomeExit.y)
            {
                // Он больше не может использовать дверь
                openDoor = 0;
            }
            // Если прзрак достиг дома
            else if (Home.x == Target.x && Home.y == Target.y)
            {
                debuffState = 0; // Обновить состояние призрака на обычное
                Target.x = HomeExit.x; // Обновить цель призрака снова на дверь
                Target.y = HomeExit.y;
            }
        }
    }
    else
    {
        // Если призрак в состоянии исследования
        if (moveState == 0)
        {
            // Задать каждому призраку направлению в свой угол карты
            switch (ghostId)
            {
                case 0: Target = {CELL_SIZE * (MAP_WIDTH -1), 0}; break;
                case 1: Target = {0, 0}; break;
                case 2: Target = {CELL_SIZE * (MAP_WIDTH -1 ), CELL_SIZE * (MAP_HEIGHT - 1)}; break;
                case 3: Target = {0, CELL_SIZE * (MAP_HEIGHT - 1)}; break;
            }
        }

        // Если призрак в состоянии погони за Пакманом
        else
        {
            // Каждый призрак действует индивидуально
            switch (ghostId)
            {
                case 0: Target.x = Pacman.x; Target.y = Pacman.y; break; // Призрак 0 преследует Пакмана
                case 1: // Призрак 1 преследует 4 клетку перед Пакманом
                {
                    Target.x = Pacman.x;
                    Target.y = Pacman.y;
                    switch (moveDir)
                    {
                        case 0: Target.x += CELL_SIZE * GHOST_1_CHASE; break;
                        case 1: Target.y -= CELL_SIZE * GHOST_1_CHASE; break;
                        case 2: Target.x -= CELL_SIZE * GHOST_1_CHASE; break;
                        case 3: Target.y += CELL_SIZE * GHOST_1_CHASE;
                    }
                    break;
                }
                case 2: // Призрак 2 преследует вторую клетку перед Пакманом
                {
                    Target.x = Pacman.x;
                    Target.y = Pacman.y;
                    switch (moveDir)
                    {
                        case 0: Target.x += CELL_SIZE * GHOST_2_CHASE; break;
                        case 1: Target.y -= CELL_SIZE * GHOST_2_CHASE; break;
                        case 2: Target.x -= CELL_SIZE * GHOST_2_CHASE; break;
                        case 3: Target.y += CELL_SIZE * GHOST_2_CHASE;
                    }

                    Target.x += Target.x - m_Ghost.x;
                    Target.y += Target.y - m_Ghost.y;
                    break;
                }
                case 3: // Призрак 3 преследует Пакмана до тех пор, пока не будет близок к нему.
                {
                    if (CELL_SIZE * GHOST_3_CHASE <= sqrt(pow(Position.x - Pacman.x, 2) + pow(Position.y - Pacman.y, 2)))
                    {
                        Target.x = Pacman.x;
                        Target.y = Pacman.y;
                    }
                    else
                    {
                        Target.x = 0;
                        Target.y = CELL_SIZE * (MAP_HEIGHT - 1);
                    }

                }
            }
        }
    }
}

void Ghost::update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& ghost, Pacman& pacman)
{
    bool canMove = 0;

    // Если доступных путей больше 1, то это означает, что призрак достиг перекрестка
    // Призраки не могут двигаться назад
    unsigned char availableWays = 0;
    unsigned char speed = GHOST_SPEED;

    // Если Пакман подобрал бафф, то установи новое состояние призраку
    if (debuffState == 0 && pacman.getPowerTimer() == POWER_TIME / pow(2, level))
    {
        debuffStateTimer = DEBUFF_SPEED;
        debuffState = 1;
    }

    // Если у Пакмана закончился бафф, то смени состояние призраку
    else if (pacman.getPowerTimer() == 0 && debuffState == 1)
    {
        debuffState = 0;
    }

    // Если Пакман задел призрака под баффом, то задай призраку новую скорость
    if (debuffState == 2 && Position.x % DEBUFF_SPEED == 0 && Position.y % DEBUFF_SPEED == 0)
    {
        speed = DEBUFF_SPEED;
    }

    // Обновить цель призрака
    updateTarget(pacman.getDirection(), ghost.getPosition(), pacman.getPosition());

    // Проверить на коллизию все четыре стороны
	walls[0] = checkCollision(0, 0, openDoor, 1 + Position.x, Position.y, i_map);
	walls[1] = checkCollision(0, 0, openDoor, Position.x, Position.y - 1, i_map);
	walls[2] = checkCollision(0, 0, openDoor, Position.x - 1, Position.y, i_map);
	walls[3] = checkCollision(0, 0, openDoor, Position.x, 1 + Position.y, i_map);

	// Если призрак находится не в состоянии беспокойства (Пакман подобрал бафф, но не задевал призрака)
	if (debuffState != 1)
    {
        unsigned char optimalMoveDir = 4;

        // Разрешить двигаться призраку
        canMove = 1;


        // В цикле определяет самое выгодное направление для призрака
        for (unsigned char i = 0; i < 4; i++)
        {
            // Призрак не может развернуться назад
            if (i == (2 + moveDir) % 4)
            {
                continue;
            }

            // Проверка на коллизию в завимимости от направления
            else if (walls[i] == 0)
            {
                if (optimalMoveDir == 4)
                {
                    optimalMoveDir = i;
                }

                availableWays++;

                if (getTargetDistance(i) < getTargetDistance(optimalMoveDir))
                {
                    // Установить самое выгодное направление
                    optimalMoveDir = i;
                }
            }
        }

        // Если призрак достиг перекрестка
        if (availableWays > 1)
        {
            // Он выберет самое выгодное направление
            moveDir = optimalMoveDir;
        }

        else
        {
            if (optimalMoveDir == 4)
            {
                // Призрак пойдет назад в случае отсутствия другого выбора
                moveDir = (2 + moveDir) % 4;
            }
            else
            {
                moveDir = optimalMoveDir;
            }
        }
    }

    // При состоянии беспокойства призраки двигаются в случайном направлении
    else
    {
        // Задать случайное направление
        unsigned char randomDir = rand() % 4;

        if (debuffStateTimer == 0)
        {
            canMove = 1;
            debuffStateTimer = DEBUFF_SPEED;

            for (unsigned char i = 0; i < 4; i++)
            {
                if (i == (2 + moveDir) % 4)
                {
                    // Двигаться назад нельзя
                    continue;
                }
                // Если по текущему проходу в цикле нет коллизии со стеной
                else if (walls[i] == 0)
                {
                    // Добавить возможные пути
                    availableWays++;
                }
            }

            if (availableWays > 0)
            {
                // До тех пор пока случайное направление выдает путь назад или пока в направлении есть стена
                while (walls[randomDir] == 1 || randomDir == (2 + moveDir) % 4)
                {
                    // Задавать новое случайное направление
                    randomDir = rand() % 4;
                }

                moveDir = randomDir;
            }

            else
            {
                // Если нет пути, развернуть призрака назад
                moveDir = (2 + moveDir) % 4;
            }
        }

        else
        {
            debuffStateTimer--;
        }
    }

    // Двигать призрака
    if (canMove == 1)
    {
        switch (moveDir)
        {
            case 0: Position.x += speed; break;
            case 1: Position.y -= speed; break;
            case 2: Position.x -= speed; break;
            case 3: Position.y += speed; break;
        }

        // Когда призрак покидает карту, задать ему координаты другой стороны
        if (-CELL_SIZE >= Position.x)
        {
            Position.x = CELL_SIZE * MAP_WIDTH - speed;
        }
        else if (Position.x >= CELL_SIZE * MAP_WIDTH)
        {
            Position.x = speed - CELL_SIZE;
        }
    }

    // Если призрак задел Пакмана
    if (pacmanCollision(pacman.getPosition()) == 1)
    {
        // Если призрак в нормальном состоянии - закончить игру
        if (debuffState == 0)
        {
            pacman.setDead(1);
        }
        // Иначе отправить призрака домой
        else
        {
            openDoor = 1;
            debuffState = 2;
            Target = Home;
        }
    }
}
