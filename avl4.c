#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* rightr(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct Node* leftr(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getb(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node* insert(struct Node* node, int data) {
    if (node == NULL)
        return createNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int b = getb(node);

    printf("Inserting %d: Critical Node: %d, Balance Factor: %d\n", data, node->data, b);

    if (b > 1 && data < node->left->data)
        return rightr(node);
    if (b > 1 && data > node->left->data) {
        node->left = leftr(node->left);
        return rightr(node);
    }
    if (b < -1 && data > node->right->data)
        return leftr(node);
    if (b < -1 && data < node->right->data) {
        node->right = rightr(node->right);
        return leftr(node);
    }
    return node;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getb(root);

    printf("Deleting %d: Critical Node: %d, Balance Factor: %d\n", data, root->data, balance);

    if (balance > 1 && getb(root->left) >= 0)
    {   printf("\nLL rotation\n");
        return rightr(root);
    }
    if (balance > 1 && getb(root->left) < 0) {
        printf("\nLR rotation\n");
        root->left = leftr(root->left);
        return rightr(root);
    }
    if (balance < -1 && getb(root->right) <= 0)
       { printf("\nRR rotation\n");
        return leftr(root);
       }
    if (balance < -1 && getb(root->right) > 0) 
    {
        printf("\nRL rotation\n");
        root->right = rightr(root->right);
        return leftr(root);
    }
    return root;
}

void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 5);
    root = insert(root, 40);
    root = insert(root, 50);

    printf("Preorder traversal before deletion:\n");
    preorder(root);
    printf("\n");

    root = deleteNode(root, 10);
    printf("Preorder traversal after deleting 10:\n");
    preorder(root);
    printf("\n");

    root = deleteNode(root, 30);
    printf("Preorder traversal after deleting 30:\n");
    preorder(root);
    printf("\n");

    root = deleteNode(root, 50);
    printf("Preorder traversal after deleting 50:\n");
    preorder(root);
    printf("\n");

    return 0;
}
