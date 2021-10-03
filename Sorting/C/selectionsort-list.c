#include <stdio.h>
#include <stdlib.h>
#include "../listhelpers.h"



void selSort(struct list **l)
{
    struct node* smallest;
    for (struct node* itr = (*l)->front; itr != (*l)->z; itr = itr->next)
    {
        smallest = itr;
        for (struct node* small = itr; small != (*l)->z; small = small->next)
            if (small->value < smallest->value)
                smallest = small;
        
        if (smallest->value < itr->value)
            swapVal(&itr, &smallest);
    }
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