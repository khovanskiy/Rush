#include "game.h"

Game::Game()
{
    state_context = new StateContext();
    counter = new QElapsedTimer();
    loop = new QTimer();
    connect(loop, SIGNAL(timeout()), this, SLOT(onLoop()));

<<<<<<< HEAD
    TICKS_PER_SECOND = 20;
=======
    TICKS_PER_SECOND = 25;
>>>>>>> origin/physicsDebug
    SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    MAX_FRAMESKIP = 5;
    counter->start();

    next_game_tick = ticksCount();
    loop->start(0);
}

void Game::onLoop()
{
    loops = 0;
    while (ticksCount() > next_game_tick && loops < MAX_FRAMESKIP)
    {
        state_context->tick(1.0 / TICKS_PER_SECOND);
        next_game_tick += SKIP_TICKS;
        loops++;
    }
    interpolation = (float)(GetTickCount() + SKIP_TICKS - next_game_tick) / (float)(SKIP_TICKS);
    GraphicCore::gi()->render(interpolation);
}

qint64 Game::ticksCount()
{
    return counter->elapsed();
}

Game::~Game()
{
    loop->stop();
    delete state_context;
    delete loop;
}


