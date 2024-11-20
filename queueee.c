#include <stdio.h> 
#include <stdlib.h> 

struct queue { 
    int rear;     
    int front;     
    int size;     
    int *arr; 
}; 

int isEmpty(struct queue *q) {     
    return q->front > q->rear; 
} 

int isFull(struct queue *q) {     
    return q->rear == q->size - 1; 
} 

void enqueue(struct queue *q, int value) {     
    if (isFull(q)) {         
        printf("Cannot insert, queue full.\n");     
    } else {         
        q->arr[++q->rear] = value; 
    } 
} 

int dequeue(struct queue *q) { 
    if (isEmpty(q)) {         
        printf("Cannot dequeue, queue empty.\n");         
        return -1;     
    } else {         
        return q->arr[q->front++]; 
    } 
} 

int peek(struct queue *q) {     
    return isEmpty(q) ? -1 : q->arr[q->front]; 
} 

void createQueue(struct queue *q) {     
    q->front = 0;     
    q->rear = -1;     
    q->size = 20;     
    q->arr = (int *)malloc(sizeof(int) * q->size); 
    if (q->arr == NULL) { 
        printf("Memory allocation failed.\n");
        exit(1);
    }
} 

void printQueue(struct queue *q) { 
    printf("[");
    for (int i = q->front; i <= q->rear; i++) {         
        printf("%d", q->arr[i]);
        if (i != q->rear) { 
            printf(", ");
        }
    }
    printf("]\n"); 
} 

void railwayqueueSort(struct queue *input, struct queue *h1, struct queue *h2, struct queue *output) {     
    int reqd = 9; 
    
    while (reqd >= 1) {         
        int x = peek(input);         
        int y = peek(h1);         
        int z = peek(h2); 

        if (x == reqd) {             
            dequeue(input);             
            enqueue(output, x);             
            reqd--;         
        } else if (y == reqd) {             
            dequeue(h1);             
            enqueue(output, y);             
            reqd--;         
        } else if (z == reqd) {             
            dequeue(h2);             
            enqueue(output, z);             
            reqd--;         
        } else {             
            if (isEmpty(h1) || x < h1->arr[h1->rear]) {                 
                enqueue(h1, x);             
            } else {                 
                enqueue(h2, x);             
            }             
            dequeue(input);         
        } 

        printf("\nH1: ");         
        printQueue(h1);         
        printf("H2: ");         
        printQueue(h2);         
        printf("Output queue: ");         
        printQueue(output);     
    } 
} 

int main() {     
    struct queue *inputQ = (struct queue *)malloc(sizeof(struct queue));     
    struct queue *outputQ = (struct queue *)malloc(sizeof(struct queue));     
    struct queue *h1 = (struct queue *)malloc(sizeof(struct queue));     
    struct queue *h2 = (struct queue *)malloc(sizeof(struct queue));     

    if (inputQ == NULL || outputQ == NULL || h1 == NULL || h2 == NULL) { 
        printf("Memory allocation failed.\n");
        return 1;
    }

    createQueue(inputQ);     
    createQueue(outputQ);     
    createQueue(h1);     
    createQueue(h2); 

    enqueue(inputQ, 5);     
    enqueue(inputQ, 8);     
    enqueue(inputQ, 1);     
    enqueue(inputQ, 7);     
    enqueue(inputQ, 4);     
    enqueue(inputQ, 2);     
    enqueue(inputQ, 9);     
    enqueue(inputQ, 6);     
    enqueue(inputQ, 3); 

    printf("The input queue is: ");     
    printQueue(inputQ); 

    railwayqueueSort(inputQ, h1, h2, outputQ); 

    printf("\nThe output queue is: ");     
    printQueue(outputQ); 

    return 0; 
}
