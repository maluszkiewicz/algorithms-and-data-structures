#include "huffman.h"

//////////////////////////////////////////////////////
// I/O file operations
string importFile() {
  string fileName;
  cout << "Podaj nazwe pliku do wczytania: ";
  cin >> fileName;

  ifstream file(fileName.c_str(),ifstream::in);

  if(file.good()) {
    string input;
    file.seekg(0,ios::end);
    input.reserve(file.tellg());
    file.seekg(0,ios::beg);

    input.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return input;
  } else {
    cout << "Nie moge znalezc pliku " << fileName << ". Koniec dzialania programu..." << endl;
    exit(-1);
  }
}

string importFile(string fileName) {
  ifstream file(fileName.c_str(),ifstream::in);

  if(file.good()) {
    string input;
    file.seekg(0,ios::end);
    input.reserve(file.tellg());
    file.seekg(0,ios::beg);

    input.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return input;
  } else {
    cout << "Nie moge znalezc pliku " << fileName << ". Koniec dzialania programu..." << endl;
    exit(-1);
  }
}

//////////////////////////////////////////////////////
// counting char and MTF code
unsigned int *countChars(string input) {
  unsigned int *charsFrequency = new unsigned int[256];
  unsigned int length = input.size();
  
  for(int i=0;i<256;i++) {
    charsFrequency[i] = 0;
  }

  for(unsigned int i=0;i<length;i++) {
    ++charsFrequency[(unsigned int)input.at(i)];
  }
  
  return charsFrequency;
}

unsigned int *getMTFCode(string input) {
  unsigned int length = input.size();
  unsigned int *mtfCode = new unsigned int[length];

  unsigned int iterator = 0, counter;
  char current;
  
  for(unsigned int i=0;i<length;i++) {
    counter = 0;
    current = input.at(i);

    do {
      if((char)(iterator%256)==current) {
        mtfCode[i] = counter;
        break;
      } else {
        ++iterator;
      }
    } while(++counter <= 256);
  }
  return mtfCode;
}

unsigned int *getMTFFrequencies(string input) {
  unsigned int *charsFrequency = countChars(input);
  unsigned int *mtfCode = getMTFCode(input);
  unsigned int *mtfFrequencies = new unsigned int[256];
  for(unsigned int i=0;i<256;i++) {
    mtfFrequencies[i] = 0;
  }
  
  unsigned int length = input.size();
  for(unsigned int i=0;i<length;i++) {
    ++mtfFrequencies[mtfCode[i]];
  }

  return mtfFrequencies;
}  

//////////////////////////////////////////////////////
// printing out results
void printMTFFrequencies(unsigned int *mtfFrequencies) {
  for(unsigned int i=0;i<256;i++) {
    if(mtfFrequencies[i]!=0)
      cout << "MTF_FREQUENCY[" << i << "] = " << mtfFrequencies[i] << endl;
  }
}

//////////////////////////////////////////////////////
// Node class
void Node::preorderCodeAssign(string prefix, string *hCodes) {
  if(value!=1000)
    hCodes[value] = prefix;

  if(lSon!=NULL) {
    lSon->preorderCodeAssign(prefix + "0",hCodes);
  }

  if(rSon!=NULL) {
    rSon->preorderCodeAssign(prefix + "1",hCodes);
  }
}

unsigned int Node::getFrequency() {
  return frequency;
}

void Node::print() {
  cout << "(" << frequency << "," <<value << ")" << endl;
}

void Node::del() {
  if(lSon!=NULL)
    lSon->del();
  if(rSon!=NULL)
    rSon->del();
  delete this;
}

Node::Node(unsigned int frequency, unsigned int value) {
  parent = lSon = rSon = NULL;
  this->frequency = frequency;
  this->value = value;
}

//////////////////////////////////////////////////////
// Element class
Element::Element(Node *n) {
  node = n;
  previous = next = NULL;
}

//////////////////////////////////////////////////////
// Tree class
string *Tree::assignCodes() {
  string *hCodes = new string[256];

  if(root->value!=1000) {
    hCodes[root->value] = root->frequency;
  }

  root->lSon->preorderCodeAssign("0",hCodes);
  root->rSon->preorderCodeAssign("1",hCodes);
  return hCodes;
}

void Tree::del() {
  root->del();
  delete this;
}

Tree::Tree() {
  root = NULL;
}

//////////////////////////////////////////////////////
// List class
void List::addElement(Node *n) {
  Element *newElement = new Element(n);

  if(first==NULL) {
    last = first = newElement;
    ++length;
    return;
  }

  Element *e = first;

  if(newElement->node->frequency >= e->node->frequency) { 
    newElement->next = e;
    e->previous = newElement;

    first = newElement;
    ++length;
    return;
  }

  while(e->next!=NULL) {
    e = e->next;
    if(newElement->node->frequency >= e->node->frequency) {
      if(e->previous!=NULL) {
        newElement->previous = e->previous;
        e->previous->next = newElement;
      }

      e->previous = newElement;
      newElement->next = e;
      ++length;

      return;
    }
  }

  e->next = newElement;
  newElement->previous = e;
  last = newElement;
  ++length;
}

Node *List::back() {
  return last->node;
}

void List::popBack() {
  if(length==0) {
    cout << "Can't popBack(): List is empty..." << endl;
    return;
  }

  if(length==1) {
    delete last;
    last = first = NULL;
  } else {
    Element *e = last;
    last = last->previous;
    last->next = NULL;
    delete e;
  }
  --length;
}

unsigned int List::size() {
  return length;
}

void List::print() {
  if(first==NULL) {
    cout << "Can't print an empty list..." << endl;
    return;
  }

  Element *e;
  e = first;
  cout << "(frequency,value)" << endl << "-------------------" << endl;
  do {
    cout << "(" << e->node->frequency << "," << e->node->value << "), ";
    e = e->next;
  } while(e!=NULL);
  cout << "\b\b \b" << endl;
}

Tree *List::buildTree() {
  Tree *T = new Tree();
  Node *n1, *n2, *newNode;

  if(this->length<2) {
    cout << "Can't build a tree, when there is less than 2 elements in the list." << endl;
    return NULL;
  }

  while(this->length>1) {
    n1 = this->back();
    this->popBack();
    n2 = this->back();
    this->popBack();

    newNode = new Node(n1->frequency+n2->frequency,1000);
    newNode->lSon = n1;
    newNode->rSon = n2;
    
    this->addElement(newNode);
  }

  T->root = this->back();
  this->popBack();

  return T;
}

void List::del() {
  Element *e1 = first;
  
  while(e1!=last) {
    e1 = e1->next;
    delete e1->previous;
  }
  
  delete e1;
  
  delete this;
}

List::List() {
  first = last = NULL;
  length = 0;
}

//////////////////////////////////////////////////////
