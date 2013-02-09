#include "ising.h"

int main(){
    int i;
    FILE *f = fopen("m.dat","w");
    for(beta=0;beta<1.5;beta+=0.005){
        init(); for(i=0;i<500;i++) run();
        fprintf(f,"%Le\t%Le\n",beta,mM/(width*height*N));
        printf("beta = %Le\n",beta);
    }
    fclose(f);
    return 0;
}
