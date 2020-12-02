#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(int argc, char *argv[])
{
    /* modification test */

    /*
    char text[] = "Je vais au macdonald tous les jours";
    Element* a = occurrence(text);
    afficherListe(a);*/
    // printf("okok");

    List_Node* a = add_by_dichotomie_v2("my_file.txt");
    // print_Tab_of_DoubleNode (a, n);
    // printf("hey\n");
    print_Tab_of_DoubleNode(a);
    printf("\n\n");
    // printf("%d", list_size(m));
    // printf("%c",(a->letter));
    // printf("%c",(a->right));
    printf("\n");
    printf("allo");
    printf("\n");
    quick_sorting_caller(a);
    //quick_sorting (a);
    //printf("ok %i", list_size(a));
    printf("euh\n");
    print_Tab_of_DoubleNode (a);


    return 0;
}


