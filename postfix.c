#include <stdio.h>
#include <stdlib.h>
#include "postfix.h"


void push1(LinkedList* list, int value) {
    Node* nn = (Node*)malloc(sizeof(Node));
    nn->data = value;
    nn->next = list->head;
    list->head = nn;
}

int pop1(LinkedList* list) {
    if (list->head == NULL) {
        fprintf(stderr, "Error: Attempting to pop1 from an empty list.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = list->head;
    list->head = temp->next;
    int pop1pedValue = temp->data;
    free(temp);
    return pop1pedValue;
}

int is_empty(LinkedList* list) {
    return (list->head == NULL);
}

int evaluate_postfix(const char* expression) {
    LinkedList l1;
    l1.head = NULL;

    for (int i = 0; expression[i] != '\0'; i++) 
    {
        if (isdigit(expression[i])) 
        {
            push1(&l1, expression[i] - '0');  // Convert character to integer
        } 
        if (expression[i] == '.') 
        {
            push1(&l1, expression[i] - '0');  // Convert character to integer
        } 
        else 
        {
            int operand2 = pop1(&l1);
            int operand1 = pop1(&l1);

            switch (expression[i]) {
                case '+':
                    push1(&l1, operand1 + operand2);
                    break;
                case '-':
                    push1(&l1, operand1 - operand2);
                    break;
                case '*':
                    push1(&l1, operand1 * operand2);
                    break;
                case '/':
                    push1(&l1, operand1 / operand2);
                    break;
                default:
                    fprintf(stderr, "Error: Invalid character in expression.\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    return pop1(&l1);
}



