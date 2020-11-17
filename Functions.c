#include "headers.h"


// B : fonction qui affiche le nombre de caractères dans un fichier txt.

int afficher_caracteres (char *nomFichier) {

 int compteur = 0;
 FILE * file;

 // Ouverture du fichier
 if ((file = fopen("nomFichier.txt", "r")) == NULL)
  perror("Erreur à l'ouverture du fichier");

 else {
   // parcours du fichier
   while(fgetc(file) != EOF)
    compteur ++;  // incrémentation du compteur
 }

 printf("Le nombre de caractères du fichier est de : %d\n", compteur);

 // fermeture du fichier
 fclose(file);

 return 0;
}
