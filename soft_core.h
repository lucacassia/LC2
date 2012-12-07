#ifndef BODY
#define BODY

#include <string.h>
#include "vec3.h"

#define RAD 0.1
#define GRAVITY 1e-1

typedef body * bodies;

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

body *clear(body *head){
    if(head != NULL){
        body *tmp = head->next;
        while(tmp != head){
            tmp = tmp->next;
            free(tmp->prev);
        }
        free(tmp);
    }
    return NULL;    
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

void move(body *head){
    if(head != NULL){
        body *j, *i = head;
        do{
            for(j = i->next; j != i; j = j->next){
                    double tmpval = GRAVITY / pow(pow(i->r.x-j->r.x,2)+pow(i->r.y-j->r.y,2)+pow(i->r.z-j->r.z,2),3.0/2.0);
                    i->v.x += (j->r.x - i->r.x) * tmpval;
                    i->v.y += (j->r.y - i->r.y) * tmpval;
                    i->v.z += (j->r.z - i->r.z) * tmpval;
            }
            i->r.x += i->v.x;
            i->r.y += i->v.y;
            i->r.z += i->v.z;
        }while((i = i->next) != head);

        do{
            i->r.x = i->r.x;
            i->r.y = i->r.y;
            i->r.z = i->r.z;
        }while((i = i->next) != head);

    }
}

void draw(body *head, void drawf(vec3,double,vec3)){
    body *tmp = head;
    while(tmp != NULL){
        drawf(tmp->r, RAD, tmp->c);
        tmp = tmp->next;
        if(tmp == head) break;
    }
}

void init(){}
void run(){}

#endif
