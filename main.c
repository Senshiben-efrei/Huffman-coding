#include <stdlib.h>
#include <stdio.h>
#include "Header.h"
#define LEN 256


int main() 
{
  Element* A = new_letter('A',1);
  Element* B = new_letter('B',2);
  Element* C = new_letter('C',3);
  Element* D = new_letter('D',4);

  A->next = B;
  B->next = C;
  C->next = D;   



  dictionairify(A);
}