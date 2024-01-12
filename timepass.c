#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next, *prev;
} node;

typedef struct number
{
    node *front, *rear;
} number;

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

void insertDecimalPoint(number *head)
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

void insertAtIndex(number * head, int index, int data)
{
    node * nn = (node*)malloc(sizeof(node));
    nn->data = data;
    nn->next=NULL;
    nn->prev = NULL;
    node * p = head->front;
    while(index > 1)
    {
    	p=p->next;
    	index--;
    }
    node * y = p->next;
    p->next = nn;
    nn->next = y;
    nn->prev = p;
    y->prev = nn;

}

void insertNegative(number *head)
{
    node *nn = (node *)malloc(sizeof(node));
    if (nn)
    {
        nn->data = -200;
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
    while (p->data != -1)
    {
        p = p->next;
        count++;
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
        else if (p->data == -200)
        {
            printf("-");
        }
        else
        {
            printf("%d", p->data);
        }
        p = p->next;
    } while (p != NULL);
}

void displayRL(number head) {
    node *p;
    p = head.rear;
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

number add(number l1, number l2)
{
    number l3;
    init(&l3);
    node *p = l1.front;
    node *q = l2.front;
    int carry = 0;
    while (p && q)
    {
        if (p->data == -1)
        {
            insertDecimalPoint(&l3);
        }
        else
        {
            int sum = p->data + q->data + carry;
            carry = sum / 10;
            insertLeft(&l3, sum % 10);
        }

        p = p->next;
        q = q->next;
    }

    //Handle remaining digits in l1 or l2
    while (p)
    {
        if (p->data == -1)
        {
            insertDecimalPoint(&l3);
        }
        else
        {
            int sum = p->data + carry;
            carry = sum / 10;
            insertLeft(&l3, sum % 10);
        }
        p = p->next;
    }

    while (q)
    {
        if (q->data == -1)
        {
            insertDecimalPoint(&l3);
        }
        else
        {
            int sum = q->data + carry;
            carry = sum / 10;
            insertLeft(&l3, sum % 10);
        }
        q = q->next;
    }

    // Handle any remaining carry
    if (carry > 0)
    {
        insertLeft(&l3, carry);
    }

    return l3;
}

number sub(number l1, number l2)
{
    number l4;
    init(&l4);
    node *l5, *l6, *p, *q;
    l5 = l1.front;
    l6 = l2.front;
    p = l1.front;
    q = l2.front;
    while (l5->next && l6->next)
    {
        l5 = l5->next;
        l6 = l6->next;
    }
    int borrow = 0;
    if (l5->next)
    {
        while (p && q)
        {
            if (p->data == -1 && q->data == -1)
            {
                insertDecimalPoint(&l4);
                p = p->next;
                q = q->next;
            }

            else if (p->data >= q->data)
            {
                insertLeft(&l4, p->data - q->data);
                p = p->next;
                q = q->next;
            }
            else if (p->data < q->data)
            {
                borrow = p->data - q->data + 10;
                insertLeft(&l4, borrow);
                p = p->next;
                q = q->next;
                if (q->data == -1)
                {
                    insertDecimalPoint(&l4);
                    p = p->next;
                    q = q->next;
                }
                p->data = p->data - 1;
            }
        }
        while (p)
        {
            insertLeft(&l4, p->data);
            p = p->next;
        }
        return l4;
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
            if (p->data == -1 && q->data == -1)
            {
                insertDecimalPoint(&l4);
                p = p->next;
                q = q->next;
            }

            else if (q->data >= p->data)
            {
                insertLeft(&l4, q->data - p->data);
                q = q->next;
                p = p->next;
            }
            else if (q->data < p->data)
            {
                borrow = q->data - p->data + 10;
                insertLeft(&l4, borrow);
                p = p->next;
                q = q->next;
                if (q->data == -1)
                {
                    insertDecimalPoint(&l4);
                    p = p->next;
                    q = q->next;
                }
                q->data = q->data - 1;
            }
        }
        while (q)
        {

            insertLeft(&l4, q->data);
            q = q->next;
        }
        insertNegative(&l4);
        return l4;
    }
    else if (l5->next == NULL && l6->next == NULL)
    {
        if (l5->data > l6->data || (l5->data == l6->data && l5->prev->data > l6->prev->data))
        {
            while (p && q)
            {
                if (p->data == -1 && q->data == -1)
                {
                    insertDecimalPoint(&l4);
                    p = p->next;
                    q = q->next;
                }

                else if (p->data >= q->data)
                {
                    insertLeft(&l4, p->data - q->data);
                    p = p->next;
                    q = q->next;
                }
                else if (p->data < q->data)
                {
                    borrow = p->data - q->data + 10;
                    insertLeft(&l4, borrow);
                    p = p->next;
                    q = q->next;
                    if (q->data == -1)
                    {
                        insertDecimalPoint(&l4);
                        p = p->next;
                        q = q->next;
                    }
                    p->data = p->data - 1;
                }
            }
            return l4;
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
                if (p->data == -1 && q->data == -1)
                {
                    insertDecimalPoint(&l4);
                    p = p->next;
                    q = q->next;
                }

                else if (q->data >= p->data)
                {
                    insertLeft(&l4, q->data - p->data);
                    q = q->next;
                    p = p->next;
                }
                else if (q->data < p->data)
                {
                    borrow = q->data - p->data + 10;
                    insertLeft(&l4, borrow);
                    p = p->next;
                    q = q->next;
                    if (q->data == -1 && p->data == -1)
                    {
                        insertDecimalPoint(&l4);
                        p = p->next;
                        q = q->next;
                    }
                    q->data = q->data - 1;
                }
            }
            insertNegative(&l4);
            return l4;
        }
    }
}

