#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

void seedRand(int seed)
{
    if (seed == -1)
      seed = time(0);

    srand(seed);
}

/** generate a random number between lo and hi */
int randomNumber(int lo, int hi)
{
  return (rand() % (hi - lo + 1)) + lo;
}

struct node {
    int value;
    struct node *next;
    struct node *prev;
};

struct list {
  struct node *head;
  struct node *z;
  struct node *front;
  struct node *back;
};
/** creates a new list object */
struct list* newList()
{
   struct list* newlist = (struct list*)malloc(sizeof(struct list));
   newlist->head = (struct node*)malloc(sizeof(struct node));
   newlist->z = (struct node*)malloc(sizeof(struct node));
   newlist->z->next = newlist->z;
   newlist->head->next = newlist->z;
   newlist->head->prev = newlist->head;
   newlist->z->prev = newlist->head;
   newlist->head->value = INT_MIN;
   newlist->z->value = INT_MAX;
   newlist->front = newlist->back = NULL;
   return newlist;
}

void listinsert(struct list **l, int n)
{
  struct node* tmp = (struct node*)malloc(sizeof(struct node));
  tmp->value = n;
  if ((*l)->head->next == (*l)->z)
  {
      (*l)->head->next = (*l)->front = (*l)->back = tmp;
  } 
  tmp->next = (*l)->z;
  tmp->prev = (*l)->z->prev;
  (*l)->back->next = tmp;
  (*l)->z->prev = (*l)->back = tmp;
}
/** swaps the value of two list elements */
void swapVal(struct node **a, struct node **b)
{
    int tmp = (*a)->value;
    (*a)->value = (*b)->value;
    (*b)->value = tmp;
}

/** Generate a singly linked list of N random numbers between lo and hi */
struct list* randomList(int size, int lo, int hi)
{
   srand(time(0));

   struct list* randlist = newList();
   
   int n;
   for (int i = 1; i < size; i++)
   {
       n = randomNumber(lo, hi);
       listinsert(&randlist, n);
   }
   return randlist;
}

/** print a singly linked list */
void printList(struct list* plist)
{
    for (struct node *itr = plist->front; itr != plist->z; itr = itr->next)
    {
        printf("%d ", itr->value);
    }
    printf("\n");
}

void printListB(struct list *l)
{
    //For loops are prettier, but what the hey.
    struct node *it = l->back; 
    while (it != l->head)
    {
        printf("%d ", it->value);
        it = it->prev;
    } 
    printf("\n");
}
