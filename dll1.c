#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node* createnode(int newd) {
    struct node* nn = (struct node*)malloc(sizeof(struct node));
    nn->data = newd;
    nn->next = NULL;
    nn->prev = NULL;
    return nn;
}

struct node* inssorted(struct node* head, int newd) {
    struct node* nn = createnode(newd);

    if (head == NULL) {
        return nn;
    }

    if (nn->data <= head->data) {
        nn->next = head;
        head->prev = nn;
        return nn;
    }

    struct node* current = head;

    while (current->next != NULL && current->next->data < newd) {
        current = current->next;
    }

    nn->next = current->next;
    if (current->next != NULL) {
        current->next->prev = nn;
    }
    current->next = nn;
    nn->prev = current;

    return head;
}

struct node* remdup(struct node* head) {
    if (head == NULL) return head;

    struct node* current = head;

    while (current->next != NULL) {
        if (current->data == current->next->data) {
            struct node* temp = current->next;
            current->next = current->next->next;
            if (current->next != NULL) {
                current->next->prev = current;
            }
            free(temp);
        } else {
            current = current->next;
        }
    }

    return head;
}

struct node* mergeSorted(struct node* head1, struct node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct node* result = NULL;

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

void display(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct node* list1 = NULL;
    struct node* list2 = NULL;

    list1 = inssorted(list1, 4);
    display(list1);
    list1 = inssorted(list1, 2);
    display(list1);
    list1 = inssorted(list1, 4);
    display(list1);
    list1 = inssorted(list1, 3);
    display(list1);
    printf("List 1: ");
    display(list1);


    
    list2 = inssorted(list2, 5);
    display(list2);
    list2 = inssorted(list2, 7);
    display(list2);
    list2 = inssorted(list2, 6);
    display(list2);
    printf("List 2: ");
    display(list2);
    
    
    

  

    list1 = remdup(list1);
    printf("List 1 after removing duplicates: ");
    display(list1);

    struct node* mergedList = mergeSorted(list1, list2);
    printf("Merged List: ");
    display(mergedList);

    return 0;
}