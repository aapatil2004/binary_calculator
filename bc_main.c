#include <stdio.h>
#include <stdlib.h>
//#include "bc_logic.c"
#include "infixtopostfix.c"
#include <ctype.h>
#include "postfix.c"

int main() 
{
    char str[10000] = "129438.4 - (48656.78 * 443.67) + 845573.78923 + 8943993.73059847";
    stack s;
    init1(&s,10000);
    char * postfix = (char*)malloc(sizeof(char)*10000);
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
    printf("\n");
     char * postfix_expression = postfix;
     number result = evaluate_postfix(postfix_expression);
     printf("\n");
     displayRL(result);
    return 0;
}
