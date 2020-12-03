#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <string.h>

typedef struct Node
{
    char letter;
    int size;
    struct Node *left, *right;
} Node;

typedef struct Element
{
    char letter; //Lettre
    struct Element *next; //Pointeur vers l'élément suivant
    int occ; //Nombre d'occurrence
    Node* node;
} Element;



void afficherListe(Element *list);

void afficher_caracteres (FILE** ftpr, char *Translation);

int check_letter(Element* list, char letter);
Element* new_letter(char letter);
Element* occurrence (char* text);

void insert_node_element(Element* root, Element* to_insert);
Node* Huffman_Tree(Element* list);
void print2DUtil(struct Node *root, int space);
void print2D(struct Node *root);

Element* get_element(Element* root, int index);
int	list_size(Element* root);
Element* add_by_dichotomie_v2 (char* my_file);
void print_occurences(Element* root);
void swap(Element* a, Element* b);


void quick_sorting (Element* root, int first, int last);
void quick_sorting_caller(Element* root);


#endif // HEADERS_H_INCLUDED
