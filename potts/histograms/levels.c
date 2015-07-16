#include<stdio.h>
#include<math.h>

int main()
{
    int l = 4;

    FILE *f = fopen("data/levels.dat","w");
    int k,j;
    for(k = 0; k < l*l+1; k++)
        for(j = 0; j < k+1; j++)
            fprintf(f, "%e\t%e\n", 1.0f-3.0f*k/(2.0f*l*l), sqrt(3)*(k-2*j)/(2.0f*l*l) );
    fclose(f);

    return 0;
}
