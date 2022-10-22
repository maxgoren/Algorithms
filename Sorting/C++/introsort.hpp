#ifndef INTROSORT_HPP
#define INTROSORT_HPP
//Max Goren 10/21/22
//Introsort, A quicksort variant originally developed for the C++ STL
//It is a combination of quicksort using a median of three pivot, a small
//subarray insertion sort and crucially, it falls back to heapsort when
//the depth of recursion is becoming too deep, thus allowing for a guranteed
//worst case of O(nlogn).

template <class T>
static void exch(T a[], int l, int r) {
    T tmp = a[l]; a[l] = a[r]; a[r] = tmp;
}
 
template <class T>
void fixDown(T a[], int k, int N) {
    while (2*k <= N) {
        int j = 2*k;
        if (j < N && a[j] < a[j+1]) j++;
        if (!(a[k] < a[j])) break;
        exch(a, k, j); k = j;
    }
}

template <class T>
void heapsort(T a[], int l, int r) {
    int k, N = r-l+1;
    T *pq = a+l-1;
    for (k = N/2; k >= 1; k--)
        fixDown(pq, k, N);
    while (N > 1) {
        exch(pq, 1, N);
        fixDown(pq, 1, --N);
    }
}

template <class T>
void inssort(T a[], int l, int r) {
    for (int i = l; i <= r; i++) {
        int j = i; T v = a[j];
        while (j > l && a[j - 1] > v) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

template <class T>
int partition(T a[], int l, int r) {
    int i = l - 1, j = r; T v = a[r];
    for (;;) {
        while (a[++i] < v);
        while (a[--j] > v) if (j == l) break;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, i, r);
    return i;
}

template <class T>
void medOf3(T a[], int l, int r) {
    int m = (l+r)/2;
    if (a[m] < a[l])
        exch(a, m, l);
    if (a[r] < a[l])
        exch(a, l, r);
    if (a[m] < a[r])
        exch(a, m, r);
}

template <class T>
void introsort(T a[], int l, int r, int d) {
    if (d == 0) {
        heapsort(a, l, r);
        return;
    }
    if (r - l < 7) {
        inssort(a, l, r);
    } else {
        medOf3(a, l, r);
        int i = partition(a, l, r);
        introsort(a, l, i - 1, d - 1);
        introsort(a, i + 1, r, d - 1);
    }
}

template <class T>
void IntroSort(T a[], int l, int r) {
    int d = floor(2 * log(r-l));
    introsort(a, l, r, d);
}

#endif