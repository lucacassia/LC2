#include <string.h>
#include "vec3.h"

int N = 256;
double SIGMA = 0.01;
double EPSILON = 1e-2;
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

void run(){
    if(particles != NULL){
        body *j, *i = particles;
        do{
            for(j = i->next; j != i; j = j->next){
                    vec3 dr;
                    dr.x = j->r.x - j->r.x;
                    dr.y = j->r.y - j->r.y;
                    dr.z = j->r.z - j->r.z;
                    double dv = 12 * (EPSILON / SIGMA) * (2 * pow(SIGMA / vec3_mod(dr), 13) - pow(SIGMA / vec3_mod(dr), 7)) / vec3_mod(dr);
                    i->v.x += dr.x * dv;
                    i->v.y += dr.y * dv;
                    i->v.z += dr.z * dv;
            }
        }while((i = i->next) != particles);

        do{
            i->r.x += i->v.x;
            i->r.y += i->v.y;
            i->r.z += i->v.z;

            i->r.x = fmod(i->r.x,1);
            i->r.y = fmod(i->r.y,1);
            i->r.z = fmod(i->r.z,1);

            if(i->r.x < 0) i->r.x += 1;
            if(i->r.y < 0) i->r.y += 1;
            if(i->r.z < 0) i->r.z += 1;
        }while((i = i->next) != particles);

        do{
            for(j = i->next; j != i; j = j->next){
                    vec3 dr;
                    dr.x = j->r.x - j->r.x;
                    dr.y = j->r.y - j->r.y;
                    dr.z = j->r.z - j->r.z;
                    double dv = 12 * (EPSILON / SIGMA) * (2 * pow(SIGMA / vec3_mod(dr), 13) - pow(SIGMA / vec3_mod(dr), 7)) / vec3_mod(dr);
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
    int k;
    for(k = 0; k < N; k++)
        particles = append(particles, newBody( vec3_new(_rand(), _rand(), _rand()), vec3_new(2.0*_rand()-1.0, 2.0*_rand()-1.0, 2.0*_rand()-1.0)));
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

