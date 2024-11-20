#include <stdio.h>
#include <stdlib.h>
#define MAX_PETROL_PUMPS 100
struct PetrolPump {
 int petrol;
 int distance;
};
struct CircularQueue {
 int front;
 int rear;
 struct PetrolPump items[MAX_PETROL_PUMPS];
};
void initializeQueue(struct CircularQueue *queue) {
 queue->front = -1;
 queue->rear = -1;
}
int isEmpty(struct CircularQueue *queue) {
 return queue->front == -1;
}
int isFull(struct CircularQueue *queue) {
 return (queue->rear + 1) % MAX_PETROL_PUMPS
== queue->front;
}
void enqueue(struct CircularQueue *queue, struct PetrolPump pump) {
 if (isFull(queue)) {
 printf("Queue is full!\n");
 return;
 }
 if (isEmpty(queue)) {
 queue->front = 0;
 }
 queue->rear = (queue->rear + 1) % MAX_PETROL_PUMPS;
 queue->items[queue->rear] = pump;
}
struct PetrolPump dequeue(struct CircularQueue *queue) {
 if (isEmpty(queue)) {
 printf("Queue is empty!\n");
 return queue->items[0]; // Dummy return value
 }
 struct PetrolPump pump = queue->items[queue->front];
 if (queue->front == queue->rear) {
 initializeQueue(queue);
 } else {
 queue->front = (queue->front + 1) % MAX_PETROL_PUMPS;
 }
 return pump;
}
int findFirstCircularTour(struct PetrolPump pumps[], int n) {
 struct CircularQueue queue;
 initializeQueue(&queue);
 int currentPetrol = 0;
 int startingIndex = 0;
 for (int i = 0; i < n; i++) {
 enqueue(&queue, pumps[i]);
 currentPetrol += pumps[i].petrol - pumps[i].distance;
 if (currentPetrol < 0) {
 while (!isEmpty(&queue) && currentPetrol < 0) {
 struct PetrolPump removedPump = dequeue(&queue);
 currentPetrol -= removedPump.petrol - removedPump.distance;
 startingIndex = (startingIndex + 1) % n;
 }
 }
 }
 return currentPetrol >= 0 ? startingIndex : -1;
}
int main() {
int i;
 struct PetrolPump pumps[] = {{4, 6}, {6, 5}, {7, 3}, {4, 5}};
 int n = sizeof(pumps) / sizeof(pumps[0]);
 int startingIndex = findFirstCircularTour(pumps, n);
 
 if (startingIndex != -1) {
 printf("The first point from where the truck can complete the circle is %d\n", startingIndex + 1);
 printf("Complete tour: ");
 for (int i = 0; i < n; i++) {
 printf("%d->", (startingIndex + i) % n + 1);
 }
 printf("%d\n", startingIndex + 1);
 } else {
 printf("No circular tour is possible.\n");
 }
 return 0;
}