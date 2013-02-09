#ifndef CLUSTER
#define CLUSTER

#include <stdlib.h>

typedef struct _cluster{
    unsigned int idx;
    struct _cluster *next_obj;
    struct _cluster *next_cl;
}cluster;

cluster *cl_add_obj(cluster *head, int idx){
    cluster *tmp;
    if((tmp = head)){
        while(tmp->next_obj) tmp = tmp->next_obj;
        tmp = tmp->next_obj = (cluster*)malloc(sizeof(cluster));
        
    }else head = tmp = (cluster*)malloc(sizeof(cluster));
    tmp->idx = idx;
    tmp->next_obj = NULL;
    tmp->next_cl = NULL;
    return head;
}

cluster *cl_add_cl(cluster *head, int idx){
    cluster *tmp;
    if((tmp = head)){
        while(tmp->next_cl) tmp = tmp->next_cl;
        tmp = tmp->next_cl = (cluster*)malloc(sizeof(cluster));
        
    }else head = tmp = (cluster*)malloc(sizeof(cluster));
    tmp->idx = idx;
    tmp->next_obj = NULL;
    tmp->next_cl = NULL;
    return head;
}

cluster *cl_merge(cluster *head, cluster *other){
    if(head == other) return head;
    if(!head) return other;
    if(!other) return head;
    cluster *tmp = head;
    while(tmp && tmp->next_cl != other) tmp = tmp->next_cl;
    if(!tmp){
        tmp = other;
        other = head;
        head = tmp;
    }
    while(tmp->next_cl != other) tmp = tmp->next_cl;
    tmp->next_cl = other->next_cl;
    tmp = head;
    while(tmp->next_obj) tmp = tmp->next_obj;
    tmp->next_obj = other;
    tmp->next_obj->next_cl = NULL;
    return head;
}

cluster *cl_clear(cluster* head){
    cluster *tmp;
    while(head->next_cl) head = cl_merge(head, head->next_cl);
    while((tmp = head)){
        head = head->next_obj;
        free(tmp);
    }
    return NULL;
}

cluster *cl_which(cluster *head, int idx){
    cluster *tmp;
    while(head){
        for(tmp = head; tmp != NULL; tmp = tmp->next_obj)
            if(tmp->idx == idx) return head;
        head = head->next_cl;
    }
    return NULL;
}

#endif
