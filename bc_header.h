#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next, *prev;
} node;

typedef struct number {
    node *front, *rear;
} number;

void init(number *head);
int isempty(number head);
void insertLeft(number *head, int d);
void insertRight(number *head, int d);
void insertDecimalPoint(number *head);
void insertAtIndex(number * head, int index, int data);
void insertNegative(number *head);
number reverse(number head);
int count(number *head);
void displayLR(number head);
void displayRL(number head);
number add(number l1, number l2);
number sub(number l1, number l2);
number mul(number l1, number l2);
