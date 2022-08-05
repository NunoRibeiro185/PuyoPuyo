#include <SDL.h>
#include <iostream>
#include "Game.h"

// Define screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


int main(int argc, char* argv []){
    // unused argc, argv
    (void) argc;
    (void) argv;

   

    int COLS = 8;
    int ROWS = 16;

    //Start the game
    Game game(COLS,ROWS);

    //Initialize everything to start
    game.GameStart();    

    //Quit SDL
    SDL_Quit();

    return 0;
}