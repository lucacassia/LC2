#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "mersenne.h"
#include "vec2.h"

#define THERMALIZATION_TIME 10000     /*Numero collisioni di termalizzazione*/
#define MAX_COLLISION 2e5
#define TIME_MAX 300        /*tempo adimensionato in cui si simula il sistema*/

int n_particles = 100;      /* number of particles */
double SIGMA = 0.0f;        /* diameter of the disks */
double *collTable;          /* collision table */
int index_collision[2];     /* (i,j,tempo di collisione) */
double time_collision = 0.0f;
int numOfCollisions = 0;
double total_time = 0.0f;
double temperature = 0.0f;
double K_BOLTZ = 1.0f;
double pression = 0.0f;
double D_mom_norm = 0.0f;
double DIST_RET = 0.0f;

char header_file[256];
double DeltaT = 0.03f;
double time_prec;
unsigned int time_counted = 0;
unsigned int NUM_TEMPI_SALVATI;

/*Struttura per la particella. COntine velocità, posizione, */
/*il tempo in cui ha effettuato l'ultima collisione, il numero di collisioni che ha fatto e la distanza percorsa.*/
typedef struct body {
    double pos[DIMENSION];  /* position */
    double mom[DIMENSION];  /* momentum */
    double distance;
    double last_collision_time;
    unsigned int n_collision;
    } body ;

body *particle;
body *time_list; /*Necessaria per il calcolo di Delta r^2 per memorizzare la "storia" di tutta la simulazione*/
double T_D = 1.0f;

void init()
{
    int k;
    srand(time(NULL));
    seed_mersenne( (long)time(NULL) );
    for(k = 0; k < 543210; k++) mersenne();
}

