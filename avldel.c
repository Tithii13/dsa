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

struct Node *newNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));

    printf("Right rotation performed on node %d\n", y->key);

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));

    printf("Left rotation performed on node %d\n", x->key);

    return y;
}

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) {
        printf("Inserted node: %d\n", key);
        return (newNode(key));
    }

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    printf("Node %d - Balance Factor: %d\n", node->key, balance);

    if (balance > 1 && key < node->left->key) {
        printf("Left Left case at node %d\n", node->key);
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        printf("Right Right case at node %d\n", node->key);
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        printf("Left Right case at node %d\n", node->key);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        printf("Right Left case at node %d\n", node->key);
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

struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            struct Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    printf("Node %d has balance factor %d\n", root->key, balance);

    if (balance > 1 && getBalance(root->left) >= 0) {
        printf("Critical node: %d\n", root->key);
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        printf("Critical node: %d\n", root->key);
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        printf("Critical node: %d\n", root->key);
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        printf("Critical node: %d\n", root->key);
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {
    struct Node *root = NULL;

    root = insert(root, 50);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 25);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 75);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 15);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 40);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 60);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 80);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 35);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 55);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 65);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 90);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    root = insert(root, 62);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    printf("Deleting node 15\n");
    root = deleteNode(root, 15);
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    return 0;
}
