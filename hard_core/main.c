#include "hard_core.h"

int main(){
    int i;
    for(n = 1; n < 10; n++){
        init();
        for(i = 0; i < 10000; i++)
            run();
        reset();
        for(i = 0; i < 10000; i++)
            run();
        print();
        printf("N = %d\truntime = %lf\n",N,runtime);
    }
    return 0;
}
