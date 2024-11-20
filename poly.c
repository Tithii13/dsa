#include <stdio.h>
#include <stdlib.h>

struct node {
    float coef;
    int expo;
    struct node *next;
};

struct node* insert(struct node* head, int co, int ex) {
    struct node *temp;
    struct node *newp=malloc(sizeof(struct node));
    newp->coef=co;
    newp->expo=ex;
    newp->next=NULL;

    if (head == NULL || ex > head->expo) {
        newp->next=head;
        head=newp;
    } else {
        temp=head;
        while (temp->next != NULL && temp->next->expo >= ex) {
            temp=temp->next;
        }
        newp->next=temp->next;
        temp->next=newp;
    }
    return head;
}

struct node* create(struct node *head) {
    int n, i;
    float coef;
    int expo;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i=0; i < n; i++) {
        printf("Enter the coefficient for term %d: ", i + 1);
        scanf("%f", &coef);
        printf("Enter the exponent for term %d: ", i + 1);
        scanf("%d", &expo);
        head=insert(head, coef, expo);
    }
    return head;
}

void print(struct node* head) {
    if (head == NULL) {
        printf("NO polynomial\n");
    } else {
        struct node* temp=head;
        while (temp != NULL) {
            printf("(%.1f, %d)", temp->coef, temp->expo);
            temp=temp->next;
            if (temp != NULL) {
                printf(" + ");
            }
        }
        printf("\n");
    }
}

void add(struct node *head1, struct node *head2) {
    struct node* ptr1=head1;
    struct node* ptr2=head2;
    struct node* head3=NULL;

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->expo == ptr2->expo) {
            head3=insert(head3, ptr1->coef + ptr2->coef, ptr1->expo);
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        } else if (ptr1->expo > ptr2->expo) {
            head3=insert(head3, ptr1->coef, ptr1->expo);
            ptr1=ptr1->next;
        } else {
            head3=insert(head3, ptr2->coef, ptr2->expo);
            ptr2=ptr2->next;
        }
    }

    while (ptr1 != NULL) {
        head3=insert(head3, ptr1->coef, ptr1->expo);
        ptr1=ptr1->next;
    }
    while (ptr2 != NULL) {
        head3=insert(head3, ptr2->coef, ptr2->expo);
        ptr2=ptr2->next;
    }

    printf("Added polynomial is: ");
    print(head3);
}

int main() {
    struct node* head1=NULL;
    struct node* head2=NULL;
    printf("Enter first polynomial\n");
    head1=create(head1);
    printf("Enter second polynomial\n");
    head2=create(head2);

    add(head1, head2);
    return 0;
}