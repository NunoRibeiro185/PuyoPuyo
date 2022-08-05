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
    tick = 850;

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
    

    last_tick = UtilsTime();

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
                board.DropNewPiece();
                board.Draw();
                board.state = FALLING_PIECE;
                break;
            case FALLING_PIECE:
                board.UpdateFalling();
                board.state = WAITING;
                break;

            case WAITING:
            case PRESSING_KEY:
                if(e.type == SDL_QUIT){
                    board.state = EXIT;
                }
                
                if(e.type == SDL_KEYUP){
                    SDL_FlushEvent(SDL_KEYDOWN);
                }

                if(e.type == SDL_KEYDOWN){

                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        board.state = EXIT;
                    }

                    if(board.keyboard){
                        board.PlayerInput(e.key.keysym.sym);
                    }
                    else{ //Fall fast if only one
                        last_tick = 0;
                    }
                }


                if(UtilsTime() - last_tick >= tick && board.state != DELETING_PIECES){
                    board.PlayerInput(SDLK_s);
                    last_tick = UtilsTime();
                }
                break;
            case SORTING_PIECES:
                if(!board.keyboard){
                    last_tick = 0;
                }
                if(UtilsTime() - last_tick > 300){
                    if(!board.UpdateFalling2()){
                        board.state = DELETING_PIECES;
                        board.SearchPuyos();
                    }
                    last_tick = UtilsTime();
                }
                break;
            case DELETING_PIECES:
                if(board.ClearConnectedPieces()){
                    board.state = SORTING_PIECES;
                }
                else{
                    board.DropNewPiece();
                    board.state = WAITING;
                }
                break;

            case EXIT:
                running = false;
                break;

            case GAMEOVER:
                board.GameOver();
                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_RETURN){
                        board.state = STARTING;
                        board.Reset();
                    }
                }
                break;

            case PAUSE:
                board.Pause();
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
