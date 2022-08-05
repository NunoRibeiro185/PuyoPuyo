#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

#define COLOR_BREAKUP(COLOR)    COLOR.r, COLOR.g, COLOR.b, COLOR.a

extern const SDL_Color COLOR_BLACK;
extern const SDL_Color COLOR_WHITE;
extern const SDL_Color COLOR_RED;
extern const SDL_Color COLOR_GREEN;
extern const SDL_Color COLOR_BLUE;
extern const SDL_Color COLOR_YELLOW;

long long UtilsTime();
void UtilsRandInit();
int UtilsRand();

SDL_Color UtilsRandomColor();
bool UtilsEqualColors(SDL_Color, SDL_Color);

#endif //UTILS_H