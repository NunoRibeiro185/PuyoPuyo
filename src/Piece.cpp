#include "Piece.h"
#include "Utils.h"

/**
    Constructor
*/
Piece::Piece(){
	x = 0;
	y = 0;
	color = COLOR_BLACK;
	free = true;
	moving = false;
	pivot = false;
	read = false;
	falling = false;
}


/**
    Reset the block to the default values

	@param void
    @return void
*/
void Piece::Reset(){
	color = COLOR_BLACK;
	free = true;
	moving = false;
	pivot = false;
	read = false;
	falling = false;
}


/**
    Copy properties from a block (Clone)

	@param Block (A Block class)
    @return void
*/
void Piece::Clone(Piece piece){
	color = piece.color;
	free = piece.free;
	moving = piece.moving;
	pivot = piece.pivot;
	read = piece.read;
	falling = piece.falling;
}
