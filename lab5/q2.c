#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

/* Create new node */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert into BST */
Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

/* Parallel BST sum using tasks */
int sum_bst(Node* root) {
    if (root == NULL)
        return 0;

    int left_sum = 0, right_sum = 0;

    #pragma omp task shared(left_sum)
    left_sum = sum_bst(root->left);

    #pragma omp task shared(right_sum)
    right_sum = sum_bst(root->right);

    #pragma omp taskwait

    return root->value + left_sum + right_sum;
}

int main() {
    Node* root = NULL;

    /* Insert 10 values */
    int values[10] = {5, 3, 8, 1, 4, 7, 9, 2, 6, 10};
    for (int i = 0; i < 10; i++)
        root = insert(root, values[i]);

    int total = 0;

    #pragma omp parallel
    {
        #pragma omp single
        total = sum_bst(root);
    }

    printf("BST Sum: %d\n", total);

    return 0;
}