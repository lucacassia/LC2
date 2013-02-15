#include "ising.h"

int main(){
    int i;
    FILE *f = fopen("m.dat","w");
    FILE *g = fopen("e.dat","w");
    FILE *h = fopen("c.dat","w");
    for(beta=0;beta<1;beta+=0.005){
        init(); for(i=0;i<500;i++) run();
        fprintf(f,"%Le\t%Le\n",beta,mM/(width*height*N));
        fprintf(g,"%Le\t%Le\n",beta,mE/(width*height*N));
        for(i=0;i<width;i++) fprintf(h,"%d\t%e\n",i,CORR[i]/N);
        printf("beta = %Le\n",beta);
    }
    fclose(f);
    fclose(g);
    fclose(h);
    return 0;
}
