#include <stdio.h>
#include <stdlib.h>
#include "bc_header.h"

void init(number *head) {
    head->front = NULL;
    head->rear = NULL;
    return;
}

int isempty(number head){
    if(head.front ==NULL)
         return 1;
    return 0;
}

void insertLeft(number *head, int d) {
    node *nn = (node *)malloc(sizeof(node));
    if (nn) {
        nn->data = d;
        nn->next = NULL;
        nn->prev = NULL;
    } else
        return;
    nn->next = head->front;
    if (head->front != NULL) {
        head->front->prev = nn;
    }
    head->front = nn;
    if (head->rear == NULL) {
        head->rear = nn;
    }
    return;
}

void insertRight(number *head, int d) {
    node *nn = (node *)malloc(sizeof(node));
    nn->next = NULL;
    nn->prev = NULL;
    nn->data = d;
    if (!isempty(*head)) {
        node *temp = head->front;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = nn;
        nn->prev = temp;
        head->rear = nn;
    } else {
        head->front = nn;
        head->rear = nn;
    }
}

void insertDecimalPoint(number *head) {
    node *nn = (node *)malloc(sizeof(node));
    if (nn) {
        nn->data = -1;
        nn->next = NULL;
        nn->prev = NULL;
    } else
        return;
    nn->next = head->front;
    if (head->front != NULL) {
        head->front->prev = nn;
    }
    head->front = nn;
    if (head->rear == NULL) {
        head->rear = nn;
    }
    return;
}

void insertNegative(number *head) {
    node *nn = (node *)malloc(sizeof(node));
    if (nn) {
        nn->data = -200;
        nn->next = NULL;
        nn->prev = NULL;
    } else
        return;
    nn->next = head->front;
    if (head->front != NULL) {
        nn->prev = nn;
    }
    head->front = nn;
    if (head->rear == NULL) {
        head->rear = nn;
    }
    return;
}

number reverse(number head){
   node  *p1, *p2;
   int temp;
   p1 = head.front; 
   p2 = head.rear;
   
   while(p1!=p2 && p2 != p1->prev){
        temp = p1->data;
        p1->data = p2->data;
        p2->data = temp;
        p1=p1->next;
        p2=p2->prev;
   }
   return head;
  
}

int count(number * head) {
    int count = 0;
    node *p = head->front;
    while (p->data != -1) {
        p = p->next;
        count++;
    }
    return count;
}

