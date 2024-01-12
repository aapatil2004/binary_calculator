#include <stdio.h>
#include <stdlib.h>
#include "bc_logic.c"
#include "infixtopostfix.c"
#include <ctype.h>
#include "postfix.c"

int main() 
{
    number  l1, l2, l3, l4, l5;
    init(&l1);
    init(&l2);
    char str[100000] = "123.456 + (29.34 - 23.34) - 10 + 10";
    stack s;
    init1(&s,10000);
    char  postfix[10000];
    int j = 0;
    char c;
    int i=0;
    while(str[i]!= '\0'){
            c = str[i];
            if(isdigit(c) || str[i]=='.')
            {
               postfix[j++] = c ;
               if(!isdigit(str[i+1]) && str[i+1]!='.')
                    postfix[j++] = ' ';
            }
            else if( c == '(')
                push(&s,'(');
            else if(c == ')'){
                    while(!isEmpty(s) && peek(s)!= '('){
                          postfix[j++] = pop(&s);
                          postfix[j++] = ' ';
                    }
                    if(peek(s) == '(')
                        pop(&s);
            }
            else {
                    if( c == '+' || c =='-' || c == '*'|| c == '/') {
                        if(isEmpty(s))
                            push(&s, c);
                        else {
                            while(!isEmpty(s) && precedence(peek(s)) >= precedence(c)){
                                  postfix[j++] = pop(&s);
                                  postfix[j++] = ' ';
                            }
                            push(&s, c);
                        }
                    }
            }
        i++;
    }

    while(!isEmpty(s)){
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    printf("Expression after infix to postfix : \n");
    for(i = 0; i < j; i++)
    
    {
          printf("%c", postfix[i]);
    
    
    }
    const char* postfix_expression = {"123.456 29.34 23.34 - + 10 - 10 + "};
    int result = evaluate_postfix(postfix_expression);
    //printf("Result of %s is: %d\n", postfix_expression, result);

    
    

    return 0;
}
