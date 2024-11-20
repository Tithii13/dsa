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
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;
    // Add edge from dest to src (since it's an undirected graph)
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

// BFS function
void bfs(int startVertex) {
    int visited[NUM_NODES] = {0};
    int parent[NUM_NODES];
    int distance[NUM_NODES];

    for (int i = 0; i < NUM_NODES; i++) {
        parent[i] = -1;
        distance[i] = INF;
    }

    Queue* queue = createQueue();

    visited[startVertex] = 1;
    distance[startVertex] = 0;
    enqueue(queue, startVertex);

    printf("Starting BFS from %s\n", cities[startVertex]);
    printf("Initial Queue: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%s ", cities[queue->items[i]]);
    }
    printf("\n");

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("Dequeued: %s\n", cities[currentVertex]);

        Node* temp = graph[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                distance[adjVertex] = distance[currentVertex] + 1;
                parent[adjVertex] = currentVertex;
                enqueue(queue, adjVertex);

                printf("Visited %s, Distance: %d, Parent: %s\n", cities[adjVertex], distance[adjVertex], cities[currentVertex]);
            }
            temp = temp->next;
        }

        // Print queue state
        printf("Queue: ");
        for (int i = queue->front; i <= queue->rear; i++) {
            printf("%s ", cities[queue->items[i]]);
        }
        printf("\n");
    }

    // Print final distances and parents
    printf("\nFinal Distance Array:\n");
    for (int i = 0; i < NUM_NODES; i++) {
        printf("Distance to %s: %d\n", cities[i], distance[i]);
    }

    printf("\nFinal Parent Array:\n");
    for (int i = 0; i < NUM_NODES; i++) {
        if (parent[i] != -1)
            printf("Parent of %s: %s\n", cities[i], cities[parent[i]]);
        else
            printf("Parent of %s: None\n", cities[i]);
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

    int startVertex;
    printf("Enter the starting city (0: Everett, 1: Seattle, 2: Olympia, 3: Portland, 4: Centralia, 5: North Bend, 6: Spokane): ");
    scanf("%d", &startVertex);

    bfs(startVertex);

    return 0;
}
