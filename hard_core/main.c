#include "hard_core.h"

int main(){
    int i;
    for(ETA = 0.46; ETA < 0.53; ETA += 0.0001){
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
