/*
  Implementation of Quick Sort: O(nlogn) sorting algorithm.
  author: Konrad Maluszkiewicz
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MIN 1
#define MAX 100

void swap(int *a, int *b) {
  int *c = a;
  a = b;
  b = c;
}

int partition(double A[], int p, int k) {
  int pivot = A[k];
  int i = p-1;

  for(int j=p;j<k;++j) {
    if(A[j] <= pivot) {
      ++i;
      swap(A[i],A[j]);
    }
  }
  swap(A[i+1],A[k]);
  return i+1;
}

int partition(int A[], int p, int k) {
  int pivot = A[k];
  int i = p-1;

  for(int j=p;j<k;++j) {
    if(A[j] <= pivot) {
      ++i;
      swap(A[i],A[j]);
    }
  }
  swap(A[i+1],A[k]);
  return i+1;
}

void quick_sort_helper(double A[], int p,int k) {
  int b = partition(A,p,k);
  if(b-1 > p)
    quick_sort_helper(A,p,b-1);
  if(b+1 < k)
    quick_sort_helper(A,b+1,k);
}

void quick_sort_helper(int A[], int p,int k){
  int b = partition(A,p,k);
  if(b-1 > p)
    quick_sort_helper(A,p,b-1);
  if(b+1 < k)
    quick_sort_helper(A,b+1,k);
}

void quick_sort(double A[], int n) {
  quick_sort_helper(A,0,n-1);
}

void quick_sort(int A[], int n) {
  quick_sort_helper(A,0,n-1);
}

void print_table(double A[], int n) {
  cout << "[ ";
  for(int i=0;i<n-1;++i) {
    cout << A[i] << ", ";
  }

  cout << A[n-1] << " ]";
}

void print_table(int A[], int n) {
  cout << "[ ";
  for(int i=0;i<n-1;++i) {
    cout << A[i] << ", ";
  }

  cout << A[n-1] << " ]";
}

void fill_table(double A[], int n)
{
  for(int i=0;i<n;++i) {
    A[i] = (MAX - MIN) * ((double)rand()/(double)RAND_MAX) + MIN;
  }   
}

void fill_table(int A[], int n)
{
  for(int i=0;i<n;++i) {
    A[i] = (rand() % (MAX - MIN + 1)) + MIN;
  }
}

int main(void)
{
  srand(time(0));
  int n = 0;

  cout << "How many elements should be in the table: ";
  cin >> n;

  if(n<2 || n > 3000) {
    do {
      cout << "The number is outside the permitted range <2..3000>. Please enter a valid number: ";
      cin >> n;
    } while(n<2 || n > 3000);
  }

  char choice = ' ';

  do {
    cout << endl << "What should be the type of numbers in the table? [d for double, i for integer]: ";
    cin >> choice;
  } while(choice!='i' && choice !='d');

  if(choice=='i') {
    int A[n];
    fill_table(A,n);

    cout << endl << "Table before sorting: ";
    print_table(A,n);

    quick_sort(A,n);
    cout << endl << endl << "Table after sorting: ";
    print_table(A,n);
    cout << endl;

  } else if(choice=='d') {
    double A[n];
    fill_table(A,n);

    cout << endl << "Table before sorting: ";
    print_table(A,n);

    quick_sort(A,n);
    cout << endl << endl << "Table after sorting: ";
    print_table(A,n);
    cout << endl;
  }

  return 0;
}