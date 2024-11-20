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

// Function to print the current queue status
void printQueue(Queue* q) {
    printf("Queue: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%s ", cities[q->items[i]]);
    }
    printf("\n");
}

// Function to print the adjacency list of the graph
void printAdjacencyList() {
    printf("Adjacency List:\n");
    for (int i = 0; i < NUM_NODES; i++) {
        printf("%s: ", cities[i]);
        Node* temp = graph[i];
        while (temp) {
            printf("%s -> ", cities[temp->vertex]);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}


// BFS function to compute shortest distances from a source vertex and show queue, parent, and distance status
void bfs(int startVertex, int distance[NUM_NODES][NUM_NODES]) {
    int visited[NUM_NODES] = {0};
    int parent[NUM_NODES];
    for (int i = 0; i < NUM_NODES; i++) {
        parent[i] = -1;
        distance[startVertex][i] = INF;
    }

    Queue* queue = createQueue();
    visited[startVertex] = 1;
    distance[startVertex][startVertex] = 0;
    enqueue(queue, startVertex);

    printf("\nBFS starting from %s:\n", cities[startVertex]);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("\nDequeued: %s\n", cities[currentVertex]);

        Node* temp = graph[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                distance[startVertex][adjVertex] = distance[startVertex][currentVertex] + 1;
                parent[adjVertex] = currentVertex;
                enqueue(queue, adjVertex);

                printf("Visited %s, Distance: %d, Parent: %s\n", cities[adjVertex], distance[startVertex][adjVertex], cities[currentVertex]);
            }
            temp = temp->next;
        }

        // Print queue, distance, and parent status
        printQueue(queue);
        printf("Distance array: ");
        for (int i = 0; i < NUM_NODES; i++) {
            if (distance[startVertex][i] == INF) {
                printf("INF ");
            } else {
                printf("%d ", distance[startVertex][i]);
            }
        }
        printf("\nParent array: ");
        for (int i = 0; i < NUM_NODES; i++) {
            if (parent[i] == -1) {
                printf("None ");
            } else {
                printf("%s ", cities[parent[i]]);
            }
        }
        printf("\n");
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
    printf("\nFinal Distance Matrix:\n");
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

    // Print the adjacency list
    printAdjacencyList();
    
    int distance[NUM_NODES][NUM_NODES];
    computeDistanceMatrix(distance);

    return 0;
}
