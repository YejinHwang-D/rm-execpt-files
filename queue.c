#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define QUEUE_EMPTY "Empty"
#define MAX_SIZE 100

// For Queue
typedef struct node {
    char* value;
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

int Push(queue* q, char* value) {
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

char* Pop(queue* q) {
    if (q->first == NULL)
        return QUEUE_EMPTY;

    node* tmp = q->first;
    char* result = tmp->value;
    q->first = q->first->link;

    if (q->first == NULL)
        q->rear = NULL;

    return result;
}

void Print(queue* q) {
    node* tmp;

    for (tmp = q->first; tmp->link != NULL; tmp = tmp->link)
        printf("%s ", tmp->value);
    printf("%s\n", tmp->value);
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
    
    char user_file[50];
    
    while (1) {
        fprintf(stdout, "\n$ 삭제에서 제외할 파일을 입력하세요. : ");
        if (fscanf(stdin, "%s", user_file) == 1) {
            printf("** %s\n", user_file);
            
            if (strcmp(user_file, "!no") == 0) break;
            
            char* temp = (char*)malloc(sizeof(char) * (strlen(user_file) + 1));
            
            strcpy(temp, user_file);
            Push(&qu, temp);
        }
    }
    
    Print(&qu);
    
    char* index = Pop(&qu);
    printf("%s popped\n", index);
    
    index = Pop(&qu);
    printf("%s popped\n", index);
    
    Print(&qu);
    
    return 0;
}
