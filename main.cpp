#include "neurone.h"

#define set 100

using namespace std;

void delet(s_neuralSystem *sys);

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen=SDL_SetVideoMode(280,280,32,SDL_DOUBLEBUF);
	SDL_Event event;
	char dialogIn[100];
	int mode=0;
	bool stop=false;
	int pause=0;
	char cur;
	int i,j,k;
	FILE *dataBase=fopen("./dataSet/train-images.idx3-ubyte","r");
	FILE *label=fopen("./dataSet/train-labels.idx1-ubyte","r");
	FILE *nweight;
	s_dataSet dataSet;
	s_neuralSystem *sys=new s_neuralSystem;

	srand(time(NULL));
	
	InitPerceptron(sys,1,10,28*28);
	//sys=loadNet("./save_3");
	cout << sys->nbLayer << endl;
	cout << sys->layer[0].nbNeurone << endl;
	cout << sys->layer[0].neurone[0].weight[0] << endl;

	//chargement expample:
	//-----------------------------------------------
	fseek(dataBase,16,SEEK_SET);
	fseek(label,8,SEEK_SET);
	dataSet.example=new s_example[set];
	for(i=0;i<set;i++){
		dataSet.example[i].entrie=new double[28*28];
	}
	//***********************************************

	while(!stop){
		SDL_PollEvent(&event);
		if(event.type==SDL_KEYDOWN){
			switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					stop=true;
				break;
				case SDLK_p:
					dispState(screen,sys);
				break;
				case SDLK_SPACE:
					pause=(pause+1)%2;
					cout << "--------PAUSE--------" << mode << endl;
				break;
				case SDLK_m:
					mode=(mode+1)%2;
					cout << "mode changé: " << mode << endl;
				break;
				case SDLK_l:

					cout << "Entrez le chemins du fichier relatif au binaire :";
					scanf("%s",dialogIn);
					cout << dialogIn << "g" << endl;
					if((sys=loadNet((const char*)dialogIn))==NULL){
						cout << "Le chemin entré ne correspond à aucun fichier." << endl;
						break;
					}
					/*for(i=0;i<sys->nbLayer;i++){
						for(j=0;j<sys->layer[i].nbNeurone;j++){
							for(k=0;k<sys->layer[i].neurone[j].nbWeight;k++){
								cout << sys->layer[i].neurone[j].weight[k] << endl;
							}
						}
					}*/
					fseek(dataBase,16,SEEK_SET);
					fseek(label,8,SEEK_SET);
				break;
				case SDLK_s:
					cout << "Entrez le chemin ou vous voulez enregistrer le fichier." << endl;
					cout << "(le fichier sera créé si il n'existe pas):";
					scanf("%s",dialogIn);
					saveNet(sys,(const char*)dialogIn);
				break;
				case SDLK_KP0:
					fseek(dataBase,16,SEEK_SET);
					fseek(label,8,SEEK_SET);
				break;
			}
		}
		if(!pause){
			loadDataSet(screen,&dataSet,dataBase,label,set);
			switch(mode){
				case 0:
					useNet(sys,dataSet.example,set);
				break;
				case 1:
					learn(sys,dataSet.example,set);
				break;
			}
			SDL_Flip(screen);
		}
	}
	for(i=0;i<set;i++){
		delete[] dataSet.example[i].entrie;
	}
	delete[] dataSet.example;
	delet(sys);
	delete[] sys;
	fclose(dataBase);
	fclose(label);
	SDL_Quit();
return 0;
}

void delet(s_neuralSystem *sys){
	int n,l;
	for(l=0;l<sys->nbLayer;l++){
		for(n=0;n<sys->layer[l].nbNeurone;n++)
			delete[] sys->layer[l].neurone[n].weight;
		delete[] sys->layer[l].neurone;
	}
	delete[] sys->layer;
}
