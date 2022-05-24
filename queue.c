#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> // for INT_MIN

#define QUEUE_EMPTY INT_MIN
#define MAX_SIZE 100

// For Queue
typedef struct node {
    int value;
    struct node* link;
} node;

typedef struct {
    node* first;
    node* rear;
} queue;

// For Queue
void init_queue(queue* q) {
    q->first = NULL;
    q->rear = NULL;
}

int Push(queue* q, int value) {
    node* newnode = malloc(sizeof(node));

    if (newnode == NULL)
        return -1;

    newnode->value = value;
    newnode->link = NULL;

    if (q->rear != NULL)
        q->rear->link = newnode;
    q->rear = newnode;

    if (q->first == NULL)
        q->first = newnode;

    return 1;
}

int Pop(queue* q) {
    if (q->first == NULL)
        return QUEUE_EMPTY;

    node* tmp = q->first;
    int result = tmp->value;
    q->first = q->first->link;

    if (q->first == NULL)
        q->rear = NULL;

    return result;
}

void Print(queue* q) {
    node* tmp;

    for (tmp = q->first; tmp->link != NULL; tmp = tmp->link)
        printf("%d ", tmp->value);
    printf("%d\n", tmp->value);
}

bool is_empty(queue* q) {
    if (q->first == NULL)
        return true;
    else
        return false;
}

int Size(queue* q) {
    node* tmp;
    int size = 0;

    for (tmp = q->first; tmp->link; tmp = tmp->link)
        size++;
    return ++size;
}

int main() {
    queue qu;
    init_queue(&qu);
    
    Push(&qu, 1);
    Push(&qu, 5);
    Push(&qu, 9);
    
    Print(&qu);
    
    int index = Pop(&qu);
    printf("%d popped\n", index);
    
    Print(&qu);
    return 0;
}
