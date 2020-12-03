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

    Element* a = add_by_dichotomie_v2("my_file.txt");
    // print_Tab_of_DoubleNode (a, n);
    // printf("hey\n");
    print_occurences(a);
    Node* root_node = Huffman_Tree(a);
    print2D(root_node);
    printf("2");
    return 0;
}


