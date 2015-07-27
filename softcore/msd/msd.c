#define DIMENSION 3

#include"softcore.h"

double TEMPERATURE;

double ***buffer = NULL;
int buffer_size = 3000;
int idx = 0;

double get_MSD(double **list0, double **list1)
{
    int i,j;
    double sum = 0.0f;
    double dr[DIMENSION];
    for(i = 0; i < N; i++){
        for(j = 0; j < DIMENSION; j++)
            dr[j] = distPBC(list1[i][j] - list0[i][j]);
        sum += scalar(dr,dr);
    }
    return sum / (N*L*L);
}

void print_MSD(char *filename)
{
    FILE *f = fopen(filename, "w");
    int count, start, shift;
    double tmp;
    double mean, error;
    for(shift = 0; shift < buffer_size; shift++){
        error = mean = count = 0.0f;
        for(start = 0; (start + shift) < buffer_size; start++){
            tmp = get_MSD( buffer[start], buffer[start+shift] );
            mean += tmp;
            error += tmp*tmp;
            count++;
        }
        mean /= count;
        error = sqrt( (error / count - mean * mean)/count );
        fprintf(f,"%e\t%e\t%e\t%e\n", rho, shift * 100 * dt, mean, error );
    }
    fclose(f);
}

int main (int argc, char *argv[])
{
    if(argc==2) TEMPERATURE = atof(argv[1]);
    else return 1;

    /* MD settings */
    N = 256;
    rho = 0.9;
    L = pow(N/rho, 1.0f/DIMENSION);

    /* allocate memory */
    obj *particle = (obj*)malloc(N*sizeof(obj));
    int **neighbour = NULL;
    neighbour = create_table(neighbour);

    init_pos(particle,N/2,0.0);
    init_pos(&particle[N/2],N-N/2,0.5);

    init_mom(particle);
    reset_mom(particle,TEMPERATURE/T);
    compute_table(particle,neighbour);
    get_acc(particle,neighbour);

    /* print header */
    printf("# DIMENSION = %d\n\n", DIMENSION );
    printf("# N=%d rho=%f L=%f T=%f dt=%f\n", N, rho, L, T, dt);

    /* allocate buffer */
    int i,j,k;
    buffer = (double***)malloc(buffer_size*sizeof(double**));
    for(k = 0; k < buffer_size; k++){
        buffer[k] = (double**)malloc(N*sizeof(double*));
        for(j = 0; j < N; j++)
            buffer[k][j]=(double*)malloc(DIMENSION*sizeof(double));
    }

    /* thermalization */
    for(i = 0; i < 10/dt; i++){
        if(!(i%10)) compute_table(particle,neighbour);
        integrate(particle,neighbour);
        if(!(i%10)) reset_mom(particle,TEMPERATURE/T);
    }
    printf("# Thermalized\n");

    /* data gathering */
    for(idx = 0; idx < buffer_size;idx++){
        for(i = 0; i < 100; i++){
            if(!(i%10)) compute_table(particle,neighbour);
            integrate(particle,neighbour);
        }
        for(i = 0; i < N; i++)
            for(j = 0; j < DIMENSION; j++)
                buffer[idx][i][j] = particle[i].pos[j];
    }
    printf("Data gathered\n");

    /* compute MSD */
    char filename[64];
    sprintf(filename,"data/%d_%.3f_%.3f_msd.dat",N,rho,TEMPERATURE);
    print_MSD(filename);

    /* close */
    for(k = 0; k < buffer_size; k++){
        for(j = 0; j < N; j++)
            free(buffer[k][j]);
        free(buffer[k]);
    }free(buffer);
    destroy_table(neighbour);
    free(particle);
    return 0;
}
