#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_list(int n) {
    Node *head = NULL, *temp;

    for (int i = n; i > 0; i--) {
        temp = (Node*)malloc(sizeof(Node));
        temp->data = i;
        temp->next = head;
        head = temp;
    }
    return head;
}

int main() {

    Node* head = create_list(10);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            Node* temp = head;

            while (temp != NULL) {

                #pragma omp task firstprivate(temp)
                {
                    printf("Thread %d processing node with value %d\n",
                           omp_get_thread_num(), temp->data);
                }

                temp = temp->next;
            }
        }
    }

    return 0;
}