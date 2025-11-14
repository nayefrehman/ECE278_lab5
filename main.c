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
    
    printf("\n");
    // add a function to do a level order pretty print
    printf("Level order print of tree 1: \n");
    levelPrint(tree1);
    
    // Create a second tree which has some values in common
    // with the above tree, and some different values.
    Node *tree2 = NULL;
    printf("Inserting values in tree 2\n");
    insert(&tree2, 5);
    insert(&tree2, 10);
    insert(&tree2, 15);
    insert(&tree2, 20);
    insert(&tree2, 23);
    insert(&tree2, 30);
    insert(&tree2, 33);
    insert(&tree2, 40);
    insert(&tree2, 45);
    insert(&tree2, 50);

    printf("PreOrder traversal of the constructed AVL tree is \n");
    preOrder(tree2);

    
    
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

// exercise 1 redo for me to better understand the tree concept 
// exercise 1

// queue implementation structs and functions
typedef struct QueueNode{
    Node * node; // pointer to tree node
    struct QueueNode * next; // pointer to next queue node
} QueueNode;

typedef struct Queue{
    QueueNode * front; // pointer to front of queue
    QueueNode * rear; // pointer to rear(end) of queue
} Queue; 

// function which enqueues a tree node pointer to the queue
void enqueue(Queue * q, Node * n){
    QueueNode * temp = (QueueNode *) malloc(sizeof(QueueNode)); // creates a new queue node
    temp -> node = n; // sets the tree node pointer
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
    QueueNode * temp = q -> front; // stores the front node to temp
    Node *n = temp -> node; // gets the tree node pointer
    q -> front = q -> front -> next; // updates the front pointer
    if (q -> front == NULL){
        q -> rear = NULL; // if queue is empty, rear pointer is also NULL
    }
    free(temp); // free the allocated memory
    return n; // return the tree node pointer
}

int isQueueEmpty(Queue *q){ // a function that checks if queue is empty by passing in a queue pointer
    return (q -> front == NULL); // returns true if front pointer is NULL
}

// function to print the tree in level order
// function to print the tree in level order with proper spacing
// function to print the tree in level order with proper spacing
void levelPrint(Node * root){
    if (root == NULL){
        printf("The tree is empty. \n");
        return;
    }

    Queue q = {NULL, NULL}; // initializes an empty queue
    enqueue(&q, root); // enqueue the root node
    int level = 0; // initializes the level counter (depth)
    int maxHeight = root -> height; // gets the max height of the tree from the root node

    while(!isQueueEmpty(&q)){
        int nodeCounter = 0; // counter for the number of nodes at the current level
        QueueNode * temp = q.front; // temporary pointer to traverse the queue

        // count the number of nodes at the current level
        while(temp){
            nodeCounter++; // increment the node counter by 1
            temp = temp -> next; // move to the next queue node
        }

        // Calculate height of nodes at this level (height decreases as depth increases)
        int currentHeight = maxHeight - level;
        
        // Calculate spacing units: before = (2^height - 1), after = (2^height)
        int unitsBefore = (1 << currentHeight) - 1;  // 2^height - 1
        int unitsAfter = (1 << currentHeight);       // 2^height
        
        // Each unit is 2 spaces (since values are 2 chars wide)
        int spacesBefore = unitsBefore * 2;
        int spacesAfter = unitsAfter * 2;

        // Print depth and height columns (fixed, not part of tree spacing)
        printf("%d %d ", level, currentHeight);

        // process all nodes @ current level
        for(int i = 0; i < nodeCounter; i++){
            Node* current = dequeue(&q); // dequeue a tree node pointer
            
            // Print spaces before the value (alignment spacing)
            for(int s = 0; s < spacesBefore; s++){
                printf(" ");
            }
            
            if(current) {
                // Print only the key value (2 chars wide)
                printf("%2d", current->key);
                
                // enqueue children (both null and non-null to maintain structure)
                enqueue(&q, current->left);
                enqueue(&q, current->right);
            }
            else{
                // Print XX for null nodes (also 2 chars wide)
                printf("XX");
                
                // enqueue NULL for both children to maintain tree structure
                enqueue(&q, NULL);
                enqueue(&q, NULL);
            }
            
            // Print spaces after the value (separation spacing)
            for(int s = 0; s < spacesAfter; s++){
                printf(" ");
            }
        }
        printf("\n"); // new line after printing all nodes at current level
        level++; // moves on to the next level

        // Check if all remaining nodes in queue are NULL
        int allNull = 1;
        temp = q.front; // reset temp to the front of the queue
        while(temp){
            if (temp -> node != NULL){
                allNull = 0; // if any node is not NULL, set allNull to 0
                break;
            }
            temp = temp -> next; // move to the next queue node
        }
        
        // Stop if we've printed all levels or all remaining are NULL
        if(allNull || level > maxHeight) {
            break; // exit the loop
        }
    }
}


