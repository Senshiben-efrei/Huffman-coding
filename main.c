#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(int argc, char *argv[])
{
	/* modification test */

	char text[] = "TASSES";
    Element* a = occurrence(text);
    printf("hey");
    afficherListe(a);
	return 0;
}
