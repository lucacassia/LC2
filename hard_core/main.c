#include "hard_core.h"

int main(){
    int i;
    for(N = 2; N <= 100; N += 2){
        init();
        for(i = 0; i < 30000; i++)
            run();
        reset();
        for(i = 0; i < 30000; i++)
            run();
        print();
        printf("N = %d\truntime = %lf\n",N,runtime);
    }
    return 0;
}
