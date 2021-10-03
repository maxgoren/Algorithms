#include <stdio.h>
#include <stdlib.h>
#include "list-helpers.h"



void bubbleSort(struct list **l)
{
    struct node* smallest;
    for (struct node* itr = (*l)->front; itr != (*l)->z; itr = itr->next)
      for (struct node* bub = itr->next; bub != (*l)->z; bub = bub->next)
        if (bub->value < itr->value)
          swapVal(&itr, &bub);
}

int main(int argc, char *argv[])
{
    seedRand(-1);
    struct list* list = randomList(10, 1, 100);
    printList(list);
    selSort(&list);  
    printList(list);
    return 0;
}
