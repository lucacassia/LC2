#include "hard_core.h"

int main(){
    int i;
    for(ETA = 0.595; ETA < 0.68; ETA += 0.001){
        init();
        for(i = 0; i < 10000; i++)
            run();
        reset();
        for(i = 0; i < 10000; i++)
            run();
        print();
        printf("ETA = %lf\truntime = %lf\n",ETA,runtime);
    }
    return 0;
}
