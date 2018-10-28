#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

typedef struct node n;

n* rear;
n* front;

void initialize(){
    rear = front = NULL;
}

void enqueue(int data){
    n* temp = (n*) malloc(sizeof(n));
    temp->data = data;
    if(isEmpty() == 0){
        rear = front = temp;
        rear->next = front->next = NULL;
    }
    else{
        temp->next = rear;
        rear = temp;
    }
}

void dequeue()
{
    if(isEmpty() == 1)
    {
        n* temp = rear;
        rear = rear->next;
        free(temp);
    }
}

int isEmpty(){
    if(rear == NULL && front == NULL)
        return 0;
    else
        return 1;
}

void display()
{
    n* temp = rear;
    printf("\n");
    while(temp != front)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d ", temp->data);
}

int main()
{
    initialize();
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    display();
    dequeue();
    display();
    return 0;
}
