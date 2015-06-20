#include "ising.h"

int thermalization_MH(FILE* f, double beta_value){
    int t; init(beta_value);
    printf("\nMetropolis-Hasting Algorithm\tbeta = %f\n",beta);
    for(t = 0; t < 350000; t++){
        MH(1);
        if(t%700 == 0) fprintf(f,"%u\t%e\t%e\n", t, get_energy()/(width*height), beta);
    }
    return 0;
}

int thermalization_SW(FILE* f, double beta_value){
    int t; init(beta_value);
    printf("\nSwendsen-Wang Algorithm\tbeta = %f\n",beta);
    for(t = 0; t < 500; t++){
        SW();
        fprintf(f,"%u\t%e\t%e\n", t, get_energy()/(width*height), beta);
    }
    return 0;
}

int main(){
    FILE *f; int t;

    f = fopen("data/thermalization_MH_0.2.dat","w");    thermalization_MH(f,0.2);    fclose(f);
    f = fopen("data/thermalization_MH_0.3.dat","w");    thermalization_MH(f,0.3);    fclose(f);
    f = fopen("data/thermalization_MH_0.4.dat","w");    thermalization_MH(f,0.4);    fclose(f);
    f = fopen("data/thermalization_MH_0.45.dat","w");   thermalization_MH(f,0.45);   fclose(f);
    f = fopen("data/thermalization_MH_0.5.dat","w");    thermalization_MH(f,0.5);    fclose(f);
    f = fopen("data/thermalization_MH_0.6.dat","w");    thermalization_MH(f,0.6);    fclose(f);

    f = fopen("data/thermalization_SW_0.2.dat","w");    thermalization_SW(f,0.2);    fclose(f);
    f = fopen("data/thermalization_SW_0.3.dat","w");    thermalization_SW(f,0.3);    fclose(f);
    f = fopen("data/thermalization_SW_0.4.dat","w");    thermalization_SW(f,0.4);    fclose(f);
    f = fopen("data/thermalization_SW_0.45.dat","w");   thermalization_SW(f,0.45);   fclose(f);
    f = fopen("data/thermalization_SW_0.5.dat","w");    thermalization_SW(f,0.5);    fclose(f);
    f = fopen("data/thermalization_SW_0.6.dat","w");    thermalization_SW(f,0.6);    fclose(f);

    init(0.3); thermalize(0);

    f = fopen("data/magnetization_MH_0.3.dat","w");
    for(t = 0; t < 1000; t++){
        MH(1);
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization()/(width*height), beta);
    }
    fclose(f);

    f = fopen("data/magnetization_MH2_0.3.dat","w");
    for(t = 0; t < 1000000; t++){
        MH(1);
        if(t%(32*32)==0)fprintf(f,"%u\t%e\t%e\n", t, get_magnetization()/(width*height), beta);
    }
    fclose(f);

    f = fopen("data/magnetization_SW_0.3.dat","w");
    for(t = 0; t < 1000; t++){
        SW();
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization()/(width*height), beta);
    }
    fclose(f);

    clear();
    return 0;
}
