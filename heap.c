#include <stdio.h>

#define MAX_SIZE 100  // Define a maximum size for the heap

typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

// Initialize the heap
void initializeHeap(MaxHeap *heap) {
    heap->size = 0;
}

// Heapify up to maintain max-heap property after insertion or increase key
void heapifyUp(MaxHeap *heap, int index) {
    int parent = (index - 1) / 2;
    if (index && heap->data[parent] < heap->data[index]) {
        // Swap if the parent is smaller than the current node
        int temp = heap->data[parent];
        heap->data[parent] = heap->data[index];
        heap->data[index] = temp;
        // Recur for the parent node
        heapifyUp(heap, parent);
    }
}

// Insert a new key into the heap
void insert(MaxHeap *heap, int key) {
    if (heap->size == MAX_SIZE) {
        printf("Heap is full\n");
        return;
    }
    // Insert the new key at the end
    heap->data[heap->size] = key;
    heap->size += 1;
    // Move up to maintain the heap property
    heapifyUp(heap, heap->size - 1);
}

// Heapify down to maintain max-heap property after removal or decrease key
void heapifyDown(MaxHeap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    if (largest != index) {
        int temp = heap->data[index];
        heap->data[index] = heap->data[largest];
        heap->data[largest] = temp;
        heapifyDown(heap, largest);
    }
}

// Increase key at a given index
void increaseKey(MaxHeap *heap, int index, int newKey) {
    if (newKey < heap->data[index]) {
        printf("New key is smaller than the current key\n");
        return;
    }
    heap->data[index] = newKey;
    heapifyUp(heap, index);
}

// Decrease key at a given index
void decreaseKey(MaxHeap *heap, int index, int newKey) {
    if (newKey > heap->data[index]) {
        printf("New key is larger than the current key\n");
        return;
    }
    heap->data[index] = newKey;
    heapifyDown(heap, index);
}

// Heapsort: Sort the elements of the heap in ascending order
void heapsort(MaxHeap *heap) {
    int originalSize = heap->size;
    for (int i = heap->size - 1; i > 0; i--) {
        // Swap the root (maximum element) with the last element
        int temp = heap->data[0];
        heap->data[0] = heap->data[i];
        heap->data[i] = temp;

        // Reduce the heap size by one
        heap->size--;

        // Heapify the root to maintain the max-heap property
        heapifyDown(heap, 0);
    }
    heap->size = originalSize;  // Restore original heap size
}

// Print the heap
void printHeap(MaxHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    MaxHeap heap;
    initializeHeap(&heap);

    // Insert elements into the heap
    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 5);
    insert(&heap, 30);
    insert(&heap, 15);

    printf("Heap before sorting: ");
    printHeap(&heap);

    // Perform increase key operation
    increaseKey(&heap, 2, 25);  // Increasing value at index 2 to 25
    printf("Heap after increasing key: ");
    printHeap(&heap);

    // Perform decrease key operation
    decreaseKey(&heap, 1, 18);  // Decreasing value at index 1 to 18
    printf("Heap after decreasing key: ");
    printHeap(&heap);

    // Perform heapsort
    heapsort(&heap);

    printf("Heap after sorting: ");
    for (int i = 0; i < heap.size; i++) {
        printf("%d ", heap.data[i]);
    }
    printf("\n");

    return 0;
}
