#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* createnode(int data) {
    struct node* nn=(struct node*)malloc(sizeof(struct node));
    nn->data=data;
    nn->left=NULL;
    nn->right=NULL;
    return nn;
}

struct node* insert(struct node* node,int data) {
    if(node==NULL) {
        return createnode(data);
    }
    if(data<node->data) {
        node->left=insert(node->left,data);
    }
    else if(data>node->data) {
        node->right=insert(node->right,data);
    }
    return node;
}

void inorder(struct node* node) {
    if(node==NULL) {
        return;
    }
    inorder(node->left);
    printf(" %d",node->data);
    inorder(node->right);
}

void preorder(struct node* node) {
    if(node==NULL) {
        return;
    }
    printf(" %d",node->data);
    preorder(node->left);
    preorder(node->right);
}

int search(struct node* node,int data) {
    if(node==NULL) {
        return 0;
    }
    if(data==node->data) {
        return 1;
    }
    if(data<node->data) {
        return search(node->left,data);
    }
    else{
        return search(node->right,data);
    }
}

int findmin(struct node* node) {
    while(node&&node->left!=NULL) {
        node=node->left;
    }
    return node->data;
}

int findmax(struct node* node) {
    while(node&&node->right!=NULL) {
        node=node->right;
    }
    return node->data;
}

struct node* successor(struct node* node,int data) {
    struct node* succ=NULL;
    while(node!=NULL) {
        if(data<node->data) {
            succ=node;
            node=node->left;
        }
        else if(data>node->data) {
            node=node->right;
        }
        else {
            if(node->right) {
                succ=node->right;
                while(succ->left!=NULL) {
                    succ=succ->left;
                }
            }
            break;
        }
    }
    return succ;
}

struct node* predecessor(struct node* node,int data) {
    struct node* pred=NULL;
    while(node!=NULL) {
        if(data>node->data) {
            pred=node;
            node=node->right;
        }
        else if(data<node->data) {
            node=node->left;
        }
        else {
            if(node->left) {
                pred=node->left;
                while(pred->right!=NULL) {
                    pred=pred->right;
                }
            }
            break;
        }
    }
    return pred;
}

struct node* deleteNode(struct node* root,int data) {
    if(root==NULL) {
        return root;
    }
    if(data<root->data) {
        root->left=deleteNode(root->left,data);
    }
    else if(data>root->data) {
        root->right=deleteNode(root->right,data);
    }
    else {
        if(root->left==NULL&&root->right==NULL) {
            free(root);
            return NULL;
        }
        if(root->left==NULL) {
            struct node* temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL) {
            struct node* temp=root->left;
            free(root);
            return temp;
        }
        int minValue=findmin(root->right);
        root->data=minValue;
        root->right=deleteNode(root->right,minValue);
    }
    return root;
}

int main() {
    struct node* root=NULL;
    int data,s,found;

    while(1) {
        printf("\nEnter the data to be inserted (-1 to stop): ");
        scanf("%d",&data);
        if (data==-1) {
            break;
        }
        else{
            root=insert(root,data);
            printf("\nINORDER TRAVERSAL OF THE CREATED TREE: ");
            inorder(root);
        }
    }

    printf("\nINORDER TRAVERSAL OF THE CREATED TREE: ");
    inorder(root);
    printf("\nPREORDER TRAVERSAL OF THE CREATED TREE: ");
    preorder(root);

    printf("\nMinimum in the tree: %d",findmin(root));
    printf("\nMaximum in the tree: %d",findmax(root));

    printf("\nEnter the data to be searched: ");
    scanf("%d",&s);
    found=search(root,s);
    if(found) {
        printf("%d FOUND\n",s);
    } 
    else{
        printf("%d NOT FOUND\n",s);
    }

    struct node* succ=successor(root,s);
    if(succ!=NULL) {
        printf("Successor of %d is: %d\n",s,succ->data);
    } else {
        printf("No successor found for %d\n",s);
    }

    struct node* pred=predecessor(root,s);
    if(pred!=NULL) {
        printf("Predecessor of %d is: %d\n",s,pred->data);
    } else {
        printf("No predecessor found for %d\n",s);
    }

    printf("\nEnter the data to be deleted: ");
    scanf("%d",&s);
    root = deleteNode(root, s);

    printf("\nINORDER TRAVERSAL AFTER DELETION: ");
    inorder(root);
    printf("\nPREORDER TRAVERSAL AFTER DELETION: ");
    preorder(root);

    return 0;
}