void print_pos()
{
    FILE *f = fopen("data/position.dat","w");
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "%e\t", particle[i].pos[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

void print_mom()
{
    FILE *f = fopen("data/momentum.dat","w");
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "%e\t", particle[i].mom[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

double get_kinetic()
{
    int i,j;
    double sum = 0.0f;
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            sum += particle[i].mom[j] * particle[i].mom[j];
    return sum / 2.0f;
}

double kin_en()
{
    int i;
    double sum = 0.0f;
    for(i = 0; i < n_particles; i++)
        sum += scalar(particle[i].mom, particle[i].mom);
    return sum / 2.0f;
}

/* Print momenta for histogram */
void print_distribution()
{
    int i;
    FILE *f = fopen("data/boltzmann.dat","a");
    for(i = 0; i < n_particles; i++)
        fprintf(f, "%e\n", sqrt( scalar( particle[i].mom, particle[i].mom) ) );
    fclose(f);
}

void set_pos()
{
    /* find the first k such that k² >= n_particles */
    int i,j,k = 0;
    while( k * k < n_particles ) k++;

    for(i = 0; i < n_particles; i++){
        /* place disks on a square lattice */
        particle[i].pos[0] = (0.5f/k)+(i%k)*(1.0f/k);
        particle[i].pos[1] = (0.5f/k)+(i/k)*(1.0f/k);

        /* set random initial momentum in [-1:1] */
        particle[i].mom[0] = 2.0f * mersenne() - 1.0f;
        particle[i].mom[1] = 2.0f * mersenne() - 1.0f;

        /* initialize other data */
        particle[i].distance = 0.0f;
        particle[i].n_collision = 0;
        particle[i].last_collision_time = 0.0f;
    }

    /* compute center of mass momentum */
    double com_mom[DIMENSION];
    for(j = 0; j < DIMENSION; j++)
        com_mom[j] = 0.0f;

    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)    
            com_mom[j] += particle[i].mom[j];

    /* boost in the center of mass frame */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] -= com_mom[j]/((double) n_particles);

    print_pos();
    print_mom();
}

void reset_mfp_variables()
{
    int i;
    for(i = 0; i < n_particles; i++){
        particle[i].distance = 0.0f;
        particle[i].n_collision = 0;
        particle[i].last_collision_time = 0.0f;
    }
}

/* Controlla che le sfere non si compenetrino.*/
/*Utilizzata solo all'inizio
EXIT CODE 1 =  ERRORE, si toccano
EXIT CODE 0 =  TUTTO OK
*/

int  check_distance (){
    int i,j;
    double distance = 0;
    double subtract_v[DIMENSION];
    int x,y;
    body temp_part;
    for (i = 0 ; i< n_particles ; i++){
        for(j = i+1;j <n_particles ; j++){
            for ( x= -1; x < 2 ; x++){
                for ( y = -1; y<2 ; y++){
                    temp_part = particle[j];
                    temp_part.pos[0] += x;
                    temp_part.pos[1] += y;
                    subtract(particle[i].pos,temp_part.pos,subtract_v);    
                    distance = sqrt(scalar(subtract_v,subtract_v));
                    if( distance <SIGMA){
                        printf("Sfere (%d,%d) troppo vicine!\n",i,j);
                        return (1);
                    }
                }
            }            
        }
    }
    return (0);
}


/*Riscala la velocità in modo da avere la temperatura desiderata T_D*/
inline void riscala_vel_temp (){
    int i,j;
    double k_en = kin_en();
    for ( i = 0; i<n_particles;i++){
        for (j = 0; j<DIMENSION;j++){
            particle[i].mom[j] *= sqrt( n_particles* T_D/k_en);
        }
    }
}


/* Calcola il tempo minimo fra le 9 immagini  */
double calc_min ( int i , int j){
    double x,y;
    double min= DBL_MAX;
    double r_subtract[DIMENSION];
    double v_subtract[DIMENSION];
    double det;
    double temp;
    body temp_part;
    for ( x= -1; x < 2 ; x++){
        for ( y = -1; y<2 ; y++){
            temp_part = particle[j];
            temp_part.pos[0] += x;
            temp_part.pos[1] += y;
            subtract(particle[i].pos,temp_part.pos, r_subtract);
            subtract( particle[i].mom,temp_part.mom, v_subtract);
            if( scalar( r_subtract, v_subtract) < 0){
                det = scalar(r_subtract,v_subtract)*scalar(r_subtract,v_subtract) - scalar(v_subtract,v_subtract)*( scalar(r_subtract,r_subtract) -SIGMA*SIGMA);
                if (det > 0){
                    /*uso debug: printf("Scalar prod: %e \n",(scalar(v_subtract,v_subtract)));*/
                    temp = ( - scalar( r_subtract, v_subtract) - sqrt( det ))/ (scalar(v_subtract,v_subtract) );
                    if ( temp < min ){
                        min = temp;
                    }
                }
            }
        }
    }
    return min;
}
/* Riempie la matrice dei tempi delle collisioni per j>i */
void collision_table (){
    int i,j;
    for (i = 0; i < n_particles ; i++){
        for ( j= i+1 ; j < n_particles; j++){
            collTable[i*n_particles + j] = calc_min ( i, j );
        }
    }
}


/*    Calcola la prima coppia che colliderà.
Gli indici di particella sono salvati in "index_collision",
mentre il tempo mancante alla collisione in time_collision.
GLOBALI
*/
void search_min_coll (){
    int i,j;
    time_collision = DBL_MAX;
    for (i = 0; i < n_particles ; i++){
        for ( j= i+1 ; j < n_particles; j++){
            if (collTable[i*n_particles+j] < time_collision){
                time_collision = collTable[i*n_particles+j];
                index_collision[0] = i;
                index_collision[1] = j;
            }
        }
    }
    }
/* Sottrae il tempo dell'avvenuta collisione a tutta la matrice (parte superiore dx) */
void substract_t0 (){
int i,j;
    for (i = 0 ; i < n_particles ; i++){
        for ( j = i+1 ; j<n_particles ; j++){
            collTable[i*n_particles+ j] -= time_collision;
        }
    }
}

/* Muove le particelle di uno step temporale*/
void step (double time_step){
    int i,j;
    for ( i = 0; i < n_particles ; i++){
        for (j =0 ; j< DIMENSION ;j ++){
            particle[i].pos[j] += time_step*particle[i].mom[j];
        }
    }
}

/*Modifica le velocità delle particelle coinvolte nella collisione*/
void switch_moms(){
    int j;
    int  x,y;
    double temp_r_subtract[DIMENSION]; /* Vettore subtracterenza temporaneo per le 9 immagini*/
    double v_subtract[DIMENSION];
    double rsubtract[2]={0,0}; /*Vero vettore subtracterenza*/
    /* temp_r_subtract = R0 - R1
     * v_subtract = V0 _ V1
     */
    double min = DBL_MAX;
    double tmp_dbl;
    body temp_part;
    double v_temp;
    for ( x= -1; x < 2 ; x++){
        for ( y = -1; y<2 ; y++){
            temp_part = particle[index_collision[1]];
            temp_part.pos[0] += x;
            temp_part.pos[1] += y;
            subtract(particle[index_collision[0]].pos,temp_part.pos, temp_r_subtract); /*vettore subtracterenza salvato in temp_r_subtract*/
            tmp_dbl = scalar(temp_r_subtract,temp_r_subtract) ; 
            if ( tmp_dbl < min){
                min = tmp_dbl;
                for ( j= 0; j<DIMENSION; j++){
                rsubtract[j] = temp_r_subtract[j];
                }
            }
        }
    }
    subtract( particle[index_collision[0]].mom, particle[index_collision[1]].mom, v_subtract);
    multiply(rsubtract, 1.0f/(sqrt(scalar(rsubtract,rsubtract))) );
    v_temp = scalar(v_subtract,rsubtract);
    for ( j = 0 ; j < DIMENSION ; j++){
        particle[index_collision[0]].mom[j] -= v_temp*rsubtract[j];
        particle[index_collision[1]].mom[j] += v_temp*rsubtract[j];
    }

    }

    
/* Aggiorna i tempi di collisioni per le righe e le colonne della matrice della particelle che hanno colliso:
 *
 *
 * NOTA BENE :
 * Modifica le righe associate ad una particella -> LA MATRICE é simmetrica 
 *
 *
 * */
void update_coll_table(){
    int i,j;
    int a,b,c;
    for (i = 0; i < 2 ; i++){
        /* a,b indici di riga e colonna -> Matrice simmetrica: tengo solo b>a, ossia j> index_collision[i] */
        for ( j= 0 ; j < n_particles; j++){
            a=index_collision[i];
            b=j;
            if( a != b){
                /*considero sempre solo la parte in alto a dx della matrice*/
                if( a>b){
                    c=a;
                    a=b;
                    b=c;
                }
                collTable[a*n_particles+b]= calc_min(a,b);
            }
        }
    }
}

/*Rimette le particelle nella scatola*/
void fix_boundaries (){
    int i = 0;
    int j = 0;
    for (i = 0 ; i< n_particles ; i++){
        for( j= 0; j< DIMENSION ; j++){
            particle[i].pos[j] -= floor(particle[i].pos[j]);
        }
    }
}



/*Calcola momento totale (in norma)*/
double total_momentum (){
    int i,j;
    double  sum[2] = {0,0};
    for ( i = 0; i< n_particles ; i++){
        for ( j = 0; j< DIMENSION ; j++){
        sum[j] += particle[i].mom[j];
        }
    }
    return sqrt(scalar(sum,sum));
    }
    
/*Calcola il libero cammino medio:
*Esso viene calcolato come lo spazio percorso dalla particella a partire dall'ultimo urto che ha fatto.
Questo viene salvato in .last_collision_time
*/
inline void  mean_free_path (){
    unsigned i;
    for ( i = 0; i<2;i++){
        particle[index_collision[i]].n_collision++;
        particle[index_collision[i]].distance += (total_time+time_collision-particle[index_collision[i]].last_collision_time)*sqrt(scalar(particle[index_collision[i]].mom,particle[index_collision[i]].mom));
    }
}

/*Evolve il sistema di uno step
* Volendo calcolar dr2(t) l'evoluzioneva di step din step e tiene conto del fatto se facendo lo step temporale che porta alla collisione successiva si supera lo step temporale
* fissato per il dr2(t)
*/
void evolve ( ) {
    double deltaV_pre[DIMENSION];
    double deltaV_post[DIMENSION];
    double deltaV[DIMENSION];
    unsigned int j = 0;
    /*Calcola la prossima coppia che si scontra e mette il tempo di collisione in time_collision*/
    search_min_coll();
    /*Mfp da calcolare prima che si siano scambiate le velocità*/
    mean_free_path();
    /*
    Ossia:
    time_prec è l'ultimo tempo in cui si son salvati i dati
    total_time è il tempo corrente 
    DeltaT è la larghezza di step temporale a cui si vuole calcolare dr2
    if ( total_time + time_collision <time_prec+DeltaT ){
    */
    /* Se non ha superato lo step temporale, muovi sempre prendere dati*/
    if ( total_time + time_collision - DeltaT -time_prec < 0){
        step(time_collision);
    }
    /* Supererebbe lo step:
    * ~ muovi del tempo necessario per arrivare allo step
    * ~ prende dati
    * ~ muove del tempo necessario per arrivare a time_collision
    */
    else{
        time_counted++;
        step( time_prec + DeltaT - total_time);
        for ( j = 0; j< n_particles;j++){
            time_list[time_counted*n_particles+j] = particle[j];
        }
        step( total_time+ time_collision - time_prec - DeltaT);
        time_prec += DeltaT;
    }
    subtract(particle[index_collision[0]].mom,particle[index_collision[1]].mom,deltaV_pre);
    switch_moms();
    /*calcoli pressione*/
    subtract(particle[index_collision[0]].mom,particle[index_collision[1]].mom,deltaV_post);
    subtract(deltaV_pre,deltaV_post,deltaV);
    /*condizioni al bordo*/
    particle[index_collision[0]].last_collision_time=total_time;
    particle[index_collision[1]].last_collision_time=total_time;
    fix_boundaries();
    substract_t0();
    update_coll_table();
    numOfCollisions ++;
    total_time+=time_collision;
    pression += sqrt(scalar(deltaV,deltaV));
    }

/* Evolve ma utilizzata solo in fase di termalizzazione, senza alcuna presa dati*/
inline void evolve_therm ( ) {
    double deltaV_pre[DIMENSION];
    search_min_coll();
    step(time_collision);
    subtract(particle[index_collision[0]].mom,particle[index_collision[1]].mom,deltaV_pre);
    switch_moms();
    /*condizioni al bordo*/
    fix_boundaries();
    substract_t0();
    update_coll_table();
    numOfCollisions +=1;
    /*total_time+=time_collision;*/
    }

void vel_file_save ( ){
    int i = 0;
    FILE *f = fopen("data/v2.dat","a");
    FILE *fx = fopen ("data/vx.dat","a");
    FILE *fy = fopen("data/vy.dat","a");
    for (i = 0; i< n_particles ; i++){
        fprintf(fx,"%e\n",particle[i].mom[0]);
        fprintf(fy,"%e\n",particle[i].mom[1]);
        fprintf(f,"%e\n",scalar(particle[i].mom,particle[i].mom));
    }
    fclose(fx);
    fclose(fy);
    fclose(f);
}
void print_coll_table (){
    int i,j;
    for(i = 0; i<n_particles; i++){
        for(j=i+1; j<n_particles; j++){
        printf("Tempo collisione (%d,%d): %e\n", i,j,collTable[i*n_particles+j]);
        }
    }
    }
    

inline void copyList ( body * in , body * out){
    unsigned int i;
    for ( i = 0; i< n_particles;i++){
        out[i] = in[i];
    }
}

/*Calcola il minimo di dr2 fra tutte le immagini
    Viene calcolato per tutte le particelle. Le due liste passate sono le liste di particelle a istanti di tempo diversi
    Deve essere chiamata da r_squared_save
*/
inline double r_squared_calc ( body * list_0, body * list_1){
    unsigned int i,k;
    double sum = 0;
    double rsubtract[DIMENSION];
    double distance, min;
    double rsubtract2[2]={0,0};
    int x,y;
    body temp_part;
    for ( i = 0; i< n_particles;i++){
        min = DBL_MAX;
        for ( x= -1; x < 2 ; x++){
            for ( y = -1; y<2 ; y++){
                temp_part = list_0[i];
                temp_part.pos[0] += x;
                temp_part.pos[1] += y;
                subtract(list_1[i].pos,temp_part.pos,rsubtract);
                distance = scalar(rsubtract,rsubtract);
                if( distance < min ){
                    min = distance;
                    for ( k = 0; k<DIMENSION;k++){
                        rsubtract2[k] = rsubtract[k];
                    }
                }
            }
        }
        sum += scalar(rsubtract2,rsubtract2);
    }
    return sum/(double)n_particles;
} 

/* Fa una media sui tempi dei dr2(delta) per tutti i delta e per tempi tali che sono distanti delta tra di loro */
void r_squared_save ( char * filename){
    FILE *f = fopen(filename, "w");
    double sum=0;
    unsigned int delta,init;
    unsigned int count ;
    fprintf(f,"%s",header_file);
    double tmp;
    double var =0;
    for ( delta = 1; delta  <  time_counted-1; delta++){
        sum = 0;
        count = 0;
        for ( init = 0; init+delta<time_counted; init++){
            tmp=r_squared_calc( time_list+(init+delta)*n_particles,time_list + init*n_particles);
            sum += tmp;
            var += tmp*tmp;
            count++;
        }
        sum /= (double) count;
        var /= (double) count;
        var -= sum*sum;
        fprintf(f,"%.14e\t%.14e\t%.14e\n",delta*DeltaT, sum, sqrt(var/(double)count));
    }
    fclose(f);
}

