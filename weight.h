#ifndef WEIGHT_H
#define WEIGHT_H

#include "init.h"

int saveNet(s_neuralSystem *sys, const char* f_path);
void write(double number, FILE *w);
s_neuralSystem* loadNet(const char* f_path);
double readWeight(FILE *w);

#endif
