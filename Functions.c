#include <stdio.h>
#include <string.h>
#include "Header.h"

void BinaryTranslator(FILE** ftpr, char *Translation)
{
    char Traduction[10000];
    char Temp[9];
    //It will make sure the fptr gets read first,
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

struct Node *newNode(char letter, unsigned freq)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

    temp->left = temp->right = NULL;
    temp->letter = letter;
    temp->freq = freq;

    return temp;
}

struct pile *cree_pile(unsigned capacity)
{
    struct pile *pile = (struct pile *)malloc(sizeof(struct pile));

    pile->taille = 0;

    pile->capacity = capacity;

    pile->liste = (struct Node **)malloc(pile->capacity * sizeof(struct Node *));
    return pile;
}

void swapNode(struct Node **a, struct Node **b)
{
    struct Node *t = *a;
    *a = *b;
    *b = t;
}

void empiler(struct pile *pile, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pile->taille && pile->liste[left]->freq < pile->liste[smallest]->freq)
        smallest = left;

    if (right < pile->taille && pile->liste[right]->freq < pile->liste[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapNode(&pile->liste[smallest], &pile->liste[idx]);
        empiler(pile, smallest);
    }
}

int last(struct pile *pile)
{
    return (pile->taille == 1);
}

struct Node *minimum(struct pile *pile)
{
    struct Node *temp = pile->liste[0];
    pile->liste[0] = pile->liste[pile->taille - 1];

    --pile->taille;
    empiler(pile, 0);

    return temp;
}

void insertpile(struct pile *pile, struct Node *pileNode)
{
    ++pile->taille;
    int i = pile->taille - 1;

    while (i && pileNode->freq < pile->liste[(i - 1) / 2]->freq)
    {
        pile->liste[i] = pile->liste[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pile->liste[i] = pileNode;
}

void buildpile(struct pile *pile)
{
    int n = pile->taille - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        empiler(pile, i);
}

int feuille(struct Node *root)
{
    return !(root->left) && !(root->right);
}

struct pile *createAndBuildpile(char letter[], int freq[], int taille)
{
    struct pile *pile = cree_pile(taille);

    for (int i = 0; i < taille; ++i)
        pile->liste[i] = newNode(letter[i], freq[i]);

    pile->taille = taille;
    buildpile(pile);

    return pile;
}

struct Node *tree(char letter[], int freq[], int taille)
{
    struct Node *left, *right, *top;
    struct pile *pile = createAndBuildpile(letter, freq, taille);

    while (!last(pile))
    {
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
    fptr = fopen("dictionary.txt", "a");

    for (i = 0; i < j; ++i)
    {
        fprintf(fptr, "%d", code[i]); //This line takes the binary code written in code[], build along the passages in the recursive function from where it came from.
    }
    fprintf(fptr,"\n");
    fclose(fptr);

}
/* This function comes directly from PrintCodes, a recursive function which builds code[].
 * Code[] is then unveiled and unraveled in a loop, which is then printed into the Dictionary file.
 * Formatting is realized by putting the letter, then a space and finally, the code.
 */


void printCodes(struct Node* root, int code[], int i)
{

    if (root->left)
    {

        code[i] = 0;
        printCodes(root->left, code, i + 1); //This line and the one above add a '0' when the program takes the left branch of the tree.
    }

    if (root->right)
    {

        code[i] = 1;
        printCodes(root->right, code, i + 1); //This line and the one above add a '1' when the program takes the left branch of the tree.
    }

    if (feuille(root))
    {

        printf("%c: ", root->letter);
        printArr(code, i);

        FILE *fptr;
        fptr = fopen("dictionary.txt", "a");
        fprintf(fptr,"%c: ", root->letter); //This line is used to print the corresponding letter to the binary code unveiled.
        fclose(fptr);
        writeArr(code, i); //Thanks to the code build along the recursive path, the code will always match the way took to reach the corresponding letter.
    }
}

/* PrintCodes is a recursive function that will build code[] and store the path taken inside it.
 * If the program takes a turn to the right, a '1' will be added.
 * If the program takes a turn to the left, a '0' will be added.
 * Once a letter has been reached, it will get added into the Dictionary, and code[] will be sent in writeArr to get unraveled and printed onto the Dictionary.
 */


void crea_liste()
{
    FILE* fichier = NULL;
    FILE* fptr = NULL;
    FILE* Texte = NULL;
    char code[8] = "";
    char CopieTexte[1000] = "";
    char Buffer[1000] = "";
    fichier = fopen("dictionary.txt", "r");
    fptr = fopen("SuiteBinaire.txt", "w");
    Texte = fopen("Texte.txt", "r");
    while (fgets(CopieTexte, 1000, Texte) != NULL) //This line will make sure the entire Text file gets read, including \n.
    {
        fscanf(Texte, "%[^\n]", CopieTexte); //This line will copy the current string to a CHAR, making it easier for the program to read.
        for (int j = 0; j <= strlen(CopieTexte); j++)
        {
            printf("J = %d\n", j);
            printf("current letter : %c\n", CopieTexte[j]);
            fseek(fichier, 0, SEEK_SET); //This line makes sure the pointer to the dictionary file gets reset to the start of the file.
            while (fgets(Buffer, 1000, fichier) != NULL) //This line will make sure the entire dictionary file gets read, including \n.
            {
                printf("%s\n", Buffer);
                fscanf(fichier, "%c", &code[0]); //This line stores the first character of the dictionary, allowing to look for similarities in the Text file.
                printf("Code = %c\n", code[0]);
                if (code[0] == CopieTexte[j]) //Here, we will see if the character on the dictionary file matches the current letter in the Text file.
                {
                    printf("Inside If loop\n");
                    fscanf(fichier, "%[^\n]", &code); //Let us copy the entire dictionary string.
                    printf("memmove\n");
                    memmove(code, code+1, strlen(code)); //Then, move the pointer two strings on the right, making sure we only copy the code and not the letters.
                    printf("prints\n");
                    fprintf(fptr, "%s", code);
                    fprintf(fptr, "\n");
                    free(code); //This line and the following resets the code variable, to reset the pointer who was now making code having only 6 spaces.
                    char code[8] = "";
                }
            }
        }
    }
    fclose(fichier);
    fclose(fptr);
    fclose(Texte);
}

/* crea_liste opens the main Text file, and translates it into another binary file.
 * This binary file will be build according to the dictionary previously created thanks to the Huffman Tree created before.
 */
