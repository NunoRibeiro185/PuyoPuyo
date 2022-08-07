#include "Board.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <sstream>

Board::Board(){    
}

Board::Board(const int cols, const int rows){
    Reset(cols,rows);
}

void Board::Reset(){
    Reset(this->cols, this->rows);
}


void Board::Reset(const int cols, const int rows){
	state = STARTING;
    this->cols = cols;
    this->rows = rows;

	//Define board (Logic)
	board = new Piece*[cols];
	for(int i = 0; i < cols; i++){
		board[i] = new Piece[rows];
	}

	//Initialize the board
	for(int x = 0;x < cols; x++){
		for(int y = 0;y < rows; y++){
			board[x][y].x = x;
			board[x][y].y = y;
			board[x][y].Reset();
		}
	}

	keyboard = true;
}

void Board::Init(SDL_Renderer *renderer){
    this->renderer = renderer;
	Reset();
    CalcScreenSize();
	//Draw game screen
	DrawScreenBoard();

}

int* Board::WindowSize(){
	int *size = new int[2];

	//Title uses 1 puyo height (Block)
	size[0] = (MARGIN * 2) + (PUYO_WIDTH * (cols));
	size[1] = (MARGIN * 2) + (PUYO_HEIGHT * (rows + 1) + PUYO_HEIGHT);

	return size;
}

void Board::CalcScreenSize(){
	width_px = (MARGIN * 2) + (PUYO_WIDTH * (cols ) + PUYO_WIDTH);
	heigth_px = (MARGIN * 2) + (PUYO_HEIGHT * (rows + 1) + PUYO_HEIGHT);
}

bool Board::UpdateFalling(){
	bool flag = false;
	for(int x = 0; x < cols; x++){
		for(int y = rows - 2 ; y >= 0; y--){ //Don't need to check last row as you can't fall any further
			if(board[x][y].free){
				continue;
			}
			if (board[x][y + 1].free && !board[x][y].free){
				Move(board[x][y], DOWN);
				flag = true;
			}
		}
	}
	return flag;
}

