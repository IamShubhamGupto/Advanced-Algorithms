#include<stdlib.h>
#include<math.h>
#include"dyntable_impl.h"
#define threshold 0.7500000
#define realloc_threshold 1
#define dealloc_threshold 0.2500000     
#define increase_factor 1.5000000
#define decrease_factor 0.2500000
struct table {
    int capacity;
    int filled;
    int arr[0];
};
typedef struct table table_t;

static void copyArray(table_t* tab, table_t* temp);

static void copyArray(table_t* tab, table_t* temp){
    for(int i = 0 ; i < tab->filled; i++){
        temp->arr[i] = tab->arr[i];
    }
}

void* make_new_dynamic_table(int n){
    table_t* tab = malloc(sizeof(table_t) + sizeof(int)*n);
    tab->capacity = n;
    tab->filled = 0;
    return tab;

}
void push_back(void** dt, int n){
    //void* dt1 = dt;
    table_t* tab = NULL;
    tab = (table_t*)*dt;
    if(tab->filled >= (int)(tab->capacity*realloc_threshold)){
        //increase table size
        int new_capacity = ceil(tab->capacity*increase_factor);
        /*
        int new_arr[new_capacity];
        for(int i = 0 ; i < tab->filled; i++){
            new_arr[i] = tab->arr[i];
        }
        tab->arr = new_arr;
        */
        table_t* temp = (table_t*)make_new_dynamic_table(new_capacity);
        temp->filled = tab->filled;
        copyArray(tab, temp);
        free(tab);
        tab = NULL;
        dt = NULL;
        dt = (void**)&temp;  
    }else{
        tab->arr[tab->filled] = n;
        tab->filled += 1;
    }


}

void pop_back(void** dt){
    table_t* tab = NULL;
    tab = (table_t*)*dt;
    if(tab->filled == 0)
        return;
    tab->arr[tab->filled] = -1;
    tab->filled -= 1;  
    if(tab->filled <= (int)(tab->capacity*dealloc_threshold)){
        int new_capacity = tab->capacity*dealloc_threshold;
        
    }  

    /*
    if((float)(tab->filled/tab->capacity) <= threshold){
        //decrease table size
    }else{
        if(tab->filled > 0){
            tab->filled -= 1;
        }
        
    }
    */

}