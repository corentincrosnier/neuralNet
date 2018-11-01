#include "init.h"

#define thrshld -5000

void InitPerceptron(s_neuralSystem *sys, int nbLayer, int nbNeurone, int nbWeight){
	int i,j,k;

	sys->nbLayer=nbLayer;
	sys->layer=new s_layer[nbLayer];
	/*sys->layer[1].nbNeurone=10;
	sys->layer[1].neurone=new s_neurone[10];*/
	for(k=0;k<nbLayer;k++){
		sys->layer[k].nbNeurone=nbNeurone;
		sys->layer[k].neurone=new s_neurone[nbNeurone];
		for(i=0;i<nbNeurone;i++){
			sys->layer[k].neurone[i].nbWeight=(!k)?nbWeight:nbNeurone;
			sys->layer[k].neurone[i].weight=new double[sys->layer[k].neurone[i].nbWeight];
			for(j=0;j<sys->layer[k].neurone[i].nbWeight;j++){
				sys->layer[k].neurone[i].weight[j]=(rand()%400001-200000)/10000.0;
			}
			sys->layer[k].neurone[i].threshold=thrshld;
		}
	}
}
