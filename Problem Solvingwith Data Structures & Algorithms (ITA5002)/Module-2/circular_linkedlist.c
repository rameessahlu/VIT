#include <stdio.h>
#include <stdlib.h>


struct node
{
    struct node* next;
    int data;
};

typedef struct node n;

n* rear;
n* front;

void initialize()
{
    rear = front = NULL;
}

void insert(int data){
    n* temp = (n*) malloc(sizeof(n));
    temp->data = data;
    if(isEmpty() == 0){
        temp->next = NULL;
        rear = front = temp;
    }
    else{
        rear->next = temp;
        rear = temp;
        rear->next = front;
    }
}

int isEmpty(){
    if(rear == NULL && front == NULL)
        return 0;
    else
        return 1;
}

void delete(){
    n* temp = front;
    if(front == NULL)
        printf("\nLinked list is underflow!\n");
    else
    {
        if(front == rear)
        {
            front = rear = NULL;
        }
        else
        {
            front = front->next;
            rear->next = front;
            free(temp);
        }
    }
}

void display()
{
    n* temp = front;
    printf("\n");
    while(temp != rear)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d ", temp->data);
    printf("%d ", temp->next->data);
}

int main()
{
    initialize();
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    display();
    delete();
    display();
    insert(6);
    display();
    return 0;
}
