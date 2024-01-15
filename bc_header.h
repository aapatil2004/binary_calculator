#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node* next, *prev;
    int data;
}node;

typedef struct number {
    int sign;
    node *front, *rear;
} number;

void init(number *head);
int isempty(number head);
void insertLeft(number *head, int d);
void insertRight(number *head, int d);
void insertDecimalPointR(number *head);
void insertDecimalPointL(number *head);
void insertAtIndex(number * head, int index, int data);
void insertNegativeL(number *head);
void insertNegativeR(number *head);
number deleteNegativeR(number head);
number deleteR(number head);
number reverse(number head);
int count(number *head);
void displayLR(number head);
void displayRL(number head);
number add(number l1, number l2);
number sub(number l1, number l2);
number mul(number l1, number l2);
