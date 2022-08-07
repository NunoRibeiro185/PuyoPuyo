#include <time.h>
#include "Utils.h"

const SDL_Color COLOR_BLACK         = {0, 0, 0, 255};
const SDL_Color COLOR_WHITE         = {255, 255, 255, 255};
const SDL_Color COLOR_RED           = {255, 0, 0, 255};
const SDL_Color COLOR_GREEN         = {0, 255, 0, 255};
const SDL_Color COLOR_BLUE          = {0, 0, 255, 255};
const SDL_Color COLOR_YELLOW        = {255, 255, 0, 255};

long long UtilsTime()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC_RAW, &t);
    return t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

int UtilsRand(int min, int max)
{
    return ( rand() % (max + 1) ) + min;
}

void UtilsRandInit()
{
    srand(time(NULL));
}

SDL_Color UtilsRandomColor(){

    srand (rand() % rand());
    int color = UtilsRand(0,3);

    SDL_Color colors[4];

    colors[0] = COLOR_RED;
	colors[1] = COLOR_GREEN;
	colors[2] = COLOR_BLUE;
	colors[3] = COLOR_YELLOW;

    return colors[color];
}

bool UtilsEqualColors (SDL_Color color1, SDL_Color color2)
{
    return *((Sint32 *) &color1) == *((Sint32 *) &color2);
}