#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node *node) {
    struct Node *x = node->left;
    struct Node *T2 = x->right;
    x->right = node;
    node->left = T2;
    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct Node *leftRotate(struct Node *node) {
    struct Node *y = node->right;
    struct Node *T2 = y->left;
    y->left = node;
    node->right = T2;
    node->height = max(height(node->left), height(node->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) {
        printf("Inserted node: %d\n", key);
        return newNode(key);
    }

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    printf("Node %d: Balance Factor: %d\n", node->key, balance);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        printf("Unbalanced at %d: Left Left Case: Performing Right Rotation\n", node->key);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        printf("Unbalanced at %d: Right Right Case: Performing Left Rotation\n", node->key);
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        printf("Unbalanced at %d: Left Right Case: Performing Left Rotation on Left Child and Right Rotation\n", node->key);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        printf("Unbalanced at %d: Right Left Case: Performing Right Rotation on Right Child and Left Rotation\n", node->key);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    
    root = insert(root, 30); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 40); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 50); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 25); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 35); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 45); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 42); printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = insert(root, 47); printf("Preorder traversal: "); preOrder(root); printf("\n");

    return 0;
}