void Board::PlayerInput(SDL_Keycode key){

	pieces.clear();
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			if (board[x][y].moving){
				pieces.push_back(board[x][y]);
			}
		}
	}

	//Variable to enable/disable the keyboard to users
	keyboard = pieces.size() == 1 ? false : true;

	if (pieces.size() > 0){
		if(key == SDLK_s || key == SDLK_DOWN){ //MOVE DOWN 
			if(pieces.size() >= 2){
				Piece piece1 = pieces[0];
				Piece piece2 = pieces[1];
				if(piece1.y > piece2.y){
					Move(piece1, DOWN);
					Move(piece2, DOWN);
				}
				else{
					Move(piece2, DOWN);
					Move(piece1, DOWN);
				}
			}
			else{
				for(Piece piece : pieces){
					Move(piece, DOWN);
				}
			}
		}
		else if(key == SDLK_a || key == SDLK_LEFT){ //MOVE LEFT
			if(pieces.size() >= 2){
				Piece piece1 = pieces[0];
				Piece piece2 = pieces[1];
				if(piece1.x > piece2.x){
					Move(piece2, LEFT);
					Move(piece1, LEFT);
				}
				else{
					Move(piece1, LEFT);
					Move(piece2, LEFT);
				}
			}
		}
		else if(key == SDLK_d || key == SDLK_RIGHT){ //MOVE RIGHT
			{
				Piece piece;
				if(pieces.size() > 1){
					piece = pieces[1];
					Move(piece, RIGHT);
				}
				piece = pieces[0];
				Move(piece, RIGHT);
				
			}
		}
		else if(key == SDLK_e){ //ROTATE RIGHT
			if(pieces.size() >= 2){
				Piece pivot;
				Piece other;

				if(pieces[0].pivot){
					pivot = pieces[0];
					other = pieces[1];
				}
				else{
					pivot = pieces[1];
					other = pieces[0];
				}

				//CASE SIDE BY SIDE
				if(pivot.y == other.y){
					if(pivot.x < other.x){// IF PIVOT ON THE LEFT
						if(other.x - 1 >= 0 && other.y + 1 < rows){
							if(board[other.x - 1][other.y + 1].free ){
								RedrawPieces(board[other.x][other.y], board[other.x - 1][other.y + 1]); //MOVE OTHER TO PLACE BELLOW PIVOT
							}
						}
					}
					else if(pivot.x > other.x){// IF PIVOT ON THE RIGHT
						if(other.x + 1 < cols && other.y - 1 >= 0){
							if(board[other.x + 1][other.y - 1].free ){
								RedrawPieces(board[other.x][other.y], board[other.x + 1][pivot.y - 1]); //MOVE OTHER TO PLACE ABOVE PIVOT
							}
						}
					}
				}
				//CASE VERTICAL
				else if(pivot.x == other.x){
					if(pivot.y > other.y){ //IF PIVOT BELOW OTHER
						if(other.x + 1 < cols && other.y + 1 < rows){
							if(board[other.x + 1][other.y + 1].free){
								RedrawPieces(board[other.x][other.y], board[other.x + 1][other.y + 1]); //MOVE OTHER TO PLACE RIGHT OF PIVOT
							}
						}		
					}
					else if(pivot.y < other.y){ //IF PIVOT ABOVE OTHER
						if(other.x - 1 >= 0 && other.y - 1 >= 0){
							if(board[other.x - 1][other.y - 1].free){
								RedrawPieces(board[other.x][other.y], board[other.x - 1][other.y - 1]); //MOVE OTHER TO PLACE LEFT OF PIVOT
							}
						}
					}
				}
			}
		}
		else if(key == SDLK_q){ //ROTATE LEFT
			if(pieces.size() >= 2){
				Piece pivot;
				Piece other;

				if(pieces[0].pivot){
					pivot = pieces[0];
					other = pieces[1];
				}
				else{
					pivot = pieces[1];
					other = pieces[0];
				}

				//CASE SIDE BY SIDE
				if(pivot.y == other.y){
					if(pivot.x < other.x){// IF PIVOT ON THE LEFT
						if(other.x - 1 >= 0 && other.y - 1 >= 0){
							if(board[other.x - 1][other.y - 1].free){
								RedrawPieces(board[other.x][other.y], board[other.x - 1][other.y - 1]); //MOVE OTHER TO PLACE ABOVE PIVOT
							}
						}
					}
					else if(pivot.x > other.x){// IF PIVOT ON THE RIGHT
						if(other.x + 1 < cols && other.y + 1 < rows){
							if(board[other.x + 1][other.y + 1].free){
								RedrawPieces(board[other.x][other.y], board[other.x + 1][pivot.y + 1]); //MOVE OTHER TO PLACE BELLOW PIVOT
							}
						}
					}
				}
				//CASE VERTICAL
				else if(pivot.x == other.x){
					if(pivot.y > other.y){ //IF PIVOT BELLOW OTHER
						if(other.x - 1 >= 0 && other.y + 1 < rows){
							if(board[other.x - 1][other.y + 1].free){
								RedrawPieces(board[other.x][other.y], board[other.x - 1][other.y + 1]); //MOVE OTHER TO PLACE LEFT OF PIVOT
							}
						}
					}
					else if(pivot.y < other.y){ //IF PIVOT ABOVE OTHER
						if(other.x + 1 < cols && other.y - 1 >= 0){
							if(board[other.x + 1][other.y - 1].free){
							RedrawPieces(board[other.x][other.y], board[other.x + 1][other.y - 1]); //MOVE OTHER TO PLACE RIGHT OF PIVOT
							}
						}
					}
				}
			}
		}
	}
	else{
		//If there are not blocks in movement, check if there are something to erase (Combos)
		if (SearchPuyos()){
			state = DELETING_PIECES;
		}
		else{
			//If there are nothing to erase, start other piece from the top
			DropNewPiece();
			if (state != GAMEOVER)
				state = WAITING;
		}
	}
	SDL_FlushEvent(SDL_KEYDOWN);
}

void Board::Move(Piece piece, int direction){
	if(direction == DOWN){ //Move Down
		if (piece.y + 1 < rows && board[piece.x][piece.y + 1].free){
			RedrawPieces(piece, board[piece.x][piece.y + 1]);
		}
		else{
			board[piece.x][piece.y].falling = false;
			board[piece.x][piece.y].moving = false;
		}
	}
	else if(direction == RIGHT){ //Move Right
		if (!keyboard){
			return;
		}
		if(piece.x + 1 < cols && board[piece.x + 1][piece.y].free){
			RedrawPieces(piece,board[piece.x + 1][piece.y]);
		}

	}
	else if(direction == LEFT){ //Move Left
		if (!keyboard){
			return;
		}
		if(piece.x - 1 >= 0 && board[piece.x - 1][piece.y].free){
			RedrawPieces(piece,board[piece.x - 1][piece.y]);
		}
	}
}

bool Board::SearchPuyos(){
	bool deleting = false;
	for(int x = 0; x < cols; x++){
		for(int y = rows - 1; y >= 0; y--){
			if(!board[x][y].free){
				FindConnected(board[x][y]);
				if(connected_pieces.size() >= 4){
					deleting = true;
					pieces_erase.push_back(connected_pieces);
				}
				else{
					for (Piece p : connected_pieces){
						board[p.x][p.y].read = false;
					}
				}
				connected_pieces.clear();
			}
		}
	}
	return deleting;
}

