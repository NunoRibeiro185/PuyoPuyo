#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>

//include board
#include "Board.h"

class Game {
public:
    Board board;

    Game();
    Game(int,int);

    void GameStart();

private:
    int window_w, window_h;
    Uint32 last_tick;
    Uint32 tick;
    bool running;
};

#endif //GAME_H