number mul(number l1, number l2)
{
    number result, temp, new_temp;
    init(&result);
    init(&new_temp);
    node *n2 = l2.front;
    node *nn = l2.front;
    while(n2)
    {
        int carry = 0;
        number temp = new_temp;
        node *n1 = l1.front;
        while (n1) {
            if (n1->data == -1) {
                n1 = n1->next;
            } else if (n2->data == -1) {
                n2 = n2->next;
            } else {
                int prod = n1->data * n2->data + carry;
                carry = prod / 10;
                insertRight(&temp, prod % 10);
                n1 = n1->next;
            }
        }
        while (carry != 0) {
            insertRight(&temp, carry % 10);
            carry /= 10;
        }
        node * p = temp.front;
        result = add(reverse(result), temp);
        n2 = n2->next;
        nn = nn->next;
        node *n3 = nn;
        init(&new_temp);
        while (n3 != NULL && n3->prev != NULL) {
            insertRight(&new_temp, 0);
            n3 = n3->prev;
        }
    }
    int total_count = count(&l1) + count(&l2);
    number x;
    if(total_count > 0)
    {
        x = reverse(result);
        insertAtIndex(&x, total_count, -1);
        result = reverse(x);
    }
    return result;
}

int main()
{
    number l1, l2, l3, l4, l7;
    init(&l1);
    int d1, d2, num;
    printf("Enter the number of digits before decimal for l1: ");
    scanf("%d", &d1);
    for (int i = 1; i <= d1; i++)
    {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertLeft(&l1, num);
    }
    printf("Enter the number of digits after decimal for l1: ");
    scanf("%d", &d2);
    if(d2 > 0) insertDecimalPoint(&l1);
    for (int i = 1; i <= d2; i++)
    {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertLeft(&l1, num);
    }

    init(&l2);
    printf("Enter the number of digits before decimal for l2: ");
    scanf("%d", &d1);
    for (int i = 1; i <= d1; i++)
    {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertLeft(&l2, num);
    }
    printf("Enter the number of digits after decimal for l2: ");
    scanf("%d", &d2);
    if(d2 > 0) insertDecimalPoint(&l2);
    for (int i = 1; i <= d2; i++)
    {
        printf("Enter digit %d: ", i);
        scanf("%d", &num);
        insertLeft(&l2, num);
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
