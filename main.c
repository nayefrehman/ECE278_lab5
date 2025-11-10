//
//  main.c
//  AVLRecursePtr
//
//  Created by Thomas Dean on 2025-10-23.
//


#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// forward declarations
void insert(Node**r, int key);
void preOrder(Node *root);
void levelPrint(Node * root);

int main(int argc, const char * argv[]) {
    Node *tree1 = NULL;
    /* Constructing tree given in the above figure */
    printf("Inserting values in tree 1\n");
    insert(&tree1, 10);
    insert(&tree1, 20);
    insert(&tree1, 30);
    insert(&tree1, 40);
    insert(&tree1, 50);
    insert(&tree1, 25);
    insert(&tree1, 27);
    insert(&tree1, 21);
    insert(&tree1, 22);
    insert(&tree1, 25);
    
    printf("Preorder traversal of the constructed AVL tree is \n");
    preOrder(tree1);
    printf("\n");
    
    // add a function to do a level order pretty print
    
    // Create a second tree which has some values in common
    // with the above tree, and some different values.
    
    
    // call a function that returns a tree that is the union
    // of both trees. Every value should only be in the
    // result tree once even if it occurs twice in one of the
    // source trees.
    
    
    // call a functon that returns a tree that is the intersection
    // of both trees. Every value should only be in the
    // result tree once even if it occurs twice in one of the
    // source trees.

    return 0;
}

int max(int a, int b);
int height(Node *n);
int calcHeight(Node *n);
Node* newNode(int key);
void rightRotate(Node **r);
void leftRotate(Node **r);
int getBalance(Node *n);

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
void insert(Node  **r, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (*r == NULL) {
        *r = newNode(key);
        // height of leaf node is 0, balance is 0
        // don't do anything more.
        return;
    }

    if (key < (*r)->key)
        insert(&((*r)->left), key);
    else // if (key >= (*r)->key) -- allow duplicates
        insert(&((*r)->right), key);
    
    /* 2. Update height of this ancestor node */
    // oldversion was redundant, retraverses entire tree...
    (*r)->height = calcHeight(*r);
    
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became unbalanced */
    int balance = getBalance(*r);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance < -1 && key < (*r)->left->key){
        rightRotate(r);
        return;
    }
    // Right Right Case
    if (balance > 1 && key > (*r)->right->key){
        leftRotate(r);
        return;
    }
    // Left Right Case
    if (balance < -1 && key > (*r)->left->key)
    {
        leftRotate(&((*r)->left));
        rightRotate(r);
        return;
    }
    // Right Left Case
    if (balance > 1 && key < (*r)->right->key)
    {
        rightRotate(&((*r)->right));
        leftRotate(r);
        return;
    }

}
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

int calcHeight(Node * n){
    if (n == NULL){
        return -1;
    }
    return 1+max(height(n->left),height(n->right));
}
int height(Node *n)
{
    if (n == NULL){
        return -1;
    }
    return n->height;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
Node* newNode(int key)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->key    = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 0; // new node is a leaf (height 0)
    return(node);
}

// A utility function to right rotate subtree rooted with *r
//  r->root  r->root
//      |        |
//      a        b
//     / \      / \
//    b   X    Z   a
//   / \          / \
//  Z  Y         Y   X

void rightRotate(Node **r)
{
    Node *a = (*r);
    Node *b = a -> left;
    Node *Y = b -> right;
    
    // Perform rotation
    b->right = a;
    a->left = Y;
    *r = b;
    
    a->height = calcHeight(a);
    b->height = calcHeight(b);
}

// A utility function to right rotate subtree rooted with *r
//  r->root     r->root
//      |           |
//      a           b
//     / \         / \
//    X   b       a   Z
//       / \     / \
//      Y   Z   X   Y

void leftRotate(Node **r)
{
    Node *a = (*r);
    Node *b = a -> right;
    Node *Y = b -> left;
    
    // Perform rotation
    b->left = a;
    a->right = Y;
    *r = b;
    
    a->height = calcHeight(a);
    b->height = calcHeight(b);
}

// Get Balance factor of node N
// this is wrong too.
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->right) - height(N->left);
}


// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(Node *root) {
    if(root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// queue implementation structs and functions
typedef struct QueueNode{
    Node * treeNode; // pointer to tree node
    struct QueueNode * next; // pointer to next queue node
} QueueNode;

typedef struct Queue{
    QueueNode * front; // pointer to front of queue
    QueueNode * rear; // pointer to rear(end) of queue
} Queue; 

// function which enqueues a tree node pointer to the queue
void enqueue(Queue * q, Node * n){
    QueueNode * temp = (QueueNode *) malloc(sizeof(QueueNode)); // creates a new queue node
    temp -> treeNode = n; // sets the tree node pointer
    temp -> next = NULL; // next pointer is null 
    if(q -> rear == NULL){ // if queue is empty
        q -> front = temp; // front and rear both point to new node
        q -> rear = temp; // rear also points to new node
    } else { // if queue is not empty
        q -> rear -> next = temp; // point rear's next to new node
        q -> rear = temp; // update the rear to new node
    }
}

// function which dequeue's a tree node pointer from the queue
Node * dequeue(Queue * q){
    if(q -> front == NULL){ // if the queue is empty
        return NULL;
    } 
    QueueNode * temp = 
}