#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int info;
    struct Node* next;
    struct Node* prev;
};

void push(struct Node** head_ref, int new_info)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->info = new_info;

    new_node->next = (*head_ref);
    new_node->prev = NULL;

    if ((*head_ref) != NULL)
    {
        (*head_ref)->prev = new_node;
    }

    (*head_ref) = new_node;
}

void printList(struct Node* node)
{
    while (node != NULL)
    {
        printf("info = %d  ptr = %d  next = %d  prev = %d\n", node->info,node,node->next,node->prev);
        node = node->next;
    }
}

void RightShift(struct Node* head_ref, int num)
{
    for (int i = 0; i < num; i++)
    {
        while ((head_ref->next) != NULL)
        {
            head_ref = head_ref->next;
        }
        int last = head_ref->info;

        while (head_ref->prev != NULL)
        {
            head_ref->info = head_ref->prev->info;
            head_ref = head_ref->prev;
        }
        head_ref->info = last;
    }
}

int main()
{
    int n;
    printf("Amount of elements:");
    scanf("%d",&n);

    srand(time(NULL));
    struct Node* head = NULL;
    for(int i = 0; i < n; i++)
    {
        push(&head, rand() %100);
    }

    printf("Original list:\n");
    printList(head);

    RightShift(head, 3);
    printf("Shifted list:\n");
    printList(head);

    return 0;
}