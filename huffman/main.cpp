#include "huffman.h"

int main(void) {
  cout << endl;

  string input = importFile();  
  unsigned int *mtfFrequencies = getMTFFrequencies(input);
  
  List *L = new List();
  for(unsigned int i=0;i<256;i++) {
    if(mtfFrequencies[i]!=0) {
      L->addElement(new Node(mtfFrequencies[i],i));
    }
  }

  unsigned int length = L->size();
  Tree *T = L->buildTree();
  L->del();
  string *hCodes = T->assignCodes();
  T->del();

  cout << "Printing Huffman Codes:" << endl << endl;
  cout << "MTF VALUE ==> HUFFMAN_CODE" << endl;
  for(unsigned int i=0;i<256;i++) {
    cout << i << " ==> " << hCodes[i] << endl; 
  }

  string encoded;
  unsigned int inputLength = input.size();
  unsigned int *mtfCode = getMTFCode(input);

  for(unsigned int i=0;i<inputLength;i++) {
    encoded = encoded + hCodes[mtfCode[i]];
  }

  cout << endl << "ENCODED: " << encoded << endl;
  cout << endl << "INPUT BITS: " << inputLength*8 << endl;
  cout << "ENCODED BITS: " << encoded.size() << endl;
  cout << "Compression ratio: " << (double)encoded.size()/(inputLength*8) << '%' << endl;

  return 0;
}
