#ifndef DISPLAY_H
#define DISPLAY_H

#include "str.h"

#define Size 10

void dispState(SDL_Surface *screen, s_neuralSystem *sys);
void dispSquare(SDL_Surface *screen, int x, int y, double color);

#endif
