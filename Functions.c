#include <stdio.h>teams
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

/*BinaryTranslator will transfer CHAR characters to BINARY.
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

/*Afficher_caracteres will count the characters from the provided from the
