#include "game.h"

Game::Game()
{
    state_context = new StateContext();
    counter = new QElapsedTimer();
    loop = new QTimer();
    connect(loop, SIGNAL(timeout()), this, SLOT(onLoop()));

    TICKS_PER_SECOND = 20;
    SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    MAX_FRAMESKIP = 5;
    counter->start();
    new_frame = false;
    next_game_tick = ticksCount();
    loop->start(0);
}

void Game::onLoop()
{
    loops = 0;

    old_state = new_frame;

    if (ticksCount() > next_game_tick)
    {
        new_frame = true;
    }
    else
    {
        new_frame = false;
    }

    GraphicCore::gi()->render(new_frame, interpolation);


    while (ticksCount() > next_game_tick && loops < MAX_FRAMESKIP)
    {
        state_context->tick(1.0 / TICKS_PER_SECOND);
        //new_frame = true;
        next_game_tick += SKIP_TICKS;
        loops++;
    }

    interpolation = (float)(ticksCount() + SKIP_TICKS - next_game_tick) / (float)(SKIP_TICKS);
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


