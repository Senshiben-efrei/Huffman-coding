#include "headers.h"


// B : fonction qui affiche le nombre de caract�res dans un fichier txt.

int afficher_caracteres (char *nomFichier) {

 int compteur = 0;
 FILE * file;

 // Ouverture du fichier
 if ((file = fopen("nomFichier.txt", "r")) == NULL)
  perror("Erreur � l'ouverture du fichier");

 else {
   // parcours du fichier
   while(fgetc(file) != EOF)
    compteur ++;  // incr�mentation du compteur
 }

 printf("Le nombre de caract�res du fichier est de : %d\n", compteur);

 // fermeture du fichier
 fclose(file);

 return 0;
}
