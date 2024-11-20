#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NOD 7

struct node
{
    int vertex;
    struct node* next;
};

struct node* graph[NOD];
char* cities[]={"Everett","Seattle","Olympia","Portland","Centaralia","North Bend","Spokane"};

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

void printlist()
{
    printf("ADJACENCY LIST: \n");
    for(int i=0;i<NOD;i++)
    {
    printf("%s-> ",cities[i]);
    struct node* temp=graph[i];
    while(temp)
    {
        printf("%s -> ",cities[temp->vertex]);
        temp=temp->next;
    }
    printf("NULL\n");
    }
}
int main()
{
        addEdge(0, 1); // Everett - Seattle
    addEdge(0, 5); // Everett - North Bend
    addEdge(0, 6); // Everett - Spokane
    addEdge(1, 2); // Seattle - Olympia
    addEdge(2, 3); // Olympia - Portland
    addEdge(2, 4); // Olympia - Centralia
    addEdge(4, 6); // Centralia - Spokane
    addEdge(5, 6); // North Bend - Spokane
    printlist();
return 0;

}