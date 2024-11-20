#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_NODES 7
#define INF 1000000

// Define the structure for each node in the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Define the graph as an array of adjacency lists
Node* graph[NUM_NODES];
char* cities[] = {"Everett", "Seattle", "Olympia", "Portland", "Centralia", "North Bend", "Spokane"};

// Queue structure for BFS
typedef struct Queue {
    int items[NUM_NODES];
    int front, rear;
} Queue;

// Function to create a new node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to add edge to the graph
void addEdge(int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph[dest];
    graph[dest] = newNode;
}

// Initialize a queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = -1;
    return q;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->rear == -1;
}

// Add to queue
void enqueue(Queue* q, int value) {
    if (q->rear == NUM_NODES - 1)
        return;
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Remove from queue
int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

// BFS function to compute shortest distances from a source vertex
void bfs(int startVertex, int distance[NUM_NODES][NUM_NODES]) {
    int visited[NUM_NODES] = {0};
    Queue* queue = createQueue();

    visited[startVertex] = 1;
    distance[startVertex][startVertex] = 0;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        Node* temp = graph[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                distance[startVertex][adjVertex] = distance[startVertex][currentVertex] + 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Function to create the distance matrix for all pairs of nodes
void computeDistanceMatrix(int distance[NUM_NODES][NUM_NODES]) {
    // Initialize distances to INF initially
    for (int i = 0; i < NUM_NODES; i++) {
        for (int j = 0; j < NUM_NODES; j++) {
            distance[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Run BFS for each node to fill the distance matrix
    for (int i = 0; i < NUM_NODES; i++) {
        bfs(i, distance);
    }

    // Print the distance matrix
    printf("Distance Matrix:\n");
    printf("       ");
    for (int i = 0; i < NUM_NODES; i++) {
        printf("%10s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < NUM_NODES; i++) {
        printf("%10s", cities[i]);
        for (int j = 0; j < NUM_NODES; j++) {
            if (distance[i][j] == INF) {
                printf("%10s", "INF");
            } else {
                printf("%10d", distance[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    // Create the graph based on the image
    addEdge(0, 1); // Everett - Seattle
    addEdge(0, 5); // Everett - North Bend
    addEdge(0, 6); // Everett - Spokane
    addEdge(1, 2); // Seattle - Olympia
    addEdge(2, 3); // Olympia - Portland
    addEdge(2, 4); // Olympia - Centralia
    addEdge(4, 6); // Centralia - Spokane
    addEdge(5, 6); // North Bend - Spokane

    int distance[NUM_NODES][NUM_NODES];
    computeDistanceMatrix(distance);

    return 0;
}
