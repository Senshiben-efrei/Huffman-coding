#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <string.h>

typedef struct Element
{
    char letter; //Lettre
    struct Element *next; //Pointeur vers l'élément suivant
    unsigned occ; //Nombre d'occurrence
} Element;

typedef struct Node
{
    char letter;
    unsigned occ;
    struct Node *left, *right;
} Node;

typedef struct List_Node
{
    Node** tab;
    int size_tab;
} List_Node;


void afficherListe(Element *list);

void afficher_caracteres (FILE** ftpr, char *Translation);

int check_letter(Element* list, char letter);
Element* new_letter(char letter);
Element* occurrence (char* text);

int get_length(Element* root);
Element* get_element(Element* root, int index);

List_Node* add_by_dichotomie_v2 (char* my_file);
void print_Tab_of_DoubleNode (List_Node* list);
void swap(Node* a, Node* b);

int	list_size(Node** lst);
void quick_sorting (List_Node* list, int first, int last);
void quick_sorting_caller(List_Node* list);


#endif // HEADERS_H_INCLUDED
