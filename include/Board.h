#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Piece.h"
#include "Utils.h"
#include <iostream>
#include <vector>


static const int MARGIN = 10;
static const int PUYO_WIDTH = 58;
static const int PUYO_HEIGHT = 58;

enum Direction{ LEFT=0, RIGHT, UP, DOWN};
enum State { STARTING=0, PAUSE, GAMEOVER, EXIT, WAITING, PRESSING_KEY, SORTING_PIECES, DELETING_PIECES};

class Board {
    public:
    State state;
    State saved_state;
    bool keyboard;

    Board();
    Board(int,int);

    void Init();
    void Init(SDL_Renderer*);
    void Reset(const int, const int);
    void Reset();

    void Draw();
	void DrawScreenBoard();

    int* WindowSize();

    void PlayerInput(SDL_Keycode);
    void Move(Piece, int);

    void DropNewPiece();
    bool UpdateFalling();

    void DrawPieces(Piece, SDL_Color);
    void RedrawPieces(Piece, Piece);

    bool SearchPuyos();
    bool ClearConnectedPieces();
    void FindConnected(Piece &);

    // 
    void CalcScreenSize();
    void SetRenderer(SDL_Renderer*);

    
    private:
    int cols, rows;
    int width_px, heigth_px;
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Renderer* renderer;

    std::vector<Piece> pieces;
    std::vector<Piece> connected_pieces;
    std::vector<std::vector<Piece>> pieces_erase;

    Piece **board;
    bool IsPieceFalling();
};

#endif //BOARD_H