void displayLR(number head) {
    node *p;
    p = head.front;
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

number add(number l1, number l2) {
    number l3;
    init(&l3);
    node * p = l1.front;
    node * q = l2.front;
    int carry = 0;
    while (p && q) {
        if (p->data == -1) {
            insertDecimalPoint(&l3);
        } else {
            int sum = p->data + q->data + carry;
            carry = sum / 10;
            insertLeft(&l3, sum % 10);
        }

        p = p->next;
        q = q->next;
    }

    // Handle remaining digits in l1 or l2
    while (p) {
        if (p->data == -1) {
            insertDecimalPoint(&l3);
        } else {
            int sum = p->data + carry;
            carry = sum / 10;
            insertLeft(&l3, sum % 10);
        }
        p = p->next;
    }

    while (q) {
        if (q->data == -1) {
            insertDecimalPoint(&l3);
        } else {
            int sum = q->data + carry;
            carry = sum / 10;
            insertLeft(&l3, sum % 10);
        }
        q = q->next;
    }

    // Handle any remaining carry
    if (carry > 0) {
        insertLeft(&l3, carry);
    }

    return l3;
}

number sub(number l1, number l2)
{
    number l4;
    init(&l4);
    node *l5, *l6, *p , *q;
    l5=l1.front;
    l6=l2.front;
    p=l1.front;
    q=l2.front;
    while(l5->next && l6->next)
    {
    	l5=l5->next;
    	l6=l6->next;
    }
    int borrow = 0;
    if(l5->next)
    {
    	while (p && q)
    	{
    	    if (p->data == -1 && q->data ==-1)
    	    {
        	insert_decimal_point(&l4);
        	p = p->next;
        	q = q->next;
    	    } 
        		
            else if (p->data >= q->data)
        	{
            	insertleft(&l4, p->data - q->data);
            	p = p->next;
            	q = q->next;
        	}
            else if (p->data < q->data)
            {
            	borrow = p->data - q->data + 10;
            	insertleft(&l4, borrow);
            	p = p->next;
            	q = q->next;
            	if(q->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	p=p->next;
           	        	q=q->next;
           	        }
        	p->data = p->data -1;
            }
        }
        while(p)
        {
                insertleft(&l4, p->data);
        	p=p->next;
        }
        return l4;
   }
    	
   else if(l6->next)
   {
    while (p && q)
    {
        	if (p == NULL || q == NULL)
       		{
            			// Handle the case where either p or q is NULL
            	break;
        	}
    		if (p->data == -1 && q->data ==-1)
    		{
        		insert_decimal_point(&l4);
        		p = p->next;
        		q = q->next;
    		} 
    				
    		else if (q->data >= p->data)
        	{
            		insertleft(&l4, q->data - p->data);
           		q = q->next;
        		p = p->next;
        	}
        	else if (q->data < p->data)
        	{
           		borrow = q->data - p->data + 10;
            		insertleft(&l4, borrow);
            		p = p->next;
           	        q = q->next;
           	        if(q->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	p=p->next;
           	        	q=q->next;
           	        }
           	        q->data = q->data -1;
                }
    	}
    	while(q)
        {
        	
        	insertleft(&l4, q->data);
        	q=q->next;
        }
        insert_negative(&l4);
        return l4;
    }
    else if (l5->next == NULL && l6->next == NULL)
    {
    	if(l5->data > l6->data || (l5->data == l6->data && l5->prev->data > l6->prev->data))
    	{
	while (p && q)
    	{
    	    if (p->data == -1 && q->data ==-1)
    	    {
        	insert_decimal_point(&l4);
        	p = p->next;
        	q = q->next;
    	    } 
        		
            else if (p->data >= q->data)
        	{
            	insertleft(&l4, p->data - q->data);
            	p = p->next;
            	q = q->next;
        	}
            else if (p->data < q->data)
            {
            	borrow = p->data - q->data + 10;
            	insertleft(&l4, borrow);
            	p = p->next;
            	q = q->next;
            	if(q->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	p=p->next;
           	        	q=q->next;
           	        }
        	p->data = p->data -1;
            }
        }
        return l4;
        }
        else if ( l6->data >= l5->data )
        {
        while (p && q)
        {
        	if (p == NULL || q == NULL)
       		{
            			// Handle the case where either p or q is NULL
            	break;
        	}
    		if (p->data == -1 && q->data ==-1)
    		{
        		insert_decimal_point(&l4);
        		p = p->next;
        		q = q->next;
    		} 
    				
    		else if (q->data >= p->data)
        	{
            		insertleft(&l4, q->data - p->data);
           		q = q->next;
        		p = p->next;
        	}
        	else if (q->data < p->data)
        	{
           		borrow = q->data - p->data + 10;
            		insertleft(&l4, borrow);
            		p = p->next;
           	        q = q->next;
           	        if(q->data == -1 && p->data == -1)
           	        {
           	        	insert_decimal_point(&l4);
           	        	p=p->next;
           	        	q=q->next;
           	        }
           	        q->data = q->data -1;
        	}
    	}
    	insert_negative(&l4);
    	return l4;
    	} 
    	
    }

}


number mul(number l1, number l2) {
    number result, temp, new_temp;
    init(&result);
    init(&temp);
    node *n2 = l2.front;
    node *nn = l2.front;
     // Declare new_temp outside the loop

    while (n2) {
        node * p = temp.rear;
        node * q = new_temp.rear;
        int carry = 0;
        p = q;
        node *n1 = l1.front;

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

        p=temp.front;


        result = add(reverse(result), temp);
        n2 = n2->next;
        nn = nn->next;
        node *n3 = nn;
        init(&new_temp);
        while (n3 != NULL && n3->prev != NULL) {
            insertright(&new_temp, 0);
            n3 = n3->prev;
        }
    }
    // Now you can use new_temp outside the loop if needed
    int total_count = count(&l1) + count(&l2);
    number x;
    if(total_count > 0)
    x = reverse(result);
    node * p = x.front;
    {
    while(total_count > 1)
    {
    	p=p->next;
    	total_count--;
    }
    number z;
    init(&z);
    node * q = z.front;
    node * y = p->next;
    insert_decimal_point(&z);
    p->next = q;
    q->next = y;
    q->prev = p;
    y->prev = q;
    while(p->prev)
    {
    	p = p->prev;
    } 
    result = reverse(x);
    }
    return result;
}
