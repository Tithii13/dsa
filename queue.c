#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Queue {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

void enqueue(Queue* queue, int data) {
    if (queue->rear < MAX_SIZE) {
        queue->data[queue->rear++] = data;
    }
}

int dequeue(Queue* queue) {
    if (!isEmpty(queue)) {
        return queue->data[queue->front++];
    }
    return -1;
}

typedef struct HoldingTrack {
    Queue* queue;
} HoldingTrack;

HoldingTrack* createHoldingTrack() {
    HoldingTrack* track = (HoldingTrack*)malloc(sizeof(HoldingTrack));
    track->queue = createQueue();
    return track;
}

void addToHoldingTrack(HoldingTrack* track, int data) {
    enqueue(track->queue, data);
}

int removeFromHoldingTrack(HoldingTrack* track) {
    return dequeue(track->queue);
}

void rearrangeCars(Queue* mainQueue, HoldingTrack* tracks, int k) {
    int expectedStation = 1;

    while (!isEmpty(mainQueue) || expectedStation <= k) {
        while (!isEmpty(mainQueue)) {
            int car = dequeue(mainQueue);
            if (car == expectedStation) {
                enqueue(mainQueue, car);
                expectedStation++;
            } else {
                addToHoldingTrack(&tracks[car - 1], car);
            }
        }

        for (int i = 0; i < k; i++) {
            while (!isEmpty(tracks[i].queue) && tracks[i].queue->data[tracks[i].queue->front] == expectedStation) {
                enqueue(mainQueue, removeFromHoldingTrack(&tracks[i]));
                expectedStation++;
            }
        }
    }
}

void freeQueue(Queue* queue) {
    free(queue);
}

void freeHoldingTracks(HoldingTrack* tracks, int k) {
    for (int i = 0; i < k; i++) {
        freeQueue(tracks[i].queue);
    }
    free(tracks);
}

int main() {
    Queue* mainQueue = createQueue();
    int k = 3; 
    HoldingTrack* tracks = (HoldingTrack*)malloc(k * sizeof(HoldingTrack));

    for (int i = 0; i < k; i++) {
        tracks[i] = *createHoldingTrack();
    }

    enqueue(mainQueue, 5);
    enqueue(mainQueue, 8);
    enqueue(mainQueue, 1);
    enqueue(mainQueue, 7);
    enqueue(mainQueue, 4);
    enqueue(mainQueue, 2);
    enqueue(mainQueue, 9);
    enqueue(mainQueue, 6);
    enqueue(mainQueue, 3);

    rearrangeCars(mainQueue, tracks, k);

    printf("Output track: ");
    for (int i = mainQueue->front; i < mainQueue->rear; i++) {
        printf("%d ", mainQueue->data[i]);
    }
    printf("\n");

    freeQueue(mainQueue);
    freeHoldingTracks(tracks, k);

    return 0;
}
