#include"potts.h"

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int i;
    for(i = 1; i < argc; i++){

        /* read from input */
        FILE *fin;
        if( !(fin = fopen(argv[i], "rb") ) ){
            printf("Error opening file: %s\n", argv[i]);
            break;
        }

        raw storage[2];
        storage[0] = load_data(fin,1,1000); /* number of spins in the state 0 */
        storage[1] = load_data(fin,3,1000); /* number of spins in the state 2 */

        int L = storage[0].hdr.l;

        /* bin data */
        int i,j,k;
        int **histogram = (int**)malloc((L*L+1)*sizeof(int*));
        for(k = 0; k < (L*L+1); k++)
            histogram[k]=(int*)malloc((k+1)*sizeof(int));
        for(k = 0; k < (L*L+1); k++) for(j = 0; j < k+1; j++)
            histogram[k][j] = 0;
        for(i = 0; i < storage[0].hdr.size; i++){
            histogram[L*L-(int)(storage[0].data[i])][(int)(storage[1].data[i])]++;
        }
        free(storage[0].data); storage[0].data = NULL;
        free(storage[1].data); storage[1].data = NULL;

        /* write to output */
        char output[50];
        sprintf(output, "data/%d_%f_%s_%d.hist", storage[0].hdr.l, storage[0].hdr.b, storage[0].hdr.algorithm, storage[0].hdr.size );
        FILE *fout = fopen(output,"w");
        for(k = 0; k < (L*L+1); k++) for(j = 0; j < k+1; j++)
            fprintf(fout, "%e\t%e\t%e\t%d\n", storage[0].hdr.b, 1.0f-(3.0f*k)/(2.0f*L*L), sqrt(3)*(k-2*j)/(2.0f*L*L), histogram[k][j] );
        fprintf(fout, "\n");
        fclose(fout);

        /* clear memory */
        printf("Written to: %s\t\tβ -> %f\n", output, storage[0].hdr.b);
        for(k = 0; k < (L*L+1); k++)
            free(histogram[k]);
        free(histogram);
    }
    return 0;
}

