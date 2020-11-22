#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
    FILE *ftpr;
    char Translation[10000];
    BinaryTranslator(&ftpr, Translation);
    afficher_caracteres(&ftpr, Translation);
    return 0;
}
