#include "neurone.h"

#define N sys->layer[l].neurone[n]
#define alpha 0.0001
#define k 0.001

using namespace std;

char cur;
char prev;

double sigmoid(double x);

double f_activation(s_neurone neurone, double *entrie){
	double sum=0;
	int i;

	for(i=0;i<28*28;i++){
		sum+=neurone.weight[i]*entrie[i];
	}
//return (sum<0)?0:1;
return sigmoid(sum-neurone.threshold);
}

void useNet(s_neuralSystem *sys, s_example *example, int nbExample){
	int e,l,n,w,i;
	int a=1;
	double answer[sys->layer[0].nbNeurone];
	double meso_entrie[sys->layer[0].nbNeurone];
	double most=0;
	int nbGood=0;

	for(e=0;e<nbExample;e++){
		for(l=0;l<sys->nbLayer;l++){
			for(n=0;n<sys->layer[l].nbNeurone;n++){
				answer[n]=f_activation(sys->layer[0].neurone[n],example[e].entrie);
			}
			for(i=0;i<10;i++){
				meso_entrie[i]=answer[i];
			}
		}
		most=0;
		for(i=0;i<10;i++){
			if(most<answer[i]){
				most=answer[i];
				a=i;
			}
		}
		if(a==example[e].answer)
			nbGood++;
	}
	cout << nbGood << " bonne réponse sur " << nbExample << endl;
	//if(nbGood==100)
	//	saveNet(sys,weight);
}

void learn(s_neuralSystem *sys, s_example *example, int nbExample){
	int e,l,n,w,i;
	int a=1;
	double answer[10];
	double meso_entrie[10];
	double most=0;
	int nbGood=0;
	//FILE *weight=fopen("./weight","w");

	for(e=0;e<nbExample;e++){
		for(l=0;l<sys->nbLayer;l++){
			for(n=0;n<sys->layer[l].nbNeurone;n++){
				answer[n]=f_activation(sys->layer[0].neurone[n],example[e].entrie);
				for(w=0;w<sys->layer[l].neurone[n].nbWeight;w++){
					N.weight[w]+=alpha*(((n==example[e].answer)?1:0)-answer[n])*example[e].entrie[w];
				}
			//	cout << answer[n] << endl;
			}
			for(i=0;i<10;i++){
				meso_entrie[i]=answer[i];
			}
		}
		most=0;
		for(i=0;i<10;i++){
			if(most<answer[i]){
				most=answer[i];
				a=i;
			}
		}
		if(a==example[e].answer)
			nbGood++;
	}
	cout << nbGood << " bonne réponse sur " << nbExample << endl;
	//if(nbGood==100)
	//	saveNet(sys,"./weight");
}

/*void loadWeight(s_neuralSystem sys, const char path){
  FILE *f=fopen(path,"r");
  bool first=true;
  bool stop=false;
  int nbNeurone=0;

  while(!stop){
  switch(cur=fgetc(f)){
  case n:
  if(first)
  n++;
  while((cur=fgetc(f))!='{'){
  if(cur>='0' && cur<='9'){

  }
  }
  break;
  }
  }
  }*/

double sigmoid(double x){
	return 1/(1+exp(-k*x));
}