void Board::FindConnected(Piece &p){ //Recursive function to find connections

	if(!board[p.x][p.y].read){ //PIece being checked
		board[p.x][p.y].read = true;
		connected_pieces.push_back(board[p.x][p.y]);
	}
	//Check surroundings (4 directions - up, down, left , right)
	if(p.x + 1 < cols && !board[p.x + 1][p.y].free && !board[p.x + 1][p.y].read){ //Check right of current piece
		if(UtilsEqualColors(board[p.x + 1][p.y].color,p.color)){
			board[p.x + 1][p.y].read = true;
			connected_pieces.push_back(board[p.x + 1][p.y]);
			FindConnected(board[p.x + 1][p.y]);		
		}
	}

	if(p.x - 1 > 0 && !board[p.x - 1][p.y].free && !board[p.x - 1][p.y].read){ //Check left of current piece
		if(UtilsEqualColors(board[p.x - 1][p.y].color,p.color)){
			board[p.x - 1][p.y].read = true;
			connected_pieces.push_back(board[p.x - 1][p.y]);
			FindConnected(board[p.x - 1][p.y]);		
		}
	}

	if(p.y + 1 < rows && !board[p.x][p.y + 1].free && !board[p.x][p.y + 1].read){ //Check bellow of current piece
		if(UtilsEqualColors(board[p.x][p.y + 1].color, p.color)){
			board[p.x][p.y + 1].read = true;
			connected_pieces.push_back(board[p.x][p.y + 1]);
			FindConnected(board[p.x][p.y + 1]);		
		}
	}

	if(p.y - 1 > 0 && !board[p.x][p.y - 1].free && !board[p.x][p.y - 1].read){ //Check above of current piece
		if(UtilsEqualColors(board[p.x][p.y - 1].color, p.color)){
			board[p.x][p.y - 1].read = true;
			connected_pieces.push_back(board[p.x][p.y - 1]);
			FindConnected(board[p.x][p.y - 1]);		
		}
	}
}

//Drop a new piece on the board
//If cant place a new piece - GAME OVER 
void Board::DropNewPiece(){
	
	//If top row is full, game is over
	if(board[cols/2][0].free == false || board[cols/2 + 1][0].free == false ){
		state = GAMEOVER;
		return; 
	}
	//Create 2 new pieces (pair) of random colors
	if(!IsPieceFalling() && state != GAMEOVER){
		//Piece 1
		board[cols/2][0].color = UtilsRandomColor();
		board[cols/2][0].falling = true;
		board[cols/2][0].moving = true;
		board[cols/2][0].free = false;
		board[cols/2][0].pivot = false; //Rotate around this one

		//Piece 2
		board[cols/2 - 1][0].color = UtilsRandomColor();
		board[cols/2 - 1][0].falling = true;
		board[cols/2 - 1][0].moving = true;
		board[cols/2 - 1][0].free = false;
		board[cols/2 - 1][0].pivot = true; //Rotate around this one

		//Add to pieces
		pieces.push_back(board[cols/2][0]);
		pieces.push_back(board[cols/2 - 1][0]);
	}
}

bool Board::IsPieceFalling(){
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			if(board[x][y].moving){
				return true;
			}
		}
	}
	return false;
}

bool Board::ClearConnectedPieces(){
	bool flag = false;
	if(pieces_erase.size() > 0){
		std::vector<Piece> erasing = pieces_erase.back();
		pieces_erase.pop_back();

		for(Piece p: erasing){
			for(int i = 0; i < rows; i++){
				if(!board[p.x][i].free){
					board[p.x][i].falling = true;
					flag = true;
				}
			}
			board[p.x][p.y].Reset();
		}
	}
	return flag;
}


void Board::Draw(){
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			DrawPieces(board[x][y], board[x][y].color);
		}
	}
}

void Board::DrawPieces(Piece piece, SDL_Color color){
	int x = PUYO_WIDTH * piece.x;
	int y = PUYO_HEIGHT * piece.y + MARGIN;
	
	SDL_Rect Rect = {x + MARGIN, y + PUYO_HEIGHT, PUYO_WIDTH, PUYO_HEIGHT};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &Rect);

	SDL_Rect Rect2 = {x + MARGIN + 2, y + PUYO_HEIGHT + 2, PUYO_WIDTH - 4 , PUYO_HEIGHT - 4};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
	SDL_RenderFillRect(renderer, &Rect2);
}

void Board::RedrawPieces(Piece old_piece, Piece new_piece){ //Draw a piece in a different location
	if (new_piece.x < cols && new_piece.x >= 0 && new_piece.y < rows){
		board[new_piece.x][new_piece.y].Clone(board[old_piece.x][old_piece.y]);
		board[old_piece.x][old_piece.y].Reset();

		if (new_piece.y >= rows || !board[new_piece.x][new_piece.y].free){
			new_piece.falling = false;
			new_piece.moving = false;
		}
	}
}

void Board::DrawScreenBoard(){
	SDL_Rect sdl_board = {MARGIN,  PUYO_HEIGHT + MARGIN, (PUYO_WIDTH * cols), (PUYO_HEIGHT * rows)};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &sdl_board);
}