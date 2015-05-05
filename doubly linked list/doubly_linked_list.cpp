/*
  Implementation of doubly linked list.
  author: Konrad Maluszkiewicz
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

  typedef struct Node {
    int x;
    Node *next;
    Node *previous;
  } Node;

  typedef struct Root {
    Node *first;
    Node *last;
  } Root;

  void print_recursively(Node *p) {
    if(p==NULL)
      return;
    
    if(p->next!=NULL) {
      cout << " (x = " << p->x << "),";
    } else {
      cout << " (x = " << p->x << ") ";
    }
    print_recursively(p->next);
  }

  void print_list(Root *k) {
    if(k->first == NULL) {
      cout << "List is empty." << endl;
      return;
    }
    cout << "[";
    print_recursively(k->first);
    cout << "]" << endl;
  }

  void add_node(int x, Root *k) {

    Node *p = new Node();

    p->x = x;
    p->next = NULL;
    p->previous = k->last;

    if(p->previous != NULL) {
      p->previous->next = p;
    }

    k->last = p;
    if(k->first == NULL) {
      k->first = p;
    }
  }

  void free_recursively(Node *p) {
    if(p->next != NULL) {
      free_recursively(p->next);
    }
    free(p);
  }

  void delete_list(Root *k) {
    if(k->first != NULL && k->first->next != NULL) {
      free_recursively(k->first->next);
    }
    free(k);
  }

int main(void)
{
  Root *k = new Root();
  k->first = k->last = NULL;

  for(int i=0;i<5;i++) {
    add_node(i,k);
  }

  print_list(k);

  delete_list(k);

  return 0;
}