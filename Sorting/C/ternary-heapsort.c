/*
	coded this on my lunch break, i wanted to see if the recursive 
	heapify algorithm could be extended out to ternary heaps.
	judgeing by the looks of it, it could be extended out to
	d-ary heaps.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void ternaryheapify(int a[], int n, int k) {
	int largest = k;
	int l = 2*k;
	int m = 2*k + 1;
	int r = 2*k + 2;
	if (l < n && a[l] > a[largest]) {	
		largest = l;
	}
	if (m < n && a[m] > a[largest]) {
		largest = m;
	}
	if (r < n && a[r] > a[largest]) {
		largest = r;
	}
	if (largest != k) {
		int t = a[largest];
		a[largest] = a[k];
		a[k] = t;
		ternaryheapify(a, n, largest);
	}
}

void ternaryheapsort(int a[], int n) {
	for (int i = n/2; i  >= 0; i--)
		ternaryheapify(a, n, i);
	for (int i = n - 1; i > 0; i--) {
		int t = a[0];
		a[0] = a[i];
		a[i] = t;
		ternaryheapify(a, i, 0);
	}
}

_Bool checksort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i+1] < a[i])
			return false;
	}
	return true;
}

int main()
{
	int ts[25];
	for (int i = 0; i < 25; i++) {
		ts[i] = rand() % 100;
		printf("%d ", ts[i]);
	}
	puts(" ");
	ternaryheapsort(ts, 25);
	for (int i = 0; i < 25; i++)
		printf("%d ", ts[i]);
	puts(" ");
	if (checksort(ts, 25)) puts("Ternary Heapsort Successful.");
	else puts("This weird sort doesnt even work.");
	return 0;
}