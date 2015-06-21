#include "ising.h"

int thermalization_MH(double beta_value){
    int t; init(beta_value);
    char filename[50];
    sprintf(filename,"data/thermalization_%f_MH.dat",beta_value);
    FILE *f = fopen(filename,"w");
    printf("\nMetropolis-Hasting Algorithm\tbeta = %f\n",beta);
    for(t = 0; t < 350000; t++){
        MH(1);
        if(t%700 == 0) fprintf(f,"%u\t%e\t%e\n", t, get_energy()/(width*height), beta);
    }
    fclose(f);
    return 0;
}

int thermalization_SW(double beta_value){
    int t; init(beta_value);
    char filename[50];
    sprintf(filename,"data/thermalization_%f_SW.dat",beta_value);
    FILE *f = fopen(filename,"w");
    printf("\nSwendsen-Wang Algorithm\tbeta = %f\n",beta);
    for(t = 0; t < 500; t++){
        SW(1);
        fprintf(f,"%u\t%e\t%e\n", t, get_energy()/(width*height), beta);
    }
    fclose(f);
    return 0;
}

int main(){

    thermalization_MH(0.20);    
    thermalization_MH(0.30);
    thermalization_MH(0.40);
    thermalization_MH(0.45);
    thermalization_MH(0.50);
    thermalization_MH(0.60);
    thermalization_MH(0.80);

    thermalization_SW(0.20);    
    thermalization_SW(0.30);
    thermalization_SW(0.40);
    thermalization_SW(0.45);
    thermalization_SW(0.50);
    thermalization_SW(0.60);

    int t;
    init(0.3);
    thermalize(MH);
    FILE *f = fopen("data/magnetization_0.300000_MH.dat","w");
    for(t = 0; t < 1000; t++){
        MH(1);
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization_nofabs()/(width*height), beta);
    }
    fclose(f);

    f = fopen("data/magnetization_0.300000_MH2.dat","w");
    for(t = 0; t < 1000; t++){
        MH(width*height);
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization_nofabs()/(width*height), beta);
    }
    fclose(f);

    f = fopen("data/magnetization_0.300000_SW.dat","w");
    for(t = 0; t < 1000; t++){
        SW(1);
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization_nofabs()/(width*height), beta);
    }
    fclose(f);

    clear();
    return 0;
}
