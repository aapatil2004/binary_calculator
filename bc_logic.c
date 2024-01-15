#include <stdio.h>
#include <stdlib.h>
#include "bc_header.h"

void init(number *head)
{
    head->front = NULL;
    head->rear = NULL;
    return;
}

int isempty(number head)
{
    if (head.front == NULL)
        return 1;
    return 0;
}

void insertLeft(number *head, int d)
{
    node *nn = (node *)malloc(sizeof(node));
    if (nn)
    {
        nn->data = d;
        nn->next = NULL;
        nn->prev = NULL;
    }
    else
        return;
    nn->next = head->front;
    if (head->front != NULL)
    {
        head->front->prev = nn;
    }
    head->front = nn;
    if (head->rear == NULL)
    {
        head->rear = nn;
    }
    return;
}

void insertRight(number *head, int d)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->next = NULL;
    nn->prev = NULL;
    nn->data = d;
    if (!isempty(*head))
    {
        node *temp = head->front;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = nn;
        nn->prev = temp;
        head->rear = nn;
    }
    else
    {
        head->front = nn;
        head->rear = nn;
    }
}

void insertDecimalPointL(number *head)
{
    node *nn = (node *)malloc(sizeof(node));
    if (nn)
    {
        nn->data = -1;
        nn->next = NULL;
        nn->prev = NULL;
    }
    else
        return;
    nn->next = head->front;
    if (head->front != NULL)
    {
        head->front->prev = nn;
    }
    head->front = nn;
    if (head->rear == NULL)
    {
        head->rear = nn;
    }
    return;
}

void insertDecimalPointR(number *head)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->next = NULL;
    nn->prev = NULL;
    nn->data = -1;
    if (!isempty(*head))
    {
        node *temp = head->front;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = nn;
        nn->prev = temp;
        head->rear = nn;
    }
    else
    {
        head->front = nn;
        head->rear = nn;
    }
}

void insertAtIndex(number *head, int index, int data)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->data = data;
    nn->next = NULL;
    nn->prev = NULL;
    node *p = head->front;
    while (index > 0)
    {
        p = p->next;
        index--;
    }
    node *y = p->next;
    p->next = nn;
    nn->next = y;
    nn->prev = p;
    y->prev = nn;
}
void insertNegativeL(number *head)
{
    node *nn = (node *)malloc(sizeof(node));
    if (nn)
    {
        nn->data = -2;
        nn->next = NULL;
        nn->prev = NULL;
    }
    else
        return;
    nn->next = head->front;
    if (head->front != NULL)
    {
        nn->prev = nn;
    }
    head->front = nn;
    if (head->rear == NULL)
    {
        head->rear = nn;
    }
    return;
}

void insertNegativeR(number *head)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->next = NULL;
    nn->prev = NULL;
    nn->data = -2;
    if (!isempty(*head))
    {
        node *temp = head->front;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = nn;
        nn->prev = temp;
        head->rear = nn;
    }
    else
    {
        head->front = nn;
        head->rear = nn;
    }
}

number deleteNegativeR(number head)
{
    if (head.rear != NULL)
    {
        node *p = head.rear;
        node *q = p->prev;
        q->next = p->next;
        head.rear = q;
        free(p);
    }
    return head;
}

number deleteR(number head)
{
    if (head.rear != NULL)
    {
        node *p = head.rear;
        node *q = p->prev;
        q->next = p->next;
        head.rear = q;
        free(p);
    }
    return head;
}

number reverse(number head)
{
    node *p1, *p2;
    int temp;
    p1 = head.front;
    p2 = head.rear;

    while (p1 != p2 && p2 != p1->prev)
    {
        temp = p1->data;
        p1->data = p2->data;
        p2->data = temp;
        p1 = p1->next;
        p2 = p2->prev;
    }
    return head;
}

int count(number *head)
{
    int count = 0;
    node *p = head->front;
    if (p == NULL)
        return 0;
    while (p->next != NULL && p->data != -1)
    {

        p = p->next;
        count++;
    }
    if (p->data != -1)
    {
        return 0;
    }
    return count;
}

void displayLR(number head)
{
    node *p;
    p = head.front;
    if (!p)
    {
        return;
    }
    do
    {
        if (p->data == -1)
        {
            printf(".");
        }
        else if (p->data == -2)
        {
            printf("-");
        }
        else
        {
            printf("%d", p->data);
        }
        p = p->next;
    } while (p != NULL);
    printf("\n");
}

void displayRL(number head)
{
    node *p;
    p = head.rear;
    if (!p)
    {
        return;
    }
    do
    {
        if (p->data == -1)
        {
            printf(".");
        }
        else if (p->data == -2)
        {
            printf("-");
        }
        else
        {
            printf("%d", p->data);
        }
        p = p->prev;
    } while (p != NULL);
}

