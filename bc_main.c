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

node *reverse(node *head) {
    node *prev = NULL;
    node *current = head;
    node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        current->prev = next;  // Update the prev pointer in a doubly linked list
        prev = current;
        current = next;
    }

    return prev;  // New head of the reversed list
}


int count (node **head)
{
	int count = 0;
	node * p = *head;
	while(p->data != -1)
	{
		p=p->next;
		count++;
	}
	return count;
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
    if(l5->next)
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
            	if(l2->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	l1=l1->next;
           	        	l2=l2->next;
           	        }
        	l1->data = l1->data -1;
            }
        }
        while(l1)
        {
                insertleft(&l4, l1->data);
        	l1=l1->next;
        }
        return l4;
   }
    	
   else if(l6->next)
   {
    while (l1 && l2)
    {
        	if (l1 == NULL || l2 == NULL)
       		{
            			// Handle the case where either l1 or l2 is NULL
            	break;
        	}
    		if (l1->data == -1 && l2->data ==-1)
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
           	        if(l2->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	l1=l1->next;
           	        	l2=l2->next;
           	        }
           	        l2->data = l2->data -1;
                }
    	}
    	while(l2)
        {
        	
        	insertleft(&l4, l2->data);
        	l2=l2->next;
        }
        insert_negative(&l4);
        return l4;
    }
    else if (l5->next == NULL && l6->next == NULL)
    {
    	if(l5->data > l6->data || (l5->data == l6->data && l5->prev->data > l6->prev->data))
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
            	if(l2->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	l1=l1->next;
           	        	l2=l2->next;
           	        }
        	l1->data = l1->data -1;
            }
        }
        return l4;
        }
        else if ( l6->data >= l5->data )
        {
        while (l1 && l2)
        {
        	if (l1 == NULL || l2 == NULL)
       		{
            			// Handle the case where either l1 or l2 is NULL
            	break;
        	}
    		if (l1->data == -1 && l2->data ==-1)
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
           	        if(l2->data == -1 && l1->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	l1=l1->next;
           	        	l2=l2->next;
           	        }
           	        l2->data = l2->data -1;
        	}
    	}
    	insert_negative(&l4);
    	return l4;
    	} 
    	
    }

}


node *mul(node *l1, node *l2) {
    node *result = NULL;
    node *n2 = l2;
    node *nn = l2;
    node *new_temp = NULL; // Declare new_temp outside the loop

    while (n2) {
        int carry = 0;
        node *temp = new_temp;
        node *n1 = l1;

        while (n1) {
            if (n1->data == -1) {
                n1 = n1->next;
            } else if (n2->data == -1) {
                n2 = n2->next;
            } else {
                int prod = n1->data * n2->data + carry;
                carry = prod / 10;
                insertright(&temp, prod % 10);
                n1 = n1->next;
            }
        }

        while (carry != 0) {
            insertright(&temp, carry % 10);
            carry /= 10;
        }

        while (temp->prev) {
            temp = temp->prev;
        }

        while (result && result->prev) {
            result = result->prev;
        }

        result = add(reverse(result), temp);
        n2 = n2->next;
        nn = nn->next;
        node *n3 = nn;
        new_temp=NULL;
        while (n3 != NULL && n3->prev != NULL) {
            insertright(&new_temp, 0);
            n3 = n3->prev;
        }
    }
    // Now you can use new_temp outside the loop if needed
    int total_count = count(&l1) + count(&l2);
    node *x;
    if(total_count > 0)
    x = reverse(result);
    {
    while(total_count > 1)
    {
    	x=x->next;
    	total_count--;
    }
    node * z = NULL;
    node * y = x->next;
    insert_decimal_point(&z);
    x->next = z;
    z->next = y;
    z->prev = x;
    y->prev = z;
    while(x->prev)
    {
    	x = x->prev;
    } 
    result = reverse(x);
    }
    return result;
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
