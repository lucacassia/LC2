#include <string.h>
#include "vec3.h"

int N = 16;
double SIGMA = 0.1;
double dt = 1e-10;
body *particles;

double ham;

body newBody(const vec3 position, const vec3 velocity){
    body tmp = {.r = position,
                .v = velocity,
                .c = vec3_new(_rand(), _rand(), _rand()),
                .prev = &tmp,
                .next = &tmp
                };
    return tmp;
}

body *append(body *head, const body obj){
    body *tmp = (body *)malloc(sizeof(body));
    memcpy(tmp, &obj, sizeof(body));
    if(head == NULL)
        head = tmp;
    tmp->next = head;
    tmp->prev = head->prev;
    tmp->next->prev = tmp;
    tmp->prev->next = tmp;
    return head;
}

body *erase(body *head, body *obj){
    if(head != NULL){
        if(head == obj){
            head = head->next;
            if(head == head->next && head == head->prev)
                head = NULL;
        }
        obj->next->prev = obj->prev;
        obj->prev->next = obj->next;
        free(obj);
    }
    return head;
}

void clear(){
    if(particles != NULL){
        body *tmp = particles->next;
        while(tmp != particles){
            tmp = tmp->next;
            free(tmp->prev);
        }
        free(tmp);
    }
    particles = NULL;
}

double get_hamilton(){
    double tmp = 0;
    body *j, *i = particles;
    do{
        tmp += vec3_dot(i->v, i->v)/2;
            double dx,dy,dz;
            for(j = i->next; j != i; j = j->next)
                for(dx = -1; dx <= 1; dx++)
                    for(dy = -1; dy <= 1; dy++)
                        for(dz = -1; dz <= 1; dz++){
                            vec3 dr;
                            dr.x = dx + j->r.x - i->r.x;
                            dr.y = dy + j->r.y - i->r.y;
                            dr.z = dz + j->r.z - i->r.z;
                            tmp += 4 * (pow(1 / vec3_mod(dr), 12) - pow(1 / vec3_mod(dr), 6));
                        }
    }while((i = i->next) != particles);
    return tmp;
}

void run(){
    if(particles != NULL){
        body *j, *i = particles;

        do{
            double dx,dy,dz;
            for(j = i->next; j != i; j = j->next)
                for(dx = -1; dx <= 1; dx++)
                    for(dy = -1; dy <= 1; dy++)
                        for(dz = -1; dz <= 1; dz++){
                            vec3 dr;
                            dr.x = dx + j->r.x - i->r.x;
                            dr.y = dy + j->r.y - i->r.y;
                            dr.z = dz + j->r.z - i->r.z;
                            double dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                            i->v.x += dr.x * dv;
                            i->v.y += dr.y * dv;
                            i->v.z += dr.z * dv;
                        }
        }while((i = i->next) != particles);

        do{
            i->r.x += i->v.x * dt;
            i->r.y += i->v.y * dt;
            i->r.z += i->v.z * dt;

            i->r.x -= floor(i->r.x);
            i->r.y -= floor(i->r.y);
            i->r.z -= floor(i->r.z);
        }while((i = i->next) != particles);

        do{
            double dx,dy,dz;
            for(j = i->next; j != i; j = j->next)
                for(dx = -1; dx <= 1; dx++)
                    for(dy = -1; dy <= 1; dy++)
                        for(dz = -1; dz <= 1; dz++){
                            vec3 dr;
                            dr.x = dx + j->r.x - i->r.x;
                            dr.y = dy + j->r.y - i->r.y;
                            dr.z = dz + j->r.z - i->r.z;
                            double dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                            i->v.x += dr.x * dv;
                            i->v.y += dr.y * dv;
                            i->v.z += dr.z * dv;
                        }
        }while((i = i->next) != particles);
    }

    ham = get_hamilton();
}

void init()
{
    int n = 0;
    while(2*n*n*n < N) n++;

    clear();
    int i,j,k,l;
    vec3 tmp, sum = vec3_new(0.0,0.0,0.0);
    for(l = i = 0; i < n && l < N/2; i++)
        for(j = 0; j < n && l < N/2; j++)
            for(k = 0; k < n && l < N/2; k++){
                tmp.x = i*1.0/n;
                tmp.y = j*1.0/n;
                tmp.z = k*1.0/n;
                particles = append(particles, newBody( tmp, vec3_new(2.0*_rand()-1.0, 2.0*_rand()-1.0, 2.0*_rand()-1.0)));
                tmp.x += 1.0/n/2.0;
                tmp.y += 1.0/n/2.0;
                tmp.z += 1.0/n/2.0;
                particles = append(particles, newBody( tmp, vec3_new(2.0*_rand()-1.0, 2.0*_rand()-1.0, 2.0*_rand()-1.0)));
                sum.x += particles->prev->v.x + particles->prev->prev->v.x;
                sum.y += particles->prev->v.y + particles->prev->prev->v.y;
                sum.z += particles->prev->v.z + particles->prev->prev->v.z;
                l++;
            }

    body *ptr = particles;
    do{
        ptr->v.x -= sum.x / N;
        ptr->v.y -= sum.y / N;
        ptr->v.z -= sum.z / N;
    }while((ptr = ptr->next) != particles);

    double norm = 0;
    do{
        norm += vec3_dot(ptr->v, ptr->v);
    }while((ptr = ptr->next) != particles);

    norm = norm / (3 * N);
    norm = sqrt(norm);
    do{
        ptr->v.x /= norm;
        ptr->v.y /= norm;
        ptr->v.z /= norm;
    }while((ptr = ptr->next) != particles);

    ham = get_hamilton();
}

void print()
{
    FILE *v = fopen("speed.dat","a");
    FILE *r = fopen("position.dat","w");

    body *i = particles;
    do{
        fprintf(v, "%e\t%e\t%e\n", i->v.x, i->v.y, i->v.z);
    }while((i = i->next) != particles);

    fclose(v);
    fclose(r);
}

