typedef struct stack{
    char *a;
    int size;
    int top;
}stack;

int precedence(char c);
void init1(stack *s, int len);
void push(stack *s, char d);
int isFull(stack s) ;
int isEmpty(stack s);
char pop(stack *s);
char peek(stack s);
