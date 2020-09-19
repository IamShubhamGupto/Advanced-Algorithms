#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"dyntable_impl.h"

#define realloc_threshold 1
#define dealloc_threshold 0.2500000     
#define increase_factor 1.5000000
#define decrease_factor 0.2500000

#define DEBUG 0
struct table {
    int capacity;
    int filled;
    int arr[0];
};
typedef struct table table_t;

static void copyArray(table_t* tab, table_t* temp, int n);

static void copyArray(table_t* tab, table_t* temp, int n){
    int i;
    if(n){
        for(i = 0 ; i < tab->filled; i++){
            temp->arr[i] = tab->arr[i];
        }
    }else{
        for(i = 0 ; i < temp->capacity; i++){
            temp->arr[i] = tab->arr[i];
        }
    }
    
}

void* make_new_dynamic_table(int size){
    table_t* tab = malloc(sizeof(*tab) + sizeof(int)*(size+1));
    tab->capacity = size;
    tab->filled = 0;
    for(int i = 0 ; i < size; i++){
        tab->arr[i] = -1;
    }
    return tab;

}
void push_back(void** dt, int n){
    //void* dt1 = dt;
    table_t* tab = NULL;
    tab = (table_t*)*dt;
    if(tab->filled >= (int)(tab->capacity*realloc_threshold)){
        //increase table size
        int new_capacity = ceil(tab->capacity*increase_factor);
        table_t* temp = (table_t*)make_new_dynamic_table(new_capacity);
        if(DEBUG){
            printf("New size after push_back %d\n",new_capacity);
        }
        temp->filled = tab->filled;
        copyArray(tab, temp, 1);
        free(*dt);
        *dt = NULL;
        *dt = (void*)temp; 
    }else{
        tab->arr[tab->filled] = n;
        tab->filled += 1;
        if(DEBUG && tab->arr[tab->filled] != -1){
            printf("push_back SOMETHING IS WRONG !!! %d %d \n",tab->arr[tab->filled], tab->filled);
            //exit(0);
        }
    }


}

void pop_back(void** dt){
    table_t* tab = NULL;
    tab = (table_t*)(*dt);
    if(tab->filled == 0)
        return;    
    tab->arr[tab->filled] = -1;
    tab->filled -= 1;  
    if(tab->filled <= (int)(tab->capacity*dealloc_threshold)){
        int new_capacity = ceil(tab->capacity*dealloc_threshold);
        if(DEBUG){
            printf("New size after pop_back %d\n",new_capacity);
        }
        if(new_capacity > 0){
            table_t* temp = (table_t*)make_new_dynamic_table(new_capacity);
            temp->filled = tab->filled;
            copyArray(tab, temp, 0);
            free(*dt);
            *dt = NULL;
            *dt = (void*)temp;
        }else{
            table_t* temp = (table_t*)make_new_dynamic_table(1);
            free(*dt);
            *dt = NULL;
            *dt = (void*)temp;
        }
        
    } 
    if(DEBUG)
        printf("after pop_back op addr %p\n",dt);

}