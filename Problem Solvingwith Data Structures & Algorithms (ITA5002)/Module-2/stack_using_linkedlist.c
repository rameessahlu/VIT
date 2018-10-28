#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node* next;
    int data;
};
typedef struct node n;

n* top;

void push(int data){
    n* temp = (n*) malloc(sizeof(n));
    temp->data = data;
    if(isEmpty() == 0){
        temp->next = top;
    }
    else{
        temp-> next = NULL;
    }
    top = temp;
}

void pop(){
    if(isEmpty() == 0)
    {
        top = top->next;
    }
}

void initialize(){
    top = NULL;
}

isFull(){

}

void display()
{
    n* temp = top;
    printf("\n");
    while(temp->next != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d ", temp->data);
}

int isEmpty(){
    if(top == NULL)
        return 1;
    else
        return 0;
}

int main()
{
    initialize();
    push(1);
    push(2);
    push(3);
    push(4);
    display();
    pop();
    display();
    return 0;
}
