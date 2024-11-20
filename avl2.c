#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node* node) {
    if (node==NULL)
    {
        return 0;
    }
    return node->height;
}

struct Node* createNode(int data)
{
    struct Node* node=(struct Node*)malloc(sizeof(struct Node));
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

int max(int a,int b) {
    return (a>b)?a:b;
}

struct Node* rightr(struct Node *y)
{
    struct Node *x=y->left;
    y->left=x->right;
    x->right=y;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    return x;
}

struct Node* leftr(struct Node *x) 
{
    struct Node *y=x->right;
    x->right=y->left;
    y->left=x;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}

int getb(struct Node* node) 
{
    if(node==NULL)
    {
            return 0;
    }
    return height(node->left)-height(node->right);
}

struct Node* insert(struct Node* node,int data) 
{
    if(node==NULL)
    {
            return createNode(data);
    }
    if(data<node->data)
    {
        node->left=insert(node->left,data);
    }
    else if(data>node->data)
    {
        node->right=insert(node->right,data);
    }
    else
    {
        return node;
    }
    node->height=1+max(height(node->left),height(node->right));
    int b=getb(node);
    printf("Inserting %d: , Balance Factor: %d\n",data,b);
     if(b>1||b<-1)
     {
    printf(" Critical Node Identified: %d, Balance Factor: %d\n",node->data,b);
     }
    if (b>1&&data<node->left->data)
    {
        printf("LL rotation on node %d\n",node->data);
        return rightr(node);
    }
    if (b>1&&data>node->left->data) {
        printf("LR rotation on node %d\n",node->data);
        node->left=leftr(node->left);
        return rightr(node);
    }
    if (b<-1&&data>node->right->data)
    {
        printf("RR rotation on node %d\n",node->data);
        return leftr(node);
    }
    if (b<-1&&data<node->right->data) {
        printf("RL rotation on node %d\n",node->data);
        node->right=rightr(node->right);
        return leftr(node);
    }
    return node;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current=node;
    while (current->left!=NULL)
        current=current->left;
    return current;
}

struct Node* deleteNode(struct Node* root,int data) {
    struct Node* criticalA=NULL;
    struct Node* criticalB=NULL;
    struct Node* criticalC=NULL;

    if (root==NULL)
        return root;

    if (data<root->data)
        root->left=deleteNode(root->left,data);
    else if (data>root->data)
        root->right=deleteNode(root->right,data);
    else {
        if ((root->left==NULL)||(root->right==NULL)) {
            struct Node* temp=root->left?root->left:root->right;
            if (temp==NULL) {
                temp=root;
                root=NULL;
            } else
                *root=*temp;
            free(temp);
        } else {
            struct Node* temp=minValueNode(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
    }

    if (root==NULL)
        return root;

    root->height=1+max(height(root->left),height(root->right));
    int balance=getb(root);

    criticalA=root;
    if(balance>1&&getb(root->left)>=0) {
        criticalB=root->left;
        printf("LL rotation on node %d\n",root->data);
        root = rightr(root);
    } else if(balance>1&&getb(root->left)<0) {
        criticalC=root->left->right;
        criticalB=root->left;
        printf("LR rotation on node %d\n",root->data);
        root->left=leftr(root->left);
        root=rightr(root);
    } else if(balance<-1&&getb(root->right)<=0) {
        criticalB=root->right;
        printf("RR rotation on node %d\n",root->data);
        root=leftr(root);
    } else if(balance<-1&& getb(root->right)>0) {
        criticalC=root->right->left;
        criticalB=root->right;
        printf("RL rotation on node %d\n",root->data);
        root->right=rightr(root->right);
        root=leftr(root);
    }

    if (criticalA) printf("Node A: %d (Critical node)\n", criticalA->data);
    if (criticalB) printf("Node B: %d (Critical node)\n", criticalB->data);
    if (criticalC) printf("Node C: %d (Critical node)\n", criticalC->data);

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
    struct Node *root=NULL;

    root=insert(root,50);
    root=insert(root,25);
    root=insert(root,75);
    root=insert(root,15);
    root=insert(root,40);
    root=insert(root,60);
    root=insert(root,80);
    root=insert(root,35);
    root=insert(root,55);
    root=insert(root,65);
    root=insert(root,90);
    root=insert(root,62);
      root = insert(root, 5);   // This will cause imbalance
    root = insert(root, 10);  // This will also contribute to imbalance
    root = insert(root, 20);

    printf("Preorder traversal before deletion:\n");
    preorder(root);
    printf("\n");

    root = deleteNode(root, 15);
    printf("Preorder traversal after deleting 15:\n");
    preorder(root);
    printf("\n");

    return 0;
}
