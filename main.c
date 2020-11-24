#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#define TAILLE 5


// B : fonction qui affiche le nombre de caracteres dans un fichier txt.

int afficher_caracteres (char *nomFichier)
{

    int compteur = 0;
    FILE * file;

// Ouverture du fichier
    if ((file = fopen("nomFichier.txt", "r")) == NULL)
        perror("Erreur a l'ouverture du fichier");

    else
    {
        // parcours du fichier
        while(fgetc(file) != EOF)
            compteur ++;  // incrémentation du compteur
    }

    printf("Le nombre de caracteres du fichier est de : %d\n", compteur);

// fermeture du fichier
    fclose(file);

    return 0;
}


// C : fonction qui renvoie une liste contenant chaque caractere present dans le texte,
//     ainsi que le nombre d’occurrences de ce caractere.

int check_letter(Element* list, char letter)
{
    int here = -1, compt = 0;    //if here return the position, else -1
    if (list != NULL)
    {
        Element* temp = list;
        while (temp != NULL)
        {
            if (temp->letter == letter)
            {
                here = compt;
            }
            temp = temp->next;
            compt ++;
        }
    }
    return here;
}

Element* new_letter(char letter)
{
    Element* new = malloc(sizeof(Element));
    new->next = NULL;
    new->letter = letter;
    new->occ = 1;
    return new;
}
Element* occurrence (char* text)        // To pass an entire array to a function, only the name of the array is passed as an argument
{
    if(strlen(text)>0)
    {
        Element* list_occ = new_letter(text[0]);
        Element* temp = list_occ;
        for(int i=1; i<=strlen(text)-1; i++)
        {
            int here = check_letter(list_occ, text[i]);
            if(here == -1)
            {
                temp->next = new_letter(text[i]);
                temp = temp->next;
            }
            else
            {
                Element* temp = list_occ;
                while((temp != NULL) && (here>0))
                {
                    temp = temp->next;
                    here --;
                }
                temp->occ ++;
            }
        }
        return list_occ;
    }
    return NULL;
}

int main()
{
  int tab[5] = {5,5,6,9,1};
  int i, j, tmp, index;

   //afficher les éléments du tableau
   for (i=0; i < TAILLE; ++i)
   {
      printf("%3d", tab[i]);
   }

  for (i=0; i < (TAILLE-1); i++)
  {
    index = i;

    for (j=i + 1; j < TAILLE; j++)
    {
      if (tab[index] > tab[j])
        index = j;
    }
    if (index != i)
    {
      tmp = tab[i];
      tab[i] = tab[index];
      tab[index] = tmp;
    }
  }

  printf("\n******** tableau triee par ordre croissant ********\n");

  for (i=0; i < TAILLE; i++)
     printf("%3d", tab[i]);

  return 0;
}