number add(number l1, number l2)
{
    number *l3 = (number *)malloc(sizeof(number));
    init(l3);
    node *r = l1.rear;
    node *s = l2.rear;
    long long count1 = count(&l1);
    long long count2 = count(&l2);
    if (r == NULL && s != NULL)
    {
        return l2;
    }
    else if (r->data == -2 && s->data == -2)
    {
        l1 = deleteNegativeR(l1);
        l2 = deleteNegativeR(l2);
        add(l1, l2);
        insertNegativeR(l3);
        return *l3;
    }
    else if (r->data == -2 && s->data != -2)
    {
        l1 = deleteNegativeR(l1);
        return sub(l2, l1);
    }
    else if (r->data != -2 && s->data == -2)
    {
        l2 = deleteNegativeR(l2);
        return sub(l1, l2);
    }
    else if (r->data != -2 && s->data != -2)
    {
        node *p = l1.front;
        node *q = l2.front;
        int carry = 0;
        while (p && q)
        {
            if (count1 > count2)
            {
                insertRight(l3, p->data);
                p = p->next;
                count1--;
                continue;
            }
            else if (count1 < count2)
            {
                insertRight(l3, q->data);
                q = q->next;
                count2--;
                continue;
            }
            if (p->data == -1 && q->data == -1)
            {
                insertDecimalPointR(l3);
            }
            else
            {
                int sum = p->data + q->data + carry;
                carry = sum / 10;
                insertRight(l3, sum % 10);
            }

            p = p->next;
            q = q->next;
        }

        // Handle remaining digits in l1 or l2
        while (p)
        {
            if (p->data == -1)
            {
                insertDecimalPointR(l3);
            }
            else
            {
                int sum = p->data + carry;
                carry = sum / 10;
                insertRight(l3, sum % 10);
            }
            p = p->next;
        }

        while (q)
        {
            if (q->data == -1)
            {
                insertDecimalPointR(l3);
            }
            else
            {
                int sum = q->data + carry;
                carry = sum / 10;
                insertRight(l3, sum % 10);
            }
            q = q->next;
        }

        // Handle any remaining carry
        if (carry > 0)
        {
            insertRight(l3, carry);
        }

        return *l3;
    }
}

