#include <stdio.h>
#include <string.h>
#include "Header.h"

void BinaryTranslator(FILE** ftpr, char *Translation)
{
    char Traduction[10000];
    char Temp[9];
    //It will make  sure the fptr gets read first,
    if ((*ftpr = fopen("Texte.txt", "r")) == NULL)
    {
        printf("Erreur, le fichier n'est pas disponible.");
        return 0;
    }
    //This scans the file and store everything in Translation
    fscanf(*ftpr, "%[^\n]", Translation);
    fclose(*ftpr);
    while (*Translation)
    {
        if(isalpha(*Translation))
        {
            strcat(Traduction, "0");
        }
        else if(isdigit(*Translation))
        {
            strcat(Traduction, "00");
        }
        itoa(*Translation, Temp, 2);
        strcat(Traduction, Temp);
        strcat(Traduction, "\n");
        ++Translation;
    }
    *ftpr = fopen("Binary.txt", "w");
    fprintf(*ftpr, Traduction);
    fclose(*ftpr);
}

/* BinaryTranslator will transfer CHAR characters to BINARY.
 * Temp will serve as a temporary CHAR to translate and store the new binary output.
 * Translation will store the new translation in BINARY.
 */

void afficher_caracteres(FILE** ftpr, char *Translation)
{
    int counter = 0;
    if ((*ftpr = fopen("Texte.txt", "r")) == NULL)
    {
        printf("Erreur, le fichier n'est pas disponible.");
        return 0;
    }
    fscanf(*ftpr, "%[^\n]", Translation);
    fclose(*ftpr);
    while (*Translation)
    {
        counter = counter + 1;
        ++Translation;
    }
    printf("Le nombre de caracteres dans Texte.txt est: %d", counter);
}

/* Afficher_caracteres will count the characters from the provided from the Texte.txt
 */

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

void printArr(int code[], int j, FILE **ftpr, struct Node* root) {
    int i;
    char Temp[1000];
    for (i = 0; i < j; i++)
    {
        Temp[i] = '0' + code[i];
        printf("i:%d \n", i);
        printf("Code:%d \n", code[i]);
        printf("Temp:%c \n", Temp[i]);
    }
    Temp[i] = '\0';
    printf("Voici le résultat final: %s\n", Temp);
    *ftpr = fopen("Dictionnary.txt", "a");
    fprintf(*ftpr, "%c ", root->letter);
    fprintf(*ftpr, Temp);
    fprintf(*ftpr, "\n");
    fclose(*ftpr);
}

void printCodes(struct Node* root, int code[], int i, FILE **ftpr) {

    if (root->left) {
        code[i] = 0;
        printCodes(root->left, code, i + 1, &ftpr);
    }

    if (root->right) {
        code[i] = 1;
        printCodes(root->right, code, i + 1, &ftpr);
    }

    if (feuille(root)) {
        printf("%c: ", root->letter);
        printArr(code, i, &ftpr, root);
    }
}

void crea_liste ()
{
    FILE* fichier = NULL;
    FILE* fptr = NULL;
    FILE* Texte = NULL;
    char code[8] = "";
    char CopieTexte[1000] = "";
    char Buffer[1000] = "";
    fichier = fopen("Dictionnary.txt", "r");
    fptr = fopen("SuiteBinaire.txt", "w");
    Texte = fopen("Texte.txt", "r");
    while (fgets(CopieTexte, 1000, Texte) != NULL)
    {
        fscanf(Texte, "%[^\n]", CopieTexte);
        for (int j = 0; j <= strlen(CopieTexte); j++)
        {
            printf("J = %d\n", j);
            printf("current letter : %c\n", CopieTexte[j]);
            fseek(fichier, 0, SEEK_SET);
            while (fgets(Buffer, 1000, fichier) != NULL)
            {
                printf("%s\n", Buffer);
                fscanf(fichier, "%c", &code[0]);
                printf("Code = %c\n", code[0]);
                if (code[0] == CopieTexte[j])
                {
                    printf("Inside If loop\n");
                    fscanf(fichier, "%[^\n]", &code);
                    printf("memmove\n");
                    memmove(code, code+1, strlen(code));
                    printf("prints\n");
                    fprintf(fptr, "%s", code);
                    fprintf(fptr, "\n");
                    free(code);
                    char code[8] = "";
                }
            }
        }
    }
    fclose(fichier);
    fclose(fptr);
    fclose(Texte);
}
