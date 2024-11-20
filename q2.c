#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 10

struct queue {
    int data[SIZE];
    int front;
    int rear;
};

// Function to initialize the queue
struct queue* initialize() {
    struct queue* newQueue = (struct queue*)malloc(sizeof(struct queue));
    newQueue->front = -1;
    newQueue->rear = -1;
    return newQueue;
}

// Function to check if the queue is full
bool isFull(struct queue* q) {
    if (q->rear == SIZE - 1) {
        return true;
    }
    return false;
}

// Function to check if the queue is empty
bool isEmpty(struct queue* q) {
    if (q->front == -1 || q->front > q->rear) {
        return true;
    }
    return false;
}

// Function to enqueue an element into the queue
void enqueue(struct queue* q, int newdata) {
    if (isFull(q)) {
        printf("\nQUEUE IS FULL\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = newdata;
    printf("\nEnqueued: %d\n", newdata);
}

void dequeue(struct queue* q)
{
    if(isEmpty(q))
    {
        printf("QUEUE IS EMPTY\n");
        return;
    }
    int data=q->front;
    if(q->front==q->rear)
    {
        q->front=q->rear=-1;
    }
    else{
        q->front++;
    }
    
}
// Function to display the queue
void display(struct queue* q) {
    if (isEmpty(q)) {
        printf("\nQUEUE IS EMPTY!\n");
        return;
    }
    printf("\nQueue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}


int main() {
    struct queue* q1 = initialize(); // Initialize queue

    enqueue(q1, 1);
    enqueue(q1, 2);
    enqueue(q1, 3);

    display(q1); // Display the queue

    dequeue(q1);
    display(q1);

    return 0;
}
