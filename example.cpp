#include "example.h"

int nbExample=0;

void loadDataSet(SDL_Surface *screen, s_dataSet *dataSet, FILE *dataBase, FILE *label, int request){
	int i;

	if(nbExample%60000==0){
		fseek(dataBase,16,SEEK_SET);
		fseek(label,8,SEEK_SET);
	}
	for(i=0;i<request;i++){
		loadEx(screen,&dataSet->example[i],dataBase);
		dataSet->example[i].answer=(int)fgetc(label);
		nbExample++;
		//std::cout << (int)dataSet->example[i].answer << std::endl;
	}
}

void loadEx(SDL_Surface *screen, s_example *example, FILE *dataBase){
	int i;

	for(i=0;i<28*28;i++){
		example->entrie[i]=(double)((unsigned char)fgetc(dataBase));
		dispSquare(screen,i%28,(int)(i/28),example->entrie[i]);
	}
}