number sub(number l1, number l2)
{
    number *l4 = (number *)malloc(sizeof(number));
    init(l4);
    long long count1 = count(&l1);
    long long count2 = count(&l2);
    node *l5, *l6, *p, *q;
    l5 = l1.front;
    l6 = l2.front;
    p = l1.front;
    q = l2.front;
    node *r = l1.rear;
    node *s = l2.rear;
    if (r->data != -2 && s->data != -2)
    {
        if (count1 > count2)
        {
            while(count1 > count2)
            {
            l5 = l5->next;
            count1--;
            }

        }
        else if (count1 < count2)
        {
            while(count1 < count2)
            {
            l6 = l6->next;
            count2--;
            }
        }
        while (l5->next && l6->next)
        {
            l5 = l5->next;
            l6 = l6->next;
        }
        int borrow = 0;
        count1=count(&l1);
        count2=count(&l2);
        if(l1.rear->data==0)
        {
                deleteR(l1);
        }
        else if(l2.rear->data==0)
        {
                deleteR(l2);
        }
        if (l5->next)
        {
            while (p && q)
            {
                if (count1 > count2)
                {
                    insertRight(l4, p->data);
                    p = p->next;
                    count1--;
                    continue;
                }
                else if (count1 < count2)
                {
                    q->data = 10 - q->data;
                    insertRight(l4, q->data);
                    q = q->next;
                    count2--;
                    q->data = q->data + 1;
                    continue;
                }

                if (p->data == -1 && q->data == -1)
                {
                    insertDecimalPointR(l4);
                    p = p->next;
                    q = q->next;
                }

                else if (p->data >= q->data)
                {
                    insertRight(l4, p->data - q->data);
                    p = p->next;
                    q = q->next;
                }
                else if (p->data < q->data)
                {
                    borrow = p->data - q->data + 10;
                    insertRight(l4, borrow);
                    p = p->next;
                    q = q->next;
                    if (q != NULL && q->data == -1)
                    {
                        insertDecimalPointR(l4);
                        p = p->next;
                        q = q->next;
                    }
                    p->data = p->data - 1;
                }
            }
            while (p)
            {
                if (p->data == -1)
                {
                    p->data = p->data + 10;
                    p = p->next;
                    p->data = p->data - 1;
                }
                insertRight(l4, p->data);
                p = p->next;
            }
            return *l4;
        }

        else if (l6->next)
        {
            while (p && q)
            {
                if (p == NULL || q == NULL)
                {
                    // Handle the case where either p or q is NULL
                    break;
                }
                if (count1 > count2)
                {
                    p->data = 10 - p->data;
                    insertRight(l4, p->data);
                    p = p->next;
                    count1--;
                    p->data = p->data + 1;
                    continue;
                    
                    
                }
                else if (count1 < count2)
                {
                    insertRight(l4, q->data);
                    q = q->next;
                    count2--;
                    continue;
                }
                if (p->data == -1 && q->data == -1)
                {
                    insertDecimalPointR(l4);
                    p = p->next;
                    q = q->next;
                }

                else if (q->data >= p->data)
                {
                    insertRight(l4, q->data - p->data);
                    q = q->next;
                    p = p->next;
                }
                else if (q->data < p->data)
                {
                    borrow = q->data - p->data + 10;
                    insertRight(l4, borrow);
                    p = p->next;
                    q = q->next;
                    if (q->data == -1)
                    {
                        insertDecimalPointR(l4);
                        p = p->next;
                        q = q->next;
                    }
                    q->data = q->data - 1;
                }
            }
            while (q)
            {

                insertRight(l4, q->data);
                q = q->next;
            }
            insertNegativeR(l4);
            return *l4;
        }
        else if (l5->next == NULL && l6->next == NULL)
        {
            if (l5->data > l6->data || (l5->data == l6->data && l5->prev->data > l6->prev->data))
            {
                while (p && q)
                {
                    if (count1 > count2)
                    {
                        insertRight(l4, p->data);
                        p = p->next;
                        count1--;
                        continue;
                    }
                    else if (count1 < count2)
                    {
                        q->data = 10 - q->data;
                        insertRight(l4, q->data);
                        q = q->next;
                        count2--;
                        q->data = q->data + 1;
                        continue;
                    }
                    if (p->data == -1 && q->data == -1)
                    {
                        insertDecimalPointR(l4);
                        p = p->next;
                        q = q->next;
                    }

                    else if (p->data >= q->data)
                    {
                        insertRight(l4, p->data - q->data);
                        p = p->next;
                        q = q->next;
                    }
                    else if (p->data < q->data)
                    {
                        borrow = p->data - q->data + 10;
                        insertRight(l4, borrow);
                        p = p->next;
                        q = q->next;
                        if (q->data == -1)
                        {
                            insertDecimalPointR(l4);
                            p = p->next;
                            q = q->next;
                        }
                        p->data = p->data - 1;
                    }
                }
                return *l4;
            }
            else if (l6->data >= l5->data)
            {
                while (p && q)
                {
                    if (p == NULL || q == NULL)
                    {
                        // Handle the case where either p or q is NULL
                        break;
                    }
                    if (count1 > count2)
                    {
                        p->data = 10 - p->data;
                        insertRight(l4, p->data);
                        p = p->next;
                        count1--;
                        p->data = p->data + 1;
                        continue;
                        
                    }
                    else if (count1 < count2)
                    {
                        insertRight(l4, q->data);
                        q = q->next;
                        count2--;
                        continue;
                    }
                    if (p->data == -1 && q->data == -1)
                    {
                        insertDecimalPointR(l4);
                        p = p->next;
                        q = q->next;
                    }

                    else if (q->data >= p->data)
                    {
                        insertRight(l4, q->data - p->data);
                        q = q->next;
                        p = p->next;
                    }
                    else if (q->data < p->data)
                    {
                        borrow = q->data - p->data + 10;
                        insertRight(l4, borrow);
                        p = p->next;
                        q = q->next;
                        if (q->data == -1 && p->data == -1)
                        {
                            insertDecimalPointR(l4);
                            p = p->next;
                            q = q->next;
                        }
                        q->data = q->data - 1;
                    }
                }
                insertNegativeR(l4);
                return *l4;
            }
        }
    }
    else if (r->data != -2 && s->data == -2)
    {
        l2 = deleteNegativeR(l2);
        return add(l1, l2);
    }
    else if (r->data == -2 && s->data != -2)
    {
        l1 = deleteNegativeR(l1);
        number l3 = add(l1, l2);
        insertNegativeR(&l3);
        return l3;

    }
    else if (r->data == -2 && s->data == -2)
    {
        l1 = deleteNegativeR(l1);
        l2 = deleteNegativeR(l2);
        return sub(l2, l1);
    }
}

number mul(number l1, number l2)
{
    number *result = (number *)malloc(sizeof(number));
    number temp, new_temp;
    init(result);
    init(&new_temp);
    node *n2 = l2.front;
    node *nn = l2.front;
    while (n2)
    {
        int carry = 0;
        number temp = new_temp;
        node *n1 = l1.front;
        while (n1)
        {
            if (n1->data == -1)
            {
                n1 = n1->next;
            }
            else if (n2->data == -1)
            {
                n2 = n2->next;
            }
            else
            {
                int prod = n1->data * n2->data + carry;
                carry = prod / 10;
                insertRight(&temp, prod % 10);
                n1 = n1->next;
            }
        }
        while (carry != 0)
        {
            insertRight(&temp, carry % 10);
            carry /= 10;
        }
        node *p = temp.front;
        *result = add(*result, temp);
        n2 = n2->next;
        nn = nn->next;
        node *n3 = nn;
        init(&new_temp);
        while (n3 != NULL && n3->prev != NULL)
        {
            insertRight(&new_temp, 0);
            n3 = n3->prev;
        }
    }
    int total_count = count(&l1) + count(&l2);
    number x;
    if (total_count > 0)
    {
        x = *result;
        insertAtIndex(&x, total_count - 1, -1);
        *result = x;
    }
    return *result;
}
