#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "weight.h"

void loadDataSet(SDL_Surface *screen, s_dataSet *dataSet, FILE *dataBase, FILE *label, int request);
void loadEx(SDL_Surface *screen, s_example *example, FILE *dataBase);

#endif
