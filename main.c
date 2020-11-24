#include <stdlib.h>
#include <stdio.h>

#include "Header.h"

int main() 
{
  char letters[] = {'A', 'B', 'C', 'D', ' ', 'f', 'n'};
  int freq[] = {5, 1, 6, 7, 1, 6, 7};
  int taille = sizeof(letters) / sizeof(letters[0]);

  tree(letters, freq, taille);
  int code[10000];
  int i = 0;
  struct Node* root = tree(letters, freq, taille); 
  printCodes(root, code, i);

}