#include<stdio.h>
#include<stdlib.h>
struct node{
    int n;
    struct node* next;
};
typedef struct node node_t;

struct list{
    node_t* head;
};
typedef struct list list_t;

list_t* initialize_list();
node_t* initialize_node(int);
void push(list_t*, int);
void pop(list_t*);
int is_empty(list_t*);
void destroy_list(list_t*);
int get_max_flow(int**,int, int, int);
int BFS(int**, int , int , int* , int );

list_t* initialize_list(){
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->head = NULL;
    return list;
}
node_t* initialize_node(int n){
    node_t* new = (node_t*)malloc(sizeof(node_t));
    new->n = n;
    new->next = NULL;
    return new;
}
void push(list_t* list, int n){
    node_t* new = initialize_node(n);
    new->next = list->head;
    list->head = new;
}

void pop(list_t* list){
    node_t* temp = list->head;
    if(temp == NULL)
        return;
    if(temp->next = NULL){
        free(temp);
        list->head = NULL;
        return;
    }
    node_t* prev =NULL;
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }
    if(prev!=NULL && temp != NULL){
        free(temp);
        prev->next = NULL;
        return;
    }
    if(prev == NULL){
        free(temp);
        list->head = NULL;
        return;
    }
    
}
int is_empty(list_t* list){
    if(list->head == NULL){
        return 1;
    }
    return 0;
}
void destroy_list(list_t* list){
    node_t* temp = list->head;
    node_t* temp2 = NULL;
    while(temp != NULL){
        temp2 = temp;
        temp = temp->next;
        free(temp2);
        temp2 = NULL;
    }
}
int min(int a, int b){
    if(a > b)
        return b;
    return a;
}
int main(){
    int V;
    int i,j;
    scanf("%d",&V);
    int** adj_matrix = (int**)malloc(V*sizeof(int*));
    for(i = 0; i < V; i++){
        adj_matrix[i] = (int*)malloc(V*sizeof(int));
        for(j = 0; j < V; j++){
            scanf("%d",&adj_matrix[i][j]);
        }
    }
    int result = get_max_flow(adj_matrix,V,0, V-1);
    printf("Max flow of network = %d\n",result);
    for(i = 0; i < V; i++){
        free(adj_matrix[i]);
    }
    free(adj_matrix);
    
    return 0;
}

int get_max_flow(int** adj_matrix,int V, int source, int sink){
    int** r_adj_matrix = (int**)malloc(V*sizeof(int*));
    int i,j;
    for(i = 0; i < V; i++){
        r_adj_matrix[i] = (int*)malloc(V*sizeof(int));
        for(j = 0; j < V; j++){
            r_adj_matrix[i][j] = adj_matrix[i][j];
        }
    }

    int* parent = (int*)malloc(V*sizeof(int));
    int max_flow = 0;
    int path_flow;
    while(BFS(r_adj_matrix, source, sink, parent, V)){
        path_flow = (1e9)+7;
        
        for(i = sink; i != source; i = parent[i]){
            j = parent[i];
            path_flow = min(path_flow, r_adj_matrix[i][j]);
        }
        for(i = sink; i != source; i = parent[i]){
            j = parent[i];
            r_adj_matrix[i][j] -= path_flow;
            r_adj_matrix[j][i] += path_flow;

        }
        max_flow += path_flow;
    }
    

    free(parent);
    for(i = 0; i < V; i++){
        free(r_adj_matrix[i]);
    }
    free(r_adj_matrix);
    return max_flow;
}

int BFS(int** r_adj_matrix, int source, int sink, int* parent, int V){
    int* visited = (int*)malloc(V*sizeof(int));
    
    int i,j,u,v;
    for(i = 0; i < V; i++){
        visited[i] = 0;
    }
    list_t* queue = initialize_list();
    push(queue, source);
    visited[source] = 1;
    parent[source] = -1;
    while(!is_empty(queue)){
        u = queue->head->n;
        pop(queue);
        for(v = 0; v < V; v++){
            if(!visited[v] && r_adj_matrix[u][v] > 0){
                    push(queue, v);
                    parent[v] = u;
                    visited[v] = 1;

            }
        }
    }
    int ans = visited[sink];
    destroy_list(queue);
    free(queue);
    free(visited);
    return ans;

}