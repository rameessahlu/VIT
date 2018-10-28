#include <stdio.h>
#include <stdlib.h>

struct node{
int key;
struct node* left;
struct node* right;
};

typedef struct node n;

n* createNode(int data)
{
    n* temp = (n*) malloc(sizeof(n));
    temp->key = data;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(n* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(n* root)
{
    if(root == NULL)
        return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(n* root)
{
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}


int main()
{
    n* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);

    root->left->left = createNode(4);
    root->left->right = createNode(8);
    root->right->left = createNode(11);
    root->right->right = createNode(16);

    n* temp = root;
    preorder(temp);

    printf("\n");

    temp = root;
    inorder(temp);

    return 0;
}
