#include "ising.h"

int main(){
    int i;
    FILE *f = fopen("m.dat","w");
    FILE *g = fopen("e.dat","w");
    FILE *h = fopen("c.dat","w");
    FILE *b = fopen("b.dat","w");
    for(beta=0;beta<1;beta+=0.005){
        init(); for(i=0;i<500;i++) run();
        fprintf(f,"%e\t%e\n",beta,mM/(width*height*N));
        fprintf(g,"%e\t%e\n",beta,mE/(width*height*N));
        for(i=0;i<width;i++) fprintf(h,"%d\t%e\n",i,CORR[i]/N);
        fprintf(b,"%e\t%e\n",beta,CORR[4]/N);
        printf("beta = %e\n",beta);
    }
    fclose(f);
    fclose(g);
    fclose(h);
    fclose(b);
    return 0;
}
