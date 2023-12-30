#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next, *prev;
} node;

void init(node **head) {
    *head = NULL;
    return;
}

void insertleft(node **head, int d) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode) {
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    } else
        return;
    newnode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newnode;
    }
    *head = newnode;
    return;
}

void insertright(node **head, int d) {
    node *newnode, *temp;
    newnode = (node *)malloc(sizeof(node));
    if (newnode) {
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    } else
        return;
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newnode;
    newnode->prev = temp;
    return;
}

void insert_decimal_point(node **head) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode) {
        newnode->data = -1;
        newnode->next = NULL;
        newnode->prev = NULL;
    } else
        return;
    newnode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newnode;
    }
    *head = newnode;
    return;
}

void insert_negative(node **head) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode) {
        newnode->data = -200;
        newnode->next = NULL;
        newnode->prev = NULL;
    } else
        return;
    newnode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newnode;
    }
    *head = newnode;
    return;
}

void displayLR(node * head) {
    node *p;
    p = head;
    if (!p) {
        return;
    }
    do {
        if (p->data == -1) {
            printf(".");
        } else if (p->data == -200) {
            printf("-");
        } else {
            printf("%d", p->data);
        }
        p = p->next;
    } while (p != NULL);
}

void displayRL(node * head) {
    node *p;
    p = head;
    while(p->next)
    {
    	p=p->next;
    }
    if (!p) {
        return;
    }
    do {
        if (p->data == -1) {
            printf(".");
        } else if (p->data == -200) {
            printf("-");
        } else {
            printf("%d", p->data);
        }
        p = p->prev;
    } while (p != NULL);
}


node *add(node *l1, node *l2) {
    node *l3 = NULL;
    int carry = 0;
    while (l1 && l2) {
        if (l1->data == -1) {
            insert_decimal_point(&l3);
        } else {
            int sum = l1->data + l2->data + carry;
            carry = sum / 10;
            insertleft(&l3, sum % 10);
        }

        l1 = l1->next;
        l2 = l2->next;
    }

    // Handle remaining digits in l1 or l2
    while (l1) {
        if (l1->data == -1) {
            insert_decimal_point(&l3);
        } else {
            int sum = l1->data + carry;
            carry = sum / 10;
            insertleft(&l3, sum % 10);
        }
        l1 = l1->next;
    }

    while (l2) {
        if (l2->data == -1) {
            insert_decimal_point(&l3);
        } else {
            int sum = l2->data + carry;
            carry = sum / 10;
            insertleft(&l3, sum % 10);
        }
        l2 = l2->next;
    }

    // Handle any remaining carry
    if (carry > 0) {
        insertleft(&l3, carry);
    }

    return l3;
}

