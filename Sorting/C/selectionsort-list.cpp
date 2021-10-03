#include <iostream>
#include "small-list.h"
using namespace std;

void selectionSort(List& tosort)
{
    for (auto itr = tosort.front; itr != tosort.z; itr = itr->next)
    {
        auto smallest = itr;
        for (auto it = itr; it != tosort.z; it = it->next)
            if (it->d < smallest->d)
                smallest = it;
            
        if (smallest->d < itr->d)
          swap(itr->d, smallest->d);
    }
}

int main()
{
    srand(time(NULL));
    List myList = randomList(12, 1, 20);
    myList.showList();
    selectionSort(myList);
    myList.showList();
    return 0;
}