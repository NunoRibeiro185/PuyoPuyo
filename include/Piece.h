#ifndef PIECE_H
#define PIECE_H

#include <SDL.h>

class Piece{
    public:
    	int x, y;
		SDL_Color color;
		bool free;
		bool moving;
		bool read;
		bool falling;
		bool pivot;

		// Constructor
		Piece();

		//Reset the block to the default values
		void Reset();

		//Copy properties from a block (Clone)
		void Clone(Piece);
};

#endif