#include "Game.h"
#include "Utils.h"
#include <iostream>

Game::Game(int cols, int rows){
    //Init Board
    board = Board(cols, rows);
    printf("cols: %i, rows: %i\n", cols, rows);
    int* size = board.WindowSize();
    window_w = size[0];
    window_h = size[1];
}

void Game::GameStart(){
    //Main loop variable
    running = true;
    
    //Pause variable
    bool pause = false;

    //Ticks
    tick = 750;

    UtilsRandInit();

    printf("Going to Start SDL\n");
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL could not be initialized!\n"
                        "SDL_Error: %s\n", SDL_GetError());
        return;
    }
    printf("We have SDL!\n");
     // Create Window
     SDL_Window *window = SDL_CreateWindow("PuyoPuyo",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            window_w, window_h,
                                            SDL_WINDOW_SHOWN);

    if(!window){
        fprintf(stderr, "Window could not be created!\n"
                        "SDL_Error: %s\n", SDL_GetError());
    } 
    printf("Oh look a window!\n");
    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "Renderer could not be created!\n"
                        "SDL_Error: %s\n", SDL_GetError());
    }
    printf("Renderer it is!\n");
    

    last_tick = SDL_GetTicks();

    FPSmanager fpsmanager;
    SDL_initFramerate(&fpsmanager);
    SDL_setFramerate(&fpsmanager, 30);


    //Main Loop
    while (running)
    {
        SDL_Event e;

        if(SDL_PollEvent(&e)){
            //Check if Quit
            if(e.type == SDL_QUIT){
                board.state = EXIT;
            }
            else if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    board.state = EXIT;
                    break;
                case SDLK_p:
                    if(!pause){
                        board.saved_state = board.state;
                        board.state = PAUSE;
                        pause = true;
                    }
                    else{
                        board.state = board.saved_state;
                        pause = false;
                    }
                
                default:
                    break;
                }
            }
        }
    
        //State Machine
        switch (board.state){
            case STARTING:
                //Init screen
                board.Init(renderer);
                board.DropNewPiece(); //Drop first piece
                board.Draw();
                board.state = WAITING;
                break;
            case WAITING:
            case PRESSING_KEY:
                if(e.type == SDL_QUIT){ //click x on the window
                    board.state = EXIT; //Exit game
                }
                
                if(e.type == SDL_KEYDOWN){

                    if(e.key.keysym.sym == SDLK_ESCAPE){ //press escape
                        board.state = EXIT; // Exit game
                    }

                    if(board.keyboard){
                        board.PlayerInput(e.key.keysym.sym);
                    }
                    else{ //Fall fast if only one || Feature disabled
                        last_tick = 0;
                    }
                }

                if(SDL_GetTicks() - last_tick >= tick && board.state != DELETING_PIECES){
                    board.PlayerInput(SDLK_s); //Move active pieces down = pressing the S key
                    last_tick = SDL_GetTicks();
                }
                break;
            case SORTING_PIECES:
                if(!board.keyboard){
                    last_tick = 0; //Pieces fall faster || Feature disabled
                }
                if(SDL_GetTicks() - last_tick > 300){
                    if(!board.UpdateFalling()){
                        board.state = DELETING_PIECES;
                        board.SearchPuyos(); //find groups of 4+ pices aka Puyos
                    }
                    last_tick = SDL_GetTicks();
                }
                break;
            case DELETING_PIECES:
                if(board.ClearConnectedPieces()){ //delete groups of 4+ pieces
                    board.state = SORTING_PIECES; //Resort that pieces in case some were destroyed
                }
                else{
                    board.keyboard = true; //Make sure player can use keyboard when new piece drops
                    board.DropNewPiece(); //If nothing to be destroyed drop a new piece
                    board.state = WAITING;
                }
                break;

            case EXIT:
                running = false;
                break;

            case GAMEOVER:
                //Insert Game Over Screen
                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_RETURN){
                        board.state = STARTING;
                        board.Reset(); //Reset board and start over
                    }
                }
                break;

            case PAUSE:
                //Insert Pause Menu 
                break;

            default:
                break;
        }

        if(board.state != GAMEOVER && board.state != PAUSE){
            board.Draw();
        }

        SDL_RenderPresent(renderer);

        SDL_framerateDelay(&fpsmanager);
    }
}
