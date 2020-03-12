#include "path.h"
#include "stdlib.h"

t_path *split(t_path *head)
{
    t_path *fast;
    t_path  *slow;
    t_path *temp;

    fast= head;
    slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    temp = slow->next;
    slow->next = NULL;
    return (temp);
}

t_path *merge(t_path *first, t_path *second)
{
    if (!first)
        return second;
    if (!second)
        return first;
    if (first->length < second->length)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return (first);
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return (second);
    }
}

t_path *merge_sort(t_path *head)
{
    t_path *second;

    if (!head || !head->next)
        return head;
    second = split(head);
    head = merge_sort(head);
    second = merge_sort(second);
    return (merge(head,second));
} 