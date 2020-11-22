#include <stdlib.h>
#include <stdio.h>



typedef struct Element{
    char letter; //Lettre
    struct Element *next; //Pointeur vers l'élément suivant
    int occ; //Nombre d'occurrence
} Element;

typedef Element* List;

int list_occurences(Element* l, int n){
    if (l == NULL) return 0;
    if (l -> data == n) return 1 + list_occurences(l -> next, n);
    return 0 + list_occurences(l -> next, n);
}


int main (void)
{

    list_occurences(struct Element, 5);

    return 0;
}
