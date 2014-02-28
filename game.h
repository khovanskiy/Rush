#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

#include "statecontext.h"
#include "graphiccore.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    ~Game();
private:
    StateContext* state_context;
    QTimer* loop;
    QElapsedTimer* counter;
    int TICKS_PER_SECOND;
    int SKIP_TICKS;
    int MAX_FRAMESKIP;
    long next_game_tick;
    int loops;
    float interpolation;
    qint64 ticksCount();
    bool new_frame, old_state;
private slots:
    void onLoop();
};

#endif // GAME_H
