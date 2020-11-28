#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int main()
{
    FILE *ftpr;
    char Translation[10000];
    char CustomBinary[] = "";
    BinaryTranslator(&ftpr, Translation);
    afficher_caracteres(&ftpr, Translation);
    char letters[] = {'A', 'B', 'C', 'D', ' ', 'f', 'n', 't', 'r', ','};
    int freq[] = {5, 1, 6, 7, 1, 6, 7, 2, 12, 2};
    int taille = sizeof(letters) / sizeof(letters[0]);
    tree(letters, freq, taille);
    int code[10000];
    int i = 0;
    struct Node* root = tree(letters, freq, taille);
    ftpr = fopen("dictionary.txt", "w");
    fprintf(ftpr, "\n");
    fclose(ftpr);
    printCodes(root, code, i);
    crea_liste();
    return 0;
}
