#define MAX_SIZE 100

typedef struct {
    float items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack);
void push1(Stack *stack, float value);
float pop1(Stack *stack);
float postfix_solver(char *expression[]);
