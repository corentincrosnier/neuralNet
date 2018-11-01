#ifndef STR_H
#define STR_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>

struct s_example{
	double *entrie;
	int answer;
};

struct s_dataSet{
	s_example *example;
};

struct s_neurone{
	int nbWeight;
	double *weight;
	double threshold;
};

struct s_layer{
	int nbNeurone;
	s_neurone *neurone;
};

struct s_neuralSystem{
	int nbLayer;
	s_layer *layer;
};

#endif
