#include <string.h>
#include "vec3.h"

int N = 512;
double SIGMA = 0.05;
double EPSILON = 1;
double dt = 1e-5;
body *particles;

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

            i->r.x = fmod(i->r.x,1);
            i->r.y = fmod(i->r.y,1);
            i->r.z = fmod(i->r.z,1);

            if(i->r.x < 0) i->r.x += 1;
            if(i->r.y < 0) i->r.y += 1;
            if(i->r.z < 0) i->r.z += 1;
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
}

void init()
{
    clear();
    vec3 sum = vec3_new(0.0,0.0,0.0);
    int k;
    for(k = 0; k < N; k++){
        body tmp = newBody( vec3_new(_rand(), _rand(), _rand()), vec3_new(2.0*_rand()-1.0, 2.0*_rand()-1.0, 2.0*_rand()-1.0));
        particles = append(particles, tmp);
        sum.x += tmp.v.x;
        sum.y += tmp.v.y;
        sum.z += tmp.v.z;
    }
    body *i = particles;
    do{
        i->v.x -= sum.x / N;
        i->v.y -= sum.y / N;
        i->v.z -= sum.z / N;
    }while((i = i->next) != particles);
}

void print()
{
    FILE *v = fopen("speed.dat","w");
    FILE *r = fopen("position.dat","w");

    body *i = particles;
    do{
        fprintf(v, "%e\t%e\t%e\n", i->v.x, i->v.y, i->v.z);
        fprintf(r, "%e\t%e\t%e\n", i->r.x, i->r.y, i->r.z);
    }while((i = i->next) != particles);

    fclose(v);
    fclose(r);
}

