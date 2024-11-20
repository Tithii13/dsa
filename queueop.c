#include <stdio.h>
#include <stdlib.h>

#define MAX_CARS 9
#define MAX_HOLDS 5

struct Queue {
    int items[MAX_CARS];
    int front;
    int rear;
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isQueueEmpty(struct Queue *q) {
    return q->rear < q->front;
}

int isQueueFull(struct Queue *q) {
    return q->rear == MAX_CARS - 1;
}

void enqueue(struct Queue *q, int value) {
    if (!isQueueFull(q)) {
        q->items[++(q->rear)] = value;
    }
}

int dequeue(struct Queue *q) {
    if (!isQueueEmpty(q)) {
        return q->items[q->front++];
    }
    return -1;
}

int main() {
    int incoming[MAX_CARS] = {5, 8, 1, 7, 4, 2, 9, 6, 3};
    struct Queue holds[MAX_HOLDS];
    int holdsCount = 0;
    int out = 0;

    printf("Initial input track: ");
    for (int i = 0; i < MAX_CARS; i++) {
        printf("%d ", incoming[i]);
    }
    printf("\nStarting reordering...\n");

    for (int j = 0; j < MAX_CARS; j++) {
        int cur = incoming[j];

        if (cur - 1 == out) {
            out = cur;
            int move;

            do {
                move = 0;
                for (int i = 0; i < holdsCount; i++) {
                    if (!isQueueEmpty(&holds[i]) && holds[i].items[holds[i].front] - 1 == out) {
                        out = dequeue(&holds[i]);
                        move = 1;
                    }
                }
            } while (move);
        } else {
            int pushed = 0;
            for (int i = 0; i < holdsCount; i++) {
                if (isQueueEmpty(&holds[i]) || cur < holds[i].items[holds[i].front]) {
                    enqueue(&holds[i], cur);
                    pushed = 1;
                    break;
                }
            }
            if (!pushed && holdsCount < MAX_HOLDS) {
                initQueue(&holds[holdsCount++]);
                enqueue(&holds[holdsCount - 1], cur);
            }
        }
    }

    printf("Reordered output track: ");
    for (int i = 1; i <= MAX_CARS; i++) {
        if (i != 1) printf(" ");
        printf("%d", i);
    }
    printf("\n");

    return 0;
}
