#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define the Queue structure
typedef struct Queue {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function to create a new queue and initialize its members
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation for queue failed\n");
        exit(1);
    }
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    if (queue == NULL) {
        printf("Queue is NULL in isEmpty()\n");
        exit(1);
    }
    return queue->front == queue->rear;
}

// Function to check if the queue is full
int isFull(Queue* queue) {
    if (queue == NULL) {
        printf("Queue is NULL in isFull()\n");
        exit(1);
    }

    printf("Checking if queue is full: front=%d, rear=%d, MAX_SIZE=%d\n", queue->front, queue->rear, MAX_SIZE); // Debug print

    return queue->rear >= MAX_SIZE;
}

// Function to add an element to the queue
void enqueue(Queue* queue, int data) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot add %d\n", data);
    } else {
        queue->data[queue->rear++] = data;
        printf("Enqueued %d, new rear=%d\n", data, queue->rear); // Debug print
    }
}

// Function to remove an element from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    } else {
        int value = queue->data[queue->front++];
        printf("Dequeued %d, new front=%d\n", value, queue->front); // Debug print
        return value;
    }
}

int main() {
    // Create the main queue
    Queue* mainQueue = createQueue();
    if (mainQueue == NULL) {
        printf("Failed to create main queue\n");
        return 1;
    }

    // Enqueue some cars into the main queue
    enqueue(mainQueue, 5);
    enqueue(mainQueue, 8);
    enqueue(mainQueue, 1);

    // Dequeue to test functionality
    dequeue(mainQueue);
    dequeue(mainQueue);

    // Check if the queue works as expected
    dequeue(mainQueue);

    // Free memory
    free(mainQueue);

    return 0;
}
