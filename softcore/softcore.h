#ifndef LIB
#define LIB

#define DIMENSION 3

int NUMBER_OF_PARTICLES;
double rho;
double Rc;
double Rm;
double dt;
double dF;
double Uc;
double L;
double TEMPERATURE;

double runtime;
double V_MAX = 0.1;

typedef struct body{
    double pos[DIMENSION];
    double mom[DIMENSION];
    double acc[DIMENSION];
    int list_start;
}body ;

int last_index;
body *particleList;
body **neighboursList;
body *buffer;
unsigned int buffer_size;


void print_coordinate()
{
    FILE *f = fopen ("data/pack.dat","w");
    int i = 0;
    for(i = 0; i< NUMBER_OF_PARTICLES ; i++){
        fprintf(f,"%e\t", particleList[i].pos[0]);
        fprintf(f,"%e\t", particleList[i].pos[1]);
        fprintf(f,"%e\n", particleList[i].pos[2]);
    }
    fclose(f);
}

void subtract(double *a, double *b, double *c)
{
    int i = 0;
    for(i = 0; i < DIMENSION; i++)
        c[i] = a[i] - b[i];
}

double scalar(double *v1, double *v2)
{
    int i = 0;
    double sum  = 0;
    for(i = 0; i < DIMENSION; i++)
        sum += v1[i] * v2[i];
    return (sum);
}

void scalar_mult(double scalar, double* vec)
{
    int i;
    for(i = 0; i < DIMENSION; i++)
        vec[i] *= scalar;
}

double kinetic()
{
    int i = 0;
    double  sum = 0;
    for ( i = 0; i < NUMBER_OF_PARTICLES; i++)
        sum += 0.5 * scalar(particleList[i].mom, particleList[i].mom);
    return (sum/(double)DIMENSION);
}

double total_momentum()
{
    int i,j;
    double sum = 0;
    for(i = 0; i < NUMBER_OF_PARTICLES; i++)
        for(j = 0; j < DIMENSION; j++)
            sum += particleList[i].mom[j];
    return (sum);
}

void PBC(body *particleList)
{
    int i,j;
    for(i = 0; i < NUMBER_OF_PARTICLES; i++)
        for(j = 0; j < DIMENSION; j++){
            particleList[i].pos[j] = fmod(particleList[i].pos[j],L);
            if(particleList[i].pos[j] < 0)
                particleList[i].pos[j] += L;
        }
}

double potential(double r)
{
    if(r < Rc) return (( 4*(1/(pow(r,12))-1/(pow(r,6)))) - Uc - dF*(r-Rc));
    return 0;
}

double force(double r){return (24*(2*pow(1/r,13) - pow(1/r,7))+ dF);}

void init()
{
    srand(time(NULL));

    int i_part = 0;
    double speed_cm[3];
    int i,j;
    int x,y,z;
    for ( i = 0; i<DIMENSION;i++) {
        speed_cm[i]=0.0;
    }
    int cube_max=0;
    do{
     cube_max++;
    }while( cube_max*cube_max*cube_max<NUMBER_OF_PARTICLES);
    double lattice_spacing = L/(double)cube_max;
    for ( x=0; x<cube_max ; x++){
        for ( y = 0;  y<cube_max; y++){
            for ( z=0; z<cube_max; z++){
                if(i_part<NUMBER_OF_PARTICLES){
                    particleList[i_part].pos[0] = lattice_spacing*(x+sqrt(2)*0.5);
                    particleList[i_part].pos[1] = lattice_spacing*(y+sqrt(2)*0.5);
                    particleList[i_part].pos[2] = lattice_spacing*(z+sqrt(2)*0.5);
                    }
                i_part++;
            }
        }
    }
    for ( i = 0; i< NUMBER_OF_PARTICLES; i++){
        for ( j = 0; j<DIMENSION;j++){
            particleList[i].mom[j] = (2*(rand()/(RAND_MAX*1.0)) - 1.0 )*V_MAX;
            speed_cm[j] += particleList[i].mom[j];
            particleList[i].acc[j]=0;
            }
    }
    for (i =0 ; i< NUMBER_OF_PARTICLES; i++){
        for ( j = 0; j<DIMENSION;j++){
            particleList[i].mom[j] -= speed_cm[j]/((double) NUMBER_OF_PARTICLES);
        }
    }
}

void create_list()
{
    int i,j;
    int x,y,z;
    int found;
    double r, r_versore[DIMENSION];
    body temp_part;
    int list_index = 0;
    int has_neighbour=0;
    for ( i = 0; i<NUMBER_OF_PARTICLES-1;i++){
        has_neighbour=0;
        for ( j = i+1; j<NUMBER_OF_PARTICLES;j++){
            found = 0;
                for ( x= -1; x < 2 ; x++){
                    for ( y = -1; y<2 ; y++){
                        for( z=-1 ; z<2 ; z++){
                            if (found == 0){
                                temp_part = particleList[j];
                                temp_part.pos[0] += x*L;
                                temp_part.pos[1] += y*L;
                                temp_part.pos[2] += z*L;
                                subtract(temp_part.pos , particleList[i].pos,r_versore );
                                r = scalar(r_versore,r_versore);
                                if(r <  Rm*Rm ){
                                    found++;
                                    neighboursList[list_index] = particleList+j;
                                    if(has_neighbour == 0){
                                        particleList[i].list_start = list_index;
                                    }
                                    list_index++;
                                    has_neighbour++;
                                }
                            }
                        }
                    }
                }
        }
        if ( has_neighbour == 0){
            particleList[i].list_start =list_index;
        }
    }
    last_index = list_index;
    particleList[NUMBER_OF_PARTICLES].list_start=last_index;
}


