#include <stdio.h>
#include <stdlib.h>
#include "list-helpers.h"

void insertSorted(struct list **l, int n)
{
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    tmp->value = n;
    
    if ((*l)->head->next == (*l)->z)
    {
        tmp->next = (*l)->z;
        tmp->prev = (*l)->head;
        (*l)->head->next = (*l)->front = (*l)->back = tmp;
        (*l)->z->prev = tmp;
        return;
    }
    for (struct node* it = (*l)->head; it != (*l)->z; it = it->next)
    {
        if (n > it->value && n <= it->next->value)
        {
            tmp->prev = it;
            tmp->next = it->next;
            it->next->prev = tmp;
            it->next = tmp;
            break;
        }
    }
}

struct list* insertionSortWRONG(struct list **l)
{
    struct list* newlist = newList();
    for (struct node* it = (*l)->front; it != (*l)->z; it = it->next)
    {
        insertSorted(&newlist, it->value);
    }
    return newlist;
}

void insertionSort(struct list **l)
{
  struct node* itr = (*l)->front;
  struct node*  p = itr;
  for (itr = p->next; itr != (*l)->z; itr = itr->next)
  {
      int v = itr->value;
      p = itr;
      while (p->prev->value > v){
        p->value = p->prev->value;
        p = p->prev;
      }
      p->value = v;
  }
}

int main(int argc, char *argv[])
{
    seedRand(-1);
    struct list* list = randomList(10, 1, 100);
    printList(list);
    insertionSort(&list); 
    printList(list); 
    return 0;
}
