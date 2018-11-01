#ifndef NEURONE_H
#define NEURONE_H

#include "example.h"

double f_activation(s_neurone neurone, double *entrie);
void useNet(s_neuralSystem *sys, s_example *example, int nbExample);
void learn(s_neuralSystem *sys, s_example *example, int nbExample);

#endif