node *sub(node *l1, node *l2)
{
    node *l4 = NULL;
    node *l5, *l6;
    l5=l1;
    l6=l2;
    while(l5->next && l6->next)
    {
    	l5=l5->next;
    	l6=l6->next;
    }
    int borrow = 0;
    if(l5->next || l5->data >= l6->data)
    {
    	while (l1 && l2)
    	{
    	    if (l1->data == -1 && l2->data ==-1)
    	    {
        	insert_decimal_point(&l4);
        	l1 = l1->next;
        	l2 = l2->next;
    	    } 
        		
            else if (l1->data >= l2->data)
        	{
            	insertleft(&l4, l1->data - l2->data);
            	l1 = l1->next;
            	l2 = l2->next;
        	}
            else if (l1->data < l2->data)
            {
            	borrow = l1->data - l2->data + 10;
            	insertleft(&l4, borrow);
            	l1 = l1->next;
            	l2 = l2->next;
    	    	if (l1->data ==-1 )
    	    	{
    	    		insert_decimal_point(&l4);
        		l1 = l1->next;
        		l2 = l2->next;
        		l1->data = l1->data -1;
            	}
            	else if (l1 != NULL) 
            	{
        		l1->data = l1->data - 1;
    	    	}
            }
        }
        while(l1)
        {
        	if(l5->data < l6->data && l1->next==NULL)
        	{
        		insertleft(&l4, l1->data);
        	}
        	else
        	{
        		insertleft(&l4, l1->data);
        	}
        	l1=l1->next;
        }
        return l4;
   }
    	
   else if(l6->next || l5->data < l6->data || (l5->prev->data < l6->prev->data && l5->data==l6->data))
   {
    while (l1 && l2)
    {
        	if (l1 == NULL || l2 == NULL)
       		{
            			// Handle the case where either l1 or l2 is NULL
            	break;
        	}
    		if (l1->data == -1 || l2->data ==-1)
    		{
        		insert_decimal_point(&l4);
        		l1 = l1->next;
        		l2 = l2->next;
    		} 
    				
    		else if (l2->data >= l1->data)
        	{
            		insertleft(&l4, l2->data - l1->data);
           		l2 = l2->next;
        		l1 = l1->next;
        	}
        	else if (l2->data < l1->data)
        	{
           		borrow = l2->data - l1->data + 10;
            		insertleft(&l4, borrow);
            		l1 = l1->next;
           	        l2 = l2->next;
    	  		if (l2->data ==-1 )
    	    		{
    	    			insert_decimal_point(&l4);
        			l1 = l1->next;
        			l2 = l2->next;
        			l2->data = l2->data -1;
            		}
            		else if (l2 != NULL) 
            		{
        			l2->data = l2->data - 1;
    	    		}
        	}
    	}
    	while(l2)
        {
        	if(l5->data > l6->data && l2->next==NULL)
        	{
        		insertleft(&l4, l2->data);
        	}
        	else
        	{
        		insertleft(&l4, l2->data);
        	}
        	l2=l2->next;
        }
        insert_negative(&l4);
    	
    			
    return l4;
    }
    
    	
}



node *mul(node *l1, node *l2) {
    node *l8 = NULL;
    node *l9 = NULL;

    int carry = 0;
    while (l2) {
        node *temp = l1;

        while (temp) 
        {
            if (temp->data == -1) 
            {
                temp=temp->next;
                continue;
            }
            else if(l2->data == -1)
            {
            	l2=l2->next;
            	continue;
            } 
            else 
            {
                int prod = (temp->data * l2->data) + carry;
                carry = prod / 10;

                if (l2->next) 
                {
                    	insertright(&l8, prod % 10);
                    	
                	
                } 
                else 
                {
                    	insertright(&l9, prod % 10);
                    	
                }
            temp = temp->next;
            }
        }
        if(l2->next)
        {
        	insertright(&l9, 0);
        }
        l2 = l2->next;
    }
    while(l8->prev)
    {
    	l8=l8->prev;
    }
    while(l9->prev)
    {
    	l9=l9->prev;
    }
    if (carry > 0) {
        insertright(&l9, carry);
    }

    return add(l8, l9);
}


int main() {
    node *l1, *l2, *l3, *l4, *l7;
    init(&l1);
    int d1, d2, num;
    printf("Enter the number of digits before decimal for l1: ");
    scanf("%d", &d1);
    for (int i = 1; i <= d1; i++) {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertleft(&l1, num);
    }
    insert_decimal_point(&l1);
    printf("Enter the number of digits after decimal for l1: ");
    scanf("%d", &d2);
    for (int i = 1; i <= d2; i++) {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertleft(&l1, num);
    }

    init(&l2);
    printf("Enter the number of digits before decimal for l2: ");
    scanf("%d", &d1);
    for (int i = 1; i <= d1; i++) {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertleft(&l2, num);
    }
    insert_decimal_point(&l2);
    printf("Enter the number of digits after decimal for l2: ");
    scanf("%d", &d2);
    for (int i = 1; i <= d2; i++) {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertleft(&l2, num);
    }

    printf("\nDisplaying l1: ");
    displayRL(l1);
    printf("\nDisplaying l2: ");
    displayRL(l2);

    init(&l7);
    l7 = mul(l1, l2);
    printf("\n\nMultiplication Result (l5): ");
    displayLR(l7);
    
    init(&l3);
    l3 = add(l1, l2);
    printf("\n\nAddition Result (l3): ");
    displayLR(l3);

    init(&l4);
    l4 = sub(l1, l2);
    printf("\n\nSubtraction Result (l4): ");
    displayLR(l4);
    
    
    
    

    return 0;
}
