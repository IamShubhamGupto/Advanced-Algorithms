#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"dyntable_impl.h"

#define realloc_threshold 1.0000000
#define dealloc_threshold 0.2500000     
#define increase_factor 1.5000000
#define decrease_factor 0.2500000
// WITH STRUCTURE HACKING
#define DEBUG 0

//unsigned long long int copies = 0;

struct table {
    int capacity_;
    int filled_;
    int array_[0];
};
typedef struct table table_t;

static void copyArray(table_t* tab, table_t* temp, int n);

static void copyArray(table_t* tab, table_t* temp, int n){
    //if(DEBUG)
    //copies++;
    int i;
    if(n){
        for(i = 0 ; i < tab->filled_; i++){
            temp->array_[i] = tab->array_[i];
        }
    }else{
        for(i = 0 ; i < temp->capacity_; i++){
            temp->array_[i] = tab->array_[i];
        }
    }
    
}

void* make_new_dynamic_table(int size){
    table_t* tab = malloc(sizeof(*tab) + sizeof(int)*(size+1));
    tab->capacity_ = size;
    tab->filled_ = 0;
    for(int i = 0 ; i < size; i++){
        tab->array_[i] = -1;
    }
    return tab;

}
void push_back(void** dt, int new_value){
    //void* dt1 = dt;
    table_t* tab = NULL;
    tab = (table_t*)*dt;
    if(((float)tab->filled_/tab->capacity_) >= realloc_threshold){
        //increase table size
        int new_capacity = ceil(tab->capacity_*increase_factor);
        table_t* temp = (table_t*)make_new_dynamic_table(new_capacity);
        if(DEBUG){
            printf("New size after push_back %d\n",new_capacity);
        }
        temp->filled_ = tab->filled_;
        copyArray(tab, temp, 1);
        temp->array_[tab->filled_] = new_value;
        temp->filled_++;
        free(*dt);
        *dt = NULL;
        *dt = (void*)temp; 
    }else{
        tab->array_[tab->filled_] = new_value;
        tab->filled_ += 1;
        if(DEBUG && tab->array_[tab->filled_] != -1){
            printf("push_back SOMETHING IS WRONG !!! %d %d \n",tab->array_[tab->filled_], tab->filled_);
            //exit(0);
        }
    }


}

void pop_back(void** dt){
    table_t* tab = NULL;
    tab = (table_t*)(*dt);
    if(tab->filled_ == 0)
        return;    
    tab->array_[tab->filled_] = -1;
    tab->filled_ -= 1;  
    if(((float)tab->filled_/tab->capacity_) <= dealloc_threshold){
        int new_capacity = tab->capacity_*decrease_factor;
        if(DEBUG){
            printf("New size after pop_back %d\n",new_capacity);
        }
        if(new_capacity > 0){
            table_t* temp = (table_t*)make_new_dynamic_table(new_capacity);
            temp->filled_ = tab->filled_;
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