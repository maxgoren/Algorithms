#include <iostream>
#include <iomanip>
#include <queue>
#include <thread>
#include <cmath>
#include <climits>
#include <map>
#include <vector>
#include <algorithm>
#include "../helpers-stl.h"
using namespace std;

void swap(vector<int>& a, int i , int j)
{
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void quickSort(vector<int>& a, int l, int r)
{
  int temp;
  if (r - l >= 0)
  {
    int v = a[r];
    int i = l - 1;
    int j = r;
    for (;;)
    {
      while (a[++i] < v);
      while (a[--j] > v);
      if (i >= j) break;
      temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
    temp = a[i];
    a[i] = a[r];
    a[r] = temp;
    quickSort(a, l, i-1);
    quickSort(a, i+1, r);
  }
  
}

void quicksort(vector<int>& a)
{
    quickSort(a, 0, a.size()-1);
}

void heapSort(std::vector<int>& a)
{
    std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
    for (auto n : a)
    {
        pq.push(a.back());
        a.pop_back();
    }
    while (!pq.empty())
    {
        a.push_back(pq.top());
        pq.pop();
    }
}

void bubbleSort(std::vector<int>& data)
{
   int temp;
   for (int i = 0; i < data.size(); i++)
   {
       for (int j = i + 1; j < data.size(); j++)
       {
           if (data[j] < data[i])
           {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
           }
       }
   }
}

void bubbleSort2(std::vector<int>& data)
{
   int temp;
   for (int i = 0; i < data.size(); i++)
   {
       for (int j = data.size() - 1; j > i; j--)
       {
           if (data[j] < data[i])
           {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
           }
       }
   }
}

void shellSort(vector<int>& arr) 
{ 
    int N = arr.size(); 
    for (int gap = N/2; gap > 0; gap /= 2) 
    { 
        for (int i = gap; i < N; i += 1) 
        { 
            //sort sub lists created by applying gap 
            int temp = arr[i]; 
 
            int j; 
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
            {
                arr[j] = arr[j - gap]; 
            }  
            arr[j] = temp; 
        } 
    } 
} 

void selectionSort(std::vector<int>& data)
{
    int temp;
    for (int i = 0; i < data.size()-1; i++)
    {
        int least = i;
        for (int j = i; j < data.size(); j++)
        {
            if (data[j] < data[least])
            {
                least = j;
            }
        }
        if (data[least] < data[i])
        {
            temp = data[i];
            data[i] = data[least];
            data[least] = temp;
        }
    }
}

void OptselectionSort(std::vector<int>& data)
{
 
    int N = data.size() - 1;
    for (int i = 0; i < N; i++)
    {
        int least = i;
        int greatest = N - 1;
        for (int j = i; j < data.size(); j++)
        {
            if (data[j] < data[least])
            {
                least = j;
            }
            if (data[j] > data[greatest])
            {
                greatest = j;
            }
        }
        if (data[least] < data[i])
        {
            swap(data, i, least);
        }
        if (data[greatest] > data[data.size() - i])
        {
            swap(data, i, greatest);
        }
        N = data.size() - i;
    }
}

void insertionSort(std::vector<int>& data)
{
    int i;
    int j;
    int v;
    for (int i = 1; i < data.size(); i++)
    {
        j = i;
        v = data[j];
        while (data[j - 1] > v && j >= 0)
        {
            data[j] = data[j-1];
            j--;
        }
        data[j] = v;
    }
}

std::pair<string, double> timedRun(int numRuns, string algoName, void (*fncptr)(vector<int>&), vector<int>& a)
{
    std::chrono::duration<double, std::milli> timing;
    std::chrono::duration<double, std::milli> average;
    //cout<<endl<<algoName<<": "<<endl;
    for (int i = 0; i < numRuns; i++)
    {
      auto t1 = std::chrono::steady_clock::now();
      fncptr(a);
      auto t2 = std::chrono::steady_clock::now();
      timing = t2 - t1;
      //cout<<"Run "<<i+1<<": "<<timing.count()<<"ms"<<endl;
      average += timing;
    }
    //cout<<"average running time: "<<setprecision(3)<<average.count()/3<<"ms"<<endl;
    std::pair<string, double> ret = std::make_pair(algoName, average.count()/3);
    return ret;
}

void merge(std::vector<int>& A, int s, int m, int e)
{
   std::vector<int> C;
   int i = s; int j = m+1; int k = 0;
   while (i <= m && j <= e)
   {
       if (A[i] <= A[j])
       {
           C.push_back(A[i]);
           ++i;
       } else {
           C.push_back(A[j]);
           ++j;
       }
   }
   while (i <= m) 
   {
     C.push_back(A[i]);
     ++i;
   }
   while (j <= e)
   {
      C.push_back(A[j]);
      ++j;
   }
   for (int i = s; i <= e; ++i)
   {
       A[i] = C[i-s];
   }
}

void msort(std::vector<int>& tosort, int s, int e)
{
    if (s < e)
    {
      int i;
      int m = (s+e) / 2;

      msort(tosort, s, m);
      msort(tosort, m+1, e);
      merge(tosort, s, m, e);
    }
}

void mergeSort(vector<int>& sort)
{
    msort(sort, 0, sort.size()-1);
}

bool cmp(std::pair<string,double>& a, std::pair<string, double>& b)
{
    return a.second < b.second;
}

void shootout(vector<int>& vec)
{
    std::vector<int> sorted;
    std::map<string, double> averages;
    std::vector<std::pair<string, double> > shoot;
    typedef void fncptr(vector<int>&);
    typedef fncptr* pfunc_t;
    std::vector<pair<string,pfunc_t> > sorts;
    sorts.push_back(make_pair("Heapsort", heapSort));
    sorts.push_back(make_pair("Quicksort", quicksort));
    sorts.push_back(make_pair("Bubble sort", bubbleSort));
    sorts.push_back(make_pair("Bubble sort2", bubbleSort2));
    sorts.push_back(make_pair("Selection sort", selectionSort));
    sorts.push_back(make_pair("Insertion sort", insertionSort));
    sorts.push_back(make_pair("Selection sort+", OptselectionSort));
    sorts.push_back(make_pair("Shell sort", shellSort));
    sorts.push_back(make_pair("Merge sort", mergeSort));
    
    for (auto p : sorts)
    { 
      sorted = vector_of_randoms<int>(100, INT_MIN, INT_MAX);
      auto [name, avg] = timedRun(10, p.first, p.second, sorted);
      averages[name] = avg;
    }
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Test one: Average of 10 runs, Each run performed on new random data set.\n";
    cout<<"Sample size: "<<sorted.size()<<" items of type: "<<typeid(vec[0]).name()<<endl;
    cout<<"Rank    Algorithm    Time To Execute "<<endl;
    cout<<"---------------------------------------\n";
    
    for (auto a : averages)
      shoot.push_back(a);
    std::sort(shoot.begin(), shoot.end(), cmp);
    for (int q = 0; q < shoot.size(); q++)
    {
      cout<<q+1<<": "<<setw(15)<<shoot[q].first<<" - "<<setprecision(3)<<shoot[q].second<<"ms"<<endl;
    }
    averages.clear();
    
    for (auto p : sorts)
    { 
      vector<int> sorted = vec;
      auto [name, avg] = timedRun(5, p.first, p.second, sorted);
      averages[name] = avg;
    }
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Test two: Average of 5 runs, All algorithms recieve same data set.\n";
    cout<<"Sample size: "<<vec.size()<<" items of type: "<<typeid(vec[0]).name()<<endl;
    cout<<"Rank    Algorithm    Time To Execute "<<endl;
    cout<<"---------------------------------------\n";
    shoot.clear();
    for (auto a : averages)
      shoot.push_back(a);
    std::sort(shoot.begin(), shoot.end(), cmp);
    for (int q = 0; q < shoot.size(); q++)
    {
      cout<<q+1<<": "<<setw(15)<<shoot[q].first<<" - "<<setprecision(3)<<shoot[q].second<<"ms"<<endl;
    }
    averages.clear();


    for (auto p : sorts)
    { 
      vector<int> sorted = vector_of_randoms<int>(1000,25,75);
      auto [name, avg] = timedRun(5, p.first, p.second, sorted);
      averages[name] = avg;
    }
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Test three: Average of 5 runs, All algorithms recieve unique, limited varying data set.\n";
    cout<<"Sample size: "<<vec.size()<<" items of type: "<<typeid(vec[0]).name()<<endl;
    cout<<"Rank    Algorithm    Time To Execute "<<endl;
    cout<<"---------------------------------------\n";
    shoot.clear();
    for (auto a : averages)
      shoot.push_back(a);
    std::sort(shoot.begin(), shoot.end(), cmp);
    for (int q = 0; q < shoot.size(); q++)
    {
      cout<<q+1<<": "<<setw(15)<<shoot[q].first<<" - "<<setprecision(3)<<shoot[q].second<<"ms"<<endl;
    }
    averages.clear();



    for (auto p : sorts)
    { 
      sorted = vector_of_randoms<int>(5000, INT_MIN, INT_MAX);
      auto [name, avg] = timedRun(10, p.first, p.second, sorted);
      averages[name] = avg;
    }
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Test Four: Average of 10 runs, Each run performed on new random data set.\n";
    cout<<"Sample size: "<<sorted.size()<<" items of type: "<<typeid(vec[0]).name()<<endl;
    cout<<"Rank    Algorithm    Time To Execute "<<endl;
    cout<<"---------------------------------------\n";
    shoot.clear();
    for (auto a : averages)
      shoot.push_back(a);
    std::sort(shoot.begin(), shoot.end(), cmp);
    for (int q = 0; q < shoot.size(); q++)
    {
      cout<<q+1<<": "<<setw(15)<<shoot[q].first<<" - "<<setprecision(3)<<shoot[q].second<<"ms"<<endl;
    }

    for (auto p : sorts)
    { 
      vector<int> sorted = vector_of_randoms<int>(90000,1,5000);
      auto [name, avg] = timedRun(5, p.first, p.second, sorted);
      averages[name] = avg;
    }
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Test Five: Average of 5 runs, All algorithms recieve unique, somewhat limited varying data set.\n";
    cout<<"Sample size: "<<vec.size()<<" items of type: "<<typeid(vec[0]).name()<<endl;
    cout<<"Rank    Algorithm    Time To Execute "<<endl;
    cout<<"---------------------------------------\n";
    shoot.clear();
    for (auto a : averages)
      shoot.push_back(a);
    std::sort(shoot.begin(), shoot.end(), cmp);
    for (int q = 0; q < shoot.size(); q++)
    {
      cout<<q+1<<": "<<setw(15)<<shoot[q].first<<" - "<<setprecision(3)<<shoot[q].second<<"ms"<<endl;
    }
    averages.clear();

}


int main()
{
    vector<int> a = vector_of_randoms<int>(3000, INT_MIN, INT_MAX);
    vector<int> sorted;
    sorted = a;
    shootout(a);
    return 0;
}
