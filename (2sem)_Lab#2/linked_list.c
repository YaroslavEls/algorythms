#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct linked_list
{
    int info;
    struct linked_list * next;
}   l_list ;

l_list * l_list_init(int item)
{
    l_list *l_p ;
    l_p = malloc(sizeof(struct linked_list));
    *l_p = (l_list)
            { .info = item,
              .next = NULL
            };
    return l_p;
}

l_list * add_list(l_list *l_p, int item)
{
    struct linked_list *node_p ;
    node_p = malloc(sizeof(struct linked_list));
    node_p->info = item;
    node_p->next = l_p;
    return node_p;
}

void printList(l_list * head)
{
    printf("Original list:\n");
    while (head)
    {
        printf("info = %d  ptr = %d  next = %d\n", head->info,head,head->next);
        head = head->next;
    }
}

void RightShift(l_list * head, int num) {
    l_list *p, *first, *last, *perv;
    last = perv = p = first = head;

    while ((last->next) != NULL) last = last->next;

    int count = 0;
    while (count != num)
    {
        if (p->next == NULL)
        {
            p = head;
            count++;
            continue;
        }
        p = p->next;
        count++;
    }
    head = head->next;

    while ((p->next) != NULL)
    {
        p = p->next;
        first = first->next;
        head = head->next;
    }

    first->next = NULL;
    last->next = perv;

    printf("Shifted list:\n");
    while (head)
    {
        printf("info = %d  ptr = %d  next = %d\n", head->info,head,head->next);
        head = head->next;
    }
}

int main()
{
    int n, list_p;

    printf("Amount of elements:");
    scanf("%d",&n);

    srand(time(NULL));
    list_p = l_list_init(rand() %100);
    for(int i = 0; i < n-1; i++)
    {
        list_p = add_list(list_p, rand() %100);
    }

    printList(list_p);
    RightShift(list_p, 3);
}