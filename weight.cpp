#include "weight.h"

/*int saveNet(s_neuralSystem *sys, const char* f_path){
	FILE *weight;
	if((weight=fopen(f_path,"w"))==NULL)
		return 0;

	int l,n,w;

	printf("--------------------NETWORK SAVED!!--------------\n");
	fseek(weight,0,SEEK_SET);
	for(l=0;l<sys->nbLayer;l++){
		fputc('l',weight);
		fputc('(',weight);
		writeLayer(sys->layer[l],weight);
		fputc(')',weight);
	}
	fclose(weight);
return 1;
}*/

int saveNet(s_neuralSystem *sys, const char* f_path){
	FILE *weight;
	if((weight=fopen(f_path,"w"))==NULL)
		return 0;

	int i,j,k;
	printf("--------------------NETWORK SAVED!!--------------\n");
	fseek(weight,0,SEEK_SET);
	fputc('l',weight);
	write(sys->nbLayer,weight);
	for(i=0;i<sys->nbLayer;i++){
		fputc('n',weight);
		write(sys->layer[i].nbNeurone,weight);
		for(j=0;j<sys->layer[i].nbNeurone;j++){
			fputc('w',weight);
			write(sys->layer[i].neurone[j].nbWeight,weight);
		}
	}
	for(i=0;i<sys->nbLayer;i++){
		for(j=0;j<sys->layer[i].nbNeurone;j++){
			for(k=0;k<sys->layer[i].neurone[j].nbWeight;k++){
				fputc(':',weight);
				write(sys->layer[i].neurone[j].weight[k],weight);
			}
		}
	}
	fclose(weight);
return 1;
}

void write(double number, FILE *w){
	int i;
	int c;
	if(number<0){
		fputc('-',w);
		number=-number;
	}
	for(i=4;i>-5;i--){
		c=(int)('0'+(number-(int)(number/pow(10,i+1))*pow(10,i+1))/pow(10,i));
		fputc(c,w);
		if(i==0)
			fputc('.',w);
	}
}

s_neuralSystem* loadNet(const char* f_path){
	FILE *weight;
	if((weight=fopen(f_path,"r"))==NULL)
		return NULL;

	s_neuralSystem *sys=new s_neuralSystem;

	int l=-1,n=0,w=0;
	bool firstW=true;
	char cur;
	while((cur=fgetc(weight))!=EOF){
		switch(cur){
			case 'l':
				sys->nbLayer=(int)readWeight(weight);
				sys->layer=new s_layer[sys->nbLayer];
			break;
			case 'n':
				l++;
				n=0;
				sys->layer[l].nbNeurone=(int)readWeight(weight);
				sys->layer[l].neurone=new s_neurone[sys->layer[l].nbNeurone];
			break;
			case 'w':
				std::cout << "weight" << std::endl;
				sys->layer[l].neurone[n].nbWeight=(int)readWeight(weight);
				sys->layer[l].neurone[n].weight=new double[sys->layer[l].neurone[n].nbWeight];
				n++;
			break;
			case ':':
				if(firstW)
					l=0,n=0,w=0,firstW=false;
				if(w==sys->layer[l].neurone[n].nbWeight)
					w=0,n++;
				if(n==sys->layer[l].nbNeurone)
					n=0,l++;
				sys->layer[l].neurone[n].weight[w]=readWeight(weight);
			break;
		}
	}
	fclose(weight);
return sys;
}

double readWeight(FILE *w){
	int sign=1;
	bool point=false;
	char cur;
	double weight=0;
	int i=0;

	if((cur=fgetc(w))=='-')
		sign*=-1;
	else
		fseek(w,-1,SEEK_CUR);

	cur=fgetc(w);
	while((cur>='0' && cur<='9') || cur=='.'){
		if(cur>='0' && cur<='9'){
			if(!point)
				weight*=10;
			else
				i--;
			weight+=(cur-'0')*pow(10,i);
		}
		else if(cur=='.' || cur==','){
			point=true;
			i=0;
		}
		cur=fgetc(w);
	}
	fseek(w,-1,SEEK_CUR);
return weight*sign;
}

/*1s_neuralSystem* loadNet(const char* f_path){
	FILE *weight;
	if((weight=fopen(f_path,"r"))==NULL)
		return NULL;

	s_neuralSystem *sys=new s_neuralSystem;
	int nbLayer=0;
	int nbNeurone=0;
	int nbWeight=0;
	int l=-1;
	int n=-1;
	int w=-1;
	char cur;
	char pre;

	fseek(weight,0,SEEK_SET);
	//                                  contage de couche:
	//----------------------------------------------------
	sys->nbLayer=0;
	while((cur=fgetc(weight))!=EOF){
		if(cur=='l')
			sys->nbLayer++;
	}
	//****************************************************
	sys->layer=new s_layer[sys->nbLayer];
	fseek(weight,0,SEEK_SET);
	//                                                  contage des neurones:
	//-----------------------------------------------------------------------
	while((cur=fgetc(weight))!=EOF){
		pre=cur;
		if(cur=='l'){
			l++;
			sys->layer[l].nbNeurone=0;
			fseek(weight,1,SEEK_CUR);
			while((cur=fgetc(weight))!=')' || pre!=')'){
				pre=cur;
				if(cur=='n')
				{
					sys->layer[l].nbNeurone++;
					std::cout << "+";
				}
			}
			sys->layer[l].neurone=new s_neurone[sys->layer[l].nbNeurone];
		}
	}
	//**********************************************************************
	l=-1;
	fseek(weight,0,SEEK_SET);
	//         																   contage des poids:
	//-------------------------------------------------------------------------------------------
	std::cout << "contage des poids" << std::endl;
	while((cur=fgetc(weight))!=EOF){
		pre=cur;
		if(cur=='l'){
			l++;
			fseek(weight,1,SEEK_CUR);
			while((cur=fgetc(weight))!=')' || pre!=')'){
				pre=cur;
				if(cur=='n'){
					n++;
					sys->layer[l].neurone[n].nbWeight=0;
					fseek(weight,1,SEEK_CUR);
					while((cur=fgetc(weight))!=')'){
						pre=cur;
						if(cur=='w')
							sys->layer[l].neurone[n].nbWeight++;
					}
					pre=cur;
					sys->layer[l].neurone[n].weight=new double[sys->layer[l].neurone[n].nbWeight];
				}
			}
		}
	}
	//********************************************************************************************
	l=-1;
	n=-1;
	fseek(weight,0,SEEK_SET);
	//                                                          valeur des poids:
	//---------------------------------------------------------------------------
	std::cout << "valeur des poids" << std::endl;
	while((cur=fgetc(weight))!=EOF){
		pre=cur;
		if(cur=='l'){
			l++;
			fseek(weight,1,SEEK_CUR);
			while((cur=fgetc(weight))!=')' || pre!=')'){
				pre=cur;
				if(cur=='n'){
					n++;
					fseek(weight,1,SEEK_CUR);
					while((cur=fgetc(weight))!=')'){
						pre=cur;
						if(cur=='w'){
							w++;
							sys->layer[l].neurone[n].weight[w]=readWeight(weight);
						}
						else if(cur=='t'){
							fseek(weight,2,SEEK_CUR);
							sys->layer[l].neurone[n].threshold=readWeight(weight);
						}
					}
					pre=cur;
				}
			}
		}
	}
	//****************************************************************************
	fclose(weight);
return sys;
}*/

