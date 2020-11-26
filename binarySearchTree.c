#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

struct BinaryTree{
    Node* root;
};

typedef struct BinaryTree BinaryTree;

struct ReturnValue{
    int success;
    Node* value;
};

typedef struct ReturnValue ReturnValue;

BinaryTree* newTree(){
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

Node* newNode(){
    Node *n = (Node*)malloc(sizeof(Node));
    n->right = NULL;
    n->left = NULL;
    return n;
}

void insert(Node* tree, Node* x, BinaryTree* bst){
    if(tree == NULL){
        bst->root = x;
        return;
    }
    if(x->data > tree->data)
        if(tree->right != NULL)
            return insert(tree->right, x, bst);
        else
            tree->right = x;
    else
        if(tree->left != NULL)
            return insert(tree->left, x, bst);
        else
            tree->left = x;
    
}

ReturnValue popMin(Node* tree, Node* parent, BinaryTree* bst){
    ReturnValue returnVal;
    if(tree == NULL){
        printf("\nERROR: Tree is empty");
        returnVal.success = 0;
        return returnVal;
    }
    if(tree->left)
        return popMin(tree->left, tree, bst);

    int left = 1;
    if(parent && parent->data < tree->data)
        // Happens while removing node with 2 children
        left = 0;

    returnVal.success = 1;
    returnVal.value = tree;

    Node* ptr;
    if(tree->right)
        ptr = tree->right;
    else
        ptr = NULL;
    if(parent == NULL)
        bst->root = ptr;
    else
        if(left)
            parent->left = ptr;
        else
            parent->right = ptr;

    return returnVal;
}

ReturnValue popMax(Node* tree, Node* parent, BinaryTree* bst){
    ReturnValue returnVal;
    if(tree == NULL){
        printf("\nERROR: Tree is empty");
        returnVal.success = 0;
        return returnVal;
    }
    if(tree->right)
        return popMax(tree->right, tree, bst);

    returnVal.success = 1;
    returnVal.value = tree;

    int right = 1;
    if(parent && parent->data > tree->data)
        right = 0;

    Node* ptr;
    if(tree->left)
        ptr = tree->left;
    else
        ptr = NULL;
    if(parent == NULL)
        bst->root = ptr;
    else
        if(right)
            parent->right = ptr;
        else
            parent->left = ptr;
    
    return returnVal;
}

void removeNode(Node* tree, int x, Node* parent, BinaryTree* bst){
    // Delete element x from tree
    if(tree == NULL){
        printf("\nERROR: Element not found");
        return;
    }
    if(x < tree->data)
        return removeNode(tree->left, x, tree, bst);
    if(x > tree->data)
        return removeNode(tree->right, x, tree, bst);

    // Assume tree is parent's right child
    int left = 0;
    if(parent != NULL && parent->data > tree->data)
        // tree is parent's left child
        left = 1;

    if(parent != NULL)
        if(left)
            parent->left = NULL;
        else
            parent->right = NULL;
    
    Node* ptr = NULL;
    if(tree->right && tree->left){
        ptr = popMin(tree->right, tree, bst).value;
        ptr->left = tree->left;
        if(tree->right != ptr)
            ptr->right = tree->right;
    }
    else if(tree->right)
        ptr = tree->right;
    else if(tree->left)
        ptr = tree->left;
        
    if(parent == NULL)
        bst->root = ptr;
    else
        if(left)
            parent->left = ptr;
        else
            parent->right = ptr;   
}

void traverse(Node* tree){
    // Inorder DFS -> ascending order
    if(tree == NULL){
        printf("Tree is empty");
        return;
    }
    if(tree->left)
        traverse(tree->left);
    printf("%d ", tree->data);   
    if(tree->right)
        traverse(tree->right);
}

void insertHelper(BinaryTree* tree, int x){
    Node* n = newNode();
    n->data = x;
    insert(tree->root, n, tree);
}

int main(){
    BinaryTree* tree = newTree();
    insertHelper(tree, 3);
    insertHelper(tree, 6);
    insertHelper(tree, 1);
    insertHelper(tree, 8);
    insertHelper(tree, 9);
    insertHelper(tree, 0);
    insertHelper(tree, 5);
    insertHelper(tree, 7);
    traverse(tree->root);
    removeNode(tree->root, 10, NULL, tree);
    printf("\n");
    traverse(tree->root);
    return 0;
}