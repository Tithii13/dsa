#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert a node in sorted order and return the new head
struct Node* insertSorted(struct Node* head, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL || head->data >= data) {
        newNode->next = head;
        if (head != NULL) head->prev = newNode;
        return newNode;  // New node is the new head
    }
    
    struct Node* current = head;
    
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }
    
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;

    return head;  // Head remains unchanged
}

// Remove duplicate nodes from the sorted list
void removeDuplicates(struct Node* head) {
    if (head == NULL) return;
    
    struct Node* current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            if (current->next != NULL) {
                current->next->prev = current;
            }
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Merge two sorted doubly linked lists and return the merged list
struct Node* mergeSorted(struct Node* head1, struct Node* head2) {
   if (head1 == NULL) 
   {
    return head2;
   }
if (head2 == NULL) 
{
    return head1;
    }


    struct Node* result = NULL;

    if (head1->data <= head2->data) {
        result = head1;
        result->next = mergeSorted(head1->next, head2);
        if (result->next) result->next->prev = result;
    } else {
        result = head2;
        result->next = mergeSorted(head1, head2->next);
        if (result->next) result->next->prev = result;
    }

    return result;
}

// Function to print the doubly linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // Insert into list1
    list1 = insertSorted(list1, 10);
    list1 = insertSorted(list1, 20);
    list1 = insertSorted(list1, 10);  // Duplicate value
    list1 = insertSorted(list1, 30);

    // Insert into list2
    list2 = insertSorted(list2, 5);
    list2 = insertSorted(list2, 15);
    list2 = insertSorted(list2, 25);

    printf("List 1: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    // Remove duplicates from list1
    removeDuplicates(list1);
    printf("List 1 after removing duplicates: ");
    printList(list1);

    // Merge the lists
    struct Node* mergedList = mergeSorted(list1, list2);
    printf("Merged List: ");
    printList(mergedList);

    return 0;
}
