#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <string.h>

typedef struct Element{
    char letter; //Lettre
    struct Element *next; //Pointeur vers l'élément suivant
    int occ; //Nombre d'occurrence
} Element;



void afficherListe(Element *list);

int afficher_caracteres (char *nomFichier);

int check_letter(Element* list, char letter);
Element* new_letter(char letter);
Element* occurrence (char* text);


#endif // HEADERS_H_INCLUDED
