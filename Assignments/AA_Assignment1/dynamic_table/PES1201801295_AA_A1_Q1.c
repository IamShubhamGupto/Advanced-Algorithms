#include<stdlib.h>
#include"dyntable_impl.h"
#define threshold 0.7500000
struct table {
    int capacity;
    int filled;
    int* arr;
};
typedef struct table table_t;
void* make_new_dynamic_table(int n){
    table_t* tab = malloc(sizeof(table_t));
    free(tab->arr);
    tab->arr = (int*)malloc(sizeof(int)*(n));
    tab->capacity = n;
    tab->filled = 0;
    return tab;

}
void push_back(void** dt, int n){
    //void* dt1 = dt;
    table_t* tab = NULL;
    tab = (table_t*)*dt;
    if((float)(tab->filled/tab->capacity) >= threshold){
        //increase table size
    }else{
        tab->arr[tab->filled] = n;
        tab->filled += 1;
    }


}

void pop_back(void** dt){
    table_t* tab = NULL;
    tab = (table_t*)*dt;
    if((float)(tab->filled/tab->capacity) <= threshold){
        //decrease table size
    }else{
        if(tab->filled > 0){
            tab->filled -= 1;
        }
        
    }

}