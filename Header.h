#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <string.h>

struct Node {
  char letter;
  unsigned freq;
  struct Node *left, *right;
};

struct pile {
  unsigned taille;
  unsigned capacity;
  struct Node **liste;
};

void BinaryTranslator(FILE** ftpr, char *Traduction);
void afficher_caracteres(FILE** ftpr, char *Translation);
struct Node *newNode(char letter, unsigned freq);
struct pile *cree_pile(unsigned capacity);
void swapNode(struct Node **a, struct Node **b);
void empiler(struct pile *pile, int idx);
int last(struct pile *pile);
struct Node *minimum(struct pile *pile);
void insertpile(struct pile *pile, struct Node *pileNode);
void buildpile(struct pile *pile);
int feuille(struct Node *root);
struct pile *createAndBuildpile(char letter[], int freq[], int taille);
struct Node *tree(char letter[], int freq[], int taille);
void printArr(int code[], int j, FILE **ftpr);
void printCodes(struct Node* root, int code[], int i, FILE **ftpr);

#endif // HEADER_H_INCLUDED
