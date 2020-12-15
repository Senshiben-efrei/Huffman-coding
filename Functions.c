
#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    char letter; //Lettre
    struct Element *next; //Pointeur vers l'élément suivant
    int occ; //Nombre d'occurrence
} Element;

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

struct Node *newNode(char letter, unsigned freq) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

  temp->left = temp->right = NULL;
  temp->letter = letter;
  temp->freq = freq;

  return temp;
}

struct pile *cree_pile(unsigned capacity) {
  struct pile *pile = (struct pile *)malloc(sizeof(struct pile));

  pile->taille = 0;

  pile->capacity = capacity;

  pile->liste = (struct Node **)malloc(pile->capacity * sizeof(struct Node *));
  return pile;
}

void swapNode(struct Node **a, struct Node **b) {
  struct Node *t = *a;
  *a = *b;
  *b = t;
}

void empiler(struct pile *pile, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < pile->taille && pile->liste[left]->freq < pile->liste[smallest]->freq)
    smallest = left;

  if (right < pile->taille && pile->liste[right]->freq < pile->liste[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapNode(&pile->liste[smallest], &pile->liste[idx]);
    empiler(pile, smallest);
  }
}

int last(struct pile *pile) {
  return (pile->taille == 1);
}

struct Node *minimum(struct pile *pile) {
  struct Node *temp = pile->liste[0];
  pile->liste[0] = pile->liste[pile->taille - 1];

  --pile->taille;
  empiler(pile, 0);

  return temp;
}