void compute_acc()
{
    double r;
    double F;
    int i,j,l;
    double r_versore[DIMENSION];
    int x,y,z;
    int found;
    body temp_part;
    for (i=0;i<NUMBER_OF_PARTICLES;i++){
        for ( l=0;l<DIMENSION;l++){
            particleList[i].acc[l] = 0;
        }
    }
    for (i=0;i<NUMBER_OF_PARTICLES-1;i++){
        for ( j = particleList[i].list_start; ((j < particleList[i+1].list_start) && ( j<last_index)) ;j++){
            found =0;
            for ( x= -1; x < 2 ; x++){
                for ( y = -1; y<2 ; y++){
                    for( z=-1 ; z<2 ; z++){
                        if (found ==0){
                            temp_part = *(neighboursList[j]) ;
                            temp_part.pos[0] += x*L;
                            temp_part.pos[1] += y*L;
                            temp_part.pos[2] += z*L;
                            subtract(particleList[i].pos,temp_part.pos ,r_versore );
                            r = scalar(r_versore,r_versore);
                            if ( r < Rc*Rc){
                                r = sqrt(r);
                                found++;
                                F= force(r);
                                scalar_mult(1/r,r_versore);
                                for ( l=0;l<DIMENSION;l++){
                                    particleList[i].acc[l] += F*r_versore[l];
                                    neighboursList[j]->acc[l] -= F*r_versore[l];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void verlet(body *list)
{
    int i,j;
    for(i = 0; i < NUMBER_OF_PARTICLES; i++){
        for(j = 0; j < DIMENSION;j++){
            list[i].pos[j] += list[i].mom[j] * dt + 0.5 * list[i].acc[j] * dt * dt;
            list[i].mom[j] += 0.5 * list[i].acc[j] * dt;
            
        }
    }
    PBC(particleList);
    compute_acc();
    for ( i = 0 ; i < NUMBER_OF_PARTICLES ; i++){
        for (j = 0; j<DIMENSION;j++){
            list[i].mom[j] += list[i].acc[j]*0.5*dt;
        }
    }
}

double total_energy()
{
    int i,j;
    double K = 0;
    double U = 0;
    double v[DIMENSION];
    for(i = 0; i < NUMBER_OF_PARTICLES-1; i++){
        K += 0.5 * scalar(particleList[i].mom, particleList[i].mom);
        for(j = particleList[i].list_start; j < particleList[i+1].list_start; j++){
            subtract(neighboursList[j]->pos, particleList[i].pos,v);
            U += potential(sqrt(scalar(v,v)));
        }
    }
    return ((K+U)/(double)NUMBER_OF_PARTICLES);
}

void set_temperature(double new_temp){
    int i,j;
    double K = kinetic();
    for(i = 0; i < NUMBER_OF_PARTICLES; i++)
        for(j = 0; j < DIMENSION; j++)
            particleList[i].mom[j] *= sqrt(new_temp/K);
}

double get_MSD(body *list0, body *list1)
{
    int i,j;
    int dx[DIMENSION];
    double distance, sum = 0.0f;
    double dr[DIMENSION];
    for(i = 0; i < NUMBER_OF_PARTICLES; i++){
        /* first copy */
        for(j = 0; j < DIMENSION; j++)
            dr[j] = list1[i].pos[j] - list0[i].pos[j];
        distance = scalar(dr,dr);
        /* check other copies */
        for(dx[0] = -1; dx[0] <= 1 ; dx[0]++)
            for(dx[1] = -1; dx[1] <= 1; dx[1]++){
                for(dx[2] = -1; dx[2] <= 1; dx[2]++){
                    for(j = 0; j < DIMENSION; j++)
                        dr[j] = dx[j] + list1[i].pos[j] - list0[i].pos[j];
                    if(scalar(dr,dr) < distance)
                        distance = scalar(dr,dr);
                }
            }
        sum += distance;
    }
    return sum / NUMBER_OF_PARTICLES;
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
            tmp = get_MSD( buffer + start * NUMBER_OF_PARTICLES, buffer + (start+shift) * NUMBER_OF_PARTICLES );
            mean += tmp;
            error += tmp*tmp;
            count++;
        }
        mean /= count;
        error = sqrt( (error / count - mean * mean)/count );
        fprintf(f,"%e\t%e\t%e\t%e\n", rho, shift * dt, mean, error );
    }
    fclose(f);
}

void print_energy()
{
    FILE *f = fopen("data/energy.dat","a");
    fprintf(f,"%e\t%e\n",runtime,total_energy() );
    fclose(f);
}

void print_momentum()
{
    FILE *f = fopen("data/momentum.dat","a");
    fprintf(f,"%e\t%e\n",runtime,total_momentum() );
    fclose(f);
}

void print_distribution()
{
    int i;
    double tmp;
    FILE *f = fopen("data/distribution.dat","a");
    for (i = 0; i < NUMBER_OF_PARTICLES; i++){
        tmp = sqrt( scalar(particleList[i].mom, particleList[i].mom) );
        fprintf(f, "%e\n", tmp);
    }
    fclose(f);
}

#endif
