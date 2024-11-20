#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *createnode(int data) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node *insert(struct node *node, int key) {
    // Create a new node if the current node is NULL
    if (node == NULL) {
        return createnode(key);
    }

    // Insert into the correct subtree
    if (key < node->data) {
        node->left = insert(node->left, key);
    } else if (key > node->data) {
        node->right = insert(node->right, key);
    }

    return node; // Return the unchanged node pointer
}

void inorder(struct node *node) {
    if (node == NULL) {
        return;
    }

    inorder(node->left);
    printf(" %d", node->data);
    inorder(node->right);
}

int main() {
    struct node *root = NULL;
    int key;

    while (1) {
        printf("Enter the data (-1 to stop): ");
        scanf("%d", &key);
        
        if (key == -1) {
            break; // Stop input
        }

        // Insert the key into the tree
        root = insert(root, key);
    }

    printf("Inorder Traversal:");
    inorder(root); // Print the inorder traversal
    printf("\n");

    return 0;
}
