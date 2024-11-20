#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NODES 7
#define INF 100000
//void bfs(int startVertex, int distance[NODES][NODES]) ;

struct node 
{
    int vertex;
    struct node* next;
};

struct node* graph[NODES];
char* cities[]={"Everett","Seattle","Olympia","Portland","Centralia","North Bend","Spokane"};


struct node* createnode(int vertex)
{
    struct node* nn=(struct node*)malloc(sizeof(struct node));
    nn->vertex=vertex;
    nn->next=NULL;
    return nn;
}

void addEdge(int src,int dest) 
{
    struct node* nn=createnode(dest);
    nn->next=graph[src];
    graph[src]=nn;
}

void printAdjacencyList() 
{   
    int i;
    printf("Adjacency List:\n");
    for(i=0;i<NODES;i++) {
        printf("%s: ",cities[i]);
        struct node* temp=graph[i];
        while(temp)
         {
            printf("%s -> ",cities[temp->vertex]);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}
struct queue
{
    int items[NODES];
    int front,rear;
};

struct queue* createqueue()
{
    struct queue* nq=(struct queue*)malloc(sizeof(struct queue));
    nq->front=-1;
    nq->rear=-1;
    return nq;
}

int isEmpty(struct queue* q)
{
    return q->rear==-1;
}

void enqueue(struct queue* q,int value)
{
if(q->rear==NODES-1)
{
    return;
}
else
{
if(q->front==-1)
{
    q->front=0;
}
q->rear++;
q->items[q->rear]=value;
}
}

int dequeue(struct queue* q) 
{
int item;
if(isEmpty(q))
{
return -1;
} 
else 
{
item=q->items[q->front];
q->front++;
if(q->front>q->rear)
{
q->front = q->rear = -1;
}
return item;
}
}

void printQueue(struct queue* q)
{
printf("Queue: ");
for(int i=q->front;i<=q->rear;i++)
{
printf("%s ",cities[q->items[i]]);
}
printf("\n");
}

void bfs(int startVertex, int distance[NODES][NODES]) 
{
int visited[NODES]={0};
int parent[NODES];
int i;
for(i=0;i<NODES;i++) 
{
parent[i]=-1;
distance[startVertex][i]=INF;
}
struct queue* queue=createqueue();
visited[startVertex]=1;
distance[startVertex][startVertex]=0;
enqueue(queue,startVertex);
printf("\nBFS starting from %s:\n", cities[startVertex]);
while (!isEmpty(queue)) 
{
int currentVertex=dequeue(queue);
printf("\nDequeued: %s\n",cities[currentVertex]);
struct node* temp=graph[currentVertex];
while(temp) 
{
int adjVertex=temp->vertex;
if (!visited[adjVertex])
{
visited[adjVertex]=1;
distance[startVertex][adjVertex]=distance[startVertex][currentVertex]+1;
parent[adjVertex]=currentVertex;
enqueue(queue,adjVertex);
printf("Visited %s,Distance: %d,Parent: %s\n",cities[adjVertex],distance[startVertex][adjVertex],cities[currentVertex]);


}
temp=temp->next;
}

printf("\nParent array: ");
for (i=0;i<NODES;i++) 
{
if(parent[i]==-1) 
{
printf("None ");
} 
else 
{
printf("%s ", cities[parent[i]]);
}
}
//printf("\n");
}
}

void distanceMatrix(int distance[NODES][NODES]) 
{
    int i;
for(i=0;i<NODES;i++) {
        for (int j = 0; j <NODES; j++) {
            distance[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (int i = 0; i < NODES; i++) {
        bfs(i, distance);
    }
    printf("\nFinal Distance Matrix:\n");
    printf("       ");
    for (int i = 0; i < NODES; i++) {
        printf("%10s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < NODES; i++) {
        printf("%10s", cities[i]);
        for (int j = 0; j <NODES; j++) {
            if (distance[i][j] == INF) {
                printf("%10s", "INF");
            } else {
                printf("%10d", distance[i][j]);
            }
        }
        printf("\n");
    }
}



int main()
{
    // Create the graph based on the image
    addEdge(0, 1); // Everett - Seattle
    addEdge(0, 5); // Everett - North Bend
    addEdge(0, 6); // Everett - Spokane
    addEdge(1, 2); // Seattle - Olympia
    addEdge(2, 3); // Olympia - Portland
    addEdge(2, 4); // Olympia - Centralia
    addEdge(4, 6); // Centralia - Spokane
    addEdge(5, 6); // North Bend - Spokane
    printAdjacencyList();

    int startVertex;
    printf("Enter the starting city (0: Everett, 1: Seattle, 2: Olympia, 3: Portland, 4: Centralia, 5: North Bend, 6: Spokane): ");
    scanf("%d", &startVertex);
    int distance[NODES][NODES];
    //bfs(startVertex,distance);
    distanceMatrix(distance);
   

    return 0;
}