void insertpile(struct pile *pile, struct Node *pileNode) {
  ++pile->taille;
  int i = pile->taille - 1;

  while (i && pileNode->freq < pile->liste[(i - 1) / 2]->freq) {
    pile->liste[i] = pile->liste[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  pile->liste[i] = pileNode;
}

void buildpile(struct pile *pile) {
  int n = pile->taille - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    empiler(pile, i);
}

int feuille(struct Node *root) {
  return !(root->left) && !(root->right);
}

struct pile *createAndBuildpile(char letter[], int freq[], int taille) {
  struct pile *pile = cree_pile(taille);

  for (int i = 0; i < taille; ++i)
    pile->liste[i] = newNode(letter[i], freq[i]);

  pile->taille = taille;
  buildpile(pile);

  return pile;
}

struct Node *tree(char letter[], int freq[], int taille) {
  struct Node *left, *right, *top;
  struct pile *pile = createAndBuildpile(letter, freq, taille);

  while (!last(pile)) {
    left = minimum(pile);
    right = minimum(pile);

    top = newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    insertpile(pile, top);
  }
  return minimum(pile);
}

void printArr(int code[], int j) 
{ 
  int i; 
  for (i = 0; i < j; ++i) 
    printf("%d", code[i]); 

  printf("\n"); 
} 

void writeArr(int code[], int j) 
{ 
  int i; 
  FILE *fptr;
  fptr = fopen("dico.txt", "a");

  for (i = 0; i < j; ++i) 
    fprintf(fptr, "%d", code[i]);
    fprintf(fptr,"\n"); 

  fclose(fptr);

} 


void printCodes(struct Node* root, int code[], int i)
{ 

  if (root->left) { 

    code[i] = 0; 
    printCodes(root->left, code, i + 1); 
  } 

  if (root->right) { 

    code[i] = 1; 
    printCodes(root->right, code, i + 1); 
  } 

  if (feuille(root)) { 

    printf("%c: ", root->letter); 
    printArr(code, i); 

    FILE *fptr;
    fptr = fopen("dico.txt", "a");
    fprintf(fptr,"%c: ", root->letter); 
    fclose(fptr);

    writeArr(code, i); 
  } 
} 

Element* new_letter(char letter,int occ)
{
    Element* new = malloc(sizeof(Element));
    new->next = NULL;
    new->letter = letter;
    new->occ = occ;
    return new;
}


void dictionairify(Element* list_occ)
{
  char letters[300];
  int freq[300];
  int liste_to_charnint(Element* maListe)
  {
    Element* temp;
    temp = maListe;
    int i =0;
    while (temp != NULL)
    {
      letters[i]=temp->letter;
      freq[i]=temp->occ;
      temp = temp->next;
      i++;
    }
    return i;
  }
  int taille = liste_to_charnint(list_occ);
  //printf("%d\n", taille);
  tree(letters, freq, taille);
  int code[10000];
  int i = 0;
  struct Node* root = tree(letters, freq, taille); 

  fclose(fopen("dico.txt", "w"));

  printCodes(root, code, i);
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    char letter; //Lettre
    struct Element *next; //Pointeur vers l'élément suivant
    int occ; //Nombre d'occurrence
} Element;

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

struct Node *newNode(char letter, unsigned freq) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

  temp->left = temp->right = NULL;
  temp->letter = letter;
  temp->freq = freq;

  return temp;
}

struct pile *cree_pile(unsigned capacity) {
  struct pile *pile = (struct pile *)malloc(sizeof(struct pile));

  pile->taille = 0;

  pile->capacity = capacity;

  pile->liste = (struct Node **)malloc(pile->capacity * sizeof(struct Node *));
  return pile;
}

void swapNode(struct Node **a, struct Node **b) {
  struct Node *t = *a;
  *a = *b;
  *b = t;
}

void empiler(struct pile *pile, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < pile->taille && pile->liste[left]->freq < pile->liste[smallest]->freq)
    smallest = left;

  if (right < pile->taille && pile->liste[right]->freq < pile->liste[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapNode(&pile->liste[smallest], &pile->liste[idx]);
    empiler(pile, smallest);
  }
}

int last(struct pile *pile) {
  return (pile->taille == 1);
}

struct Node *minimum(struct pile *pile) {
  struct Node *temp = pile->liste[0];
  pile->liste[0] = pile->liste[pile->taille - 1];

  --pile->taille;
  empiler(pile, 0);

  return temp;
}

void insertpile(struct pile *pile, struct Node *pileNode) {
  ++pile->taille;
  int i = pile->taille - 1;

  while (i && pileNode->freq < pile->liste[(i - 1) / 2]->freq) {
    pile->liste[i] = pile->liste[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  pile->liste[i] = pileNode;
}

void buildpile(struct pile *pile) {
  int n = pile->taille - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    empiler(pile, i);
}

int feuille(struct Node *root) {
  return !(root->left) && !(root->right);
}

struct pile *createAndBuildpile(char letter[], int freq[], int taille) {
  struct pile *pile = cree_pile(taille);

  for (int i = 0; i < taille; ++i)
    pile->liste[i] = newNode(letter[i], freq[i]);

  pile->taille = taille;
  buildpile(pile);

  return pile;
}

struct Node *tree(char letter[], int freq[], int taille) {
  struct Node *left, *right, *top;
  struct pile *pile = createAndBuildpile(letter, freq, taille);

  while (!last(pile)) {
    left = minimum(pile);
    right = minimum(pile);

    top = newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    insertpile(pile, top);
  }
  return minimum(pile);
}

void printArr(int code[], int j) 
{ 
  int i; 
  for (i = 0; i < j; ++i) 
    printf("%d", code[i]); 

  printf("\n"); 
} 

void writeArr(int code[], int j) 
{ 
  int i; 
  FILE *fptr;
  fptr = fopen("dico.txt", "a");

  for (i = 0; i < j; ++i) 
    fprintf(fptr, "%d", code[i]);
    fprintf(fptr,"\n"); 

  fclose(fptr);

} 


void printCodes(struct Node* root, int code[], int i)
{ 

  if (root->left) { 

    code[i] = 0; 
    printCodes(root->left, code, i + 1); 
  } 

  if (root->right) { 

    code[i] = 1; 
    printCodes(root->right, code, i + 1); 
  } 

  if (feuille(root)) { 

    printf("%c: ", root->letter); 
    printArr(code, i); 

    FILE *fptr;
    fptr = fopen("dico.txt", "a");
    fprintf(fptr,"%c: ", root->letter); 
    fclose(fptr);

    writeArr(code, i); 
  } 
} 

Element* new_letter(char letter,int occ)
{
    Element* new = malloc(sizeof(Element));
    new->next = NULL;
    new->letter = letter;
    new->occ = occ;
    return new;
}


void dictionairify(Element* list_occ)
{
  char letters[300];
  int freq[300];
  int liste_to_charnint(Element* maListe)
  {
    Element* temp;
    temp = maListe;
    int i =0;
    while (temp != NULL)
    {
      letters[i]=temp->letter;
      freq[i]=temp->occ;
      temp = temp->next;
      i++;
    }
    return i;
  }
  int taille = liste_to_charnint(list_occ);
  //printf("%d\n", taille);
  tree(letters, freq, taille);
  int code[10000];
  int i = 0;
  struct Node* root = tree(letters, freq, taille); 

  fclose(fopen("dico.txt", "w"));

  printCodes(root, code, i);
}