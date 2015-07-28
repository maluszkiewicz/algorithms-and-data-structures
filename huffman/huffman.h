#ifndef HUFFMAN_h
#define HUFFMAN_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

// file I/O operations
string importFile();
string importFile(string fileName);

// char and MTF arrays
unsigned int *countChars(string input);
unsigned int *getMTFCode(string input);
unsigned int *getMTFFrequencies(string input);

// printing out results
void printMTFFrequencies(unsigned int *mtfFrequencies);

// Node class
class Node {
 public:
  Node *parent, *lSon, *rSon;
  unsigned int frequency, value;
  void preorderCodeAssign(string prefix, string *hCodes);
  unsigned int getFrequency();
  void print();
  void del();
  Node(unsigned int frequency, unsigned int value);
};

// Element class
class Element {
 public:
  Node *node;
  Element *previous, *next;
  Element(Node *n);
};

// Tree class
class Tree {
 public:
  Node *root;
  string *assignCodes();
  void del();
  Tree();
};

// List class
class List {
 public:
  Element *first, *last;
  unsigned int length;
  void addElement(Node *n);
  Node *back();
  void popBack();
  unsigned int size();
  void print();
  void del();
  Tree *buildTree();
  List();
};

#endif // HUFFMAN_h
