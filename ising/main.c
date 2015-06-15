#include "ising.h"

int main(){
    int i;
    FILE *f1 = fopen("magnetization.dat","w");
    FILE *f2 = fopen("energy.dat","w");
    FILE *f3 = fopen("correlation.dat","w");
    FILE *f4 = fopen("beta.dat","w");
    for(beta=0;beta<1;beta+=0.005){
        init(); for(i=0;i<500;i++) run();
        fprintf(f1,"%e\t%e\n",beta,mean_magnetization/(width*height*markov_time));
        fprintf(f2,"%e\t%e\n",beta,mean_energy/(width*height*markov_time));
        for(i=0;i<width;i++) fprintf(f3,"%d\t%e\n",i,correlation[i]/markov_time);
        fprintf(f4,"%e\t%e\n",beta,correlation[4]/markov_time);
        printf("beta = %e\n",beta);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    return 0;
}
