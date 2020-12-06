// Given a directed graph with a source and a sink and capacities assigned to the edges, determine the maximum flow from the source to the sink.
// For each edge, the flow must not exceed the edge's capacity.
// For each node, the incoming flow must be equal to the outgoing flow.

#include<stdio.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX 1000
#define INFI 1000000000

int n, e; // nodes and edges
int capacity[MAX][MAX];
int flow[MAX][MAX];
int colour[MAX]; // needed for BFS
int pred[MAX]; // to store path

int min(int a, int b)
{
    return a<b? a:b;
}

int head;
int tail;
int queue[MAX+2];

void enqueue(int data)
{
    queue[tail++] = data; // add elem to tail
    colour[data] = GRAY;
}

int dequeue()
{
    int x = queue[head++]; // remove element from front
    colour[x] = BLACK;
    return x;
}

int BFS(int start, int node)
{
    int u, v;
    for(u=0; u<n; ++u)
        colour[u] = WHITE;

    head = tail = 0;
    enqueue(start);
    pred[start] = -1;

    while(head != tail)
    {
        u = dequeue();
        for(v=0; v<n; ++v)
        {
            if(colour[v] == WHITE && capacity[u][v] - flow[u][v] > 0)
            {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
    return colour[node] == BLACK; //goal reached
}

int max_flow(int source, int sink)
{
    int max = 0;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            flow[i][j] = 0;
        }
    }

    while(BFS(source, sink))
    {
        int increment = INFI;
        for(int u=n-1; pred[u]>=0; u=pred[u])
        {
            increment = min(increment, capacity[pred[u]][u]-flow[pred[u]][u]);
        }

        for(int u=n-1; pred[u]>=0; u=pred[u])
        {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }

        max += increment;
    }
    return max;
}

void read_input()
{
    FILE *file = fopen("ford_fulkerson.txt", "r");
    fscanf(file, "%d %d", &n, &e); // <nodes> <edges>
    //printf("\nNumber of Vertices : %d   Edges : %d",n,e);

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
            capacity[i][j] = 0;
    }

    int i, j, cap;
    for(int k=0; k<e; ++k)
    {
        fscanf(file, "%d %d %d", &i, &j, &cap); // <node> <node> <capacity>
        capacity[i][j] = cap;
        //printf capacity
    }
    fclose(file);
}


int main()
{
    read_input();
    int source = 0, sink = n-1;
    printf("\nMac Flow: %d\n", max_flow(source, sink));

    return 0;
} 