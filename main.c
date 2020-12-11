#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "headers.h"


// AVANT DE COMMENCER NE PAS OUBLIER DE SUPP LES FICHIERS DICT.TXT, OUTPUT.TXT, OUTPUT_HUFFMAN.TXT POUR UNE MEILLEURE REALISATION
// DE LA FONCTION DE COMPRESSION.

int main(){

    char* dict = "dict.txt";
    char* output_Huffman = "output_Huffman.txt";
    char* input = "my_file.txt";
    char* output = "output.txt";
    char* decoding = "decoding";


    //trois choix sont proposes pour l'utilisateur

    int choix;
    printf("----- Menu -----\n");
    printf("1 - Compresser un fichier texte \n");
    printf("2 - Compresser un fichier texte de facon optimisee\n");
    printf("3 - Decompresser un fichier texte de facon optimisee\n");

    printf("Votre choix : ");
    scanf("%d", &choix);
    printf("\n");

    while(choix!=1 && choix!=2 && choix!=3)
  {
    printf("Saisie incorrecte, entrer le numero correspondant a votre choix :  ");
    scanf("%d",&choix);
    printf("\n");
  }

  if (choix == 1){
    FILE *input = open_file("my_file.txt", "r");
    FILE *output = open_file("output.txt", "w+");

    FILE *output_Huffman = open_file("output_Huffman.txt", "w+");
    FILE *dict = open_file("dict.txt", "w+");

    file_to_binary_file(input, output, 0);

    Element *occurrences = get_occurrences_by_dichotomy(input, 0);
    print_occurrences(occurrences, 0, 0);
    HuffmanTree *huffman_root = huffman_tree_from_occurrences(occurrences);

    print_tree_2D_wrapper(huffman_root->root_node);
    print_occurrences(huffman_root->root_dict, 1, 0);
    write_huffman_dict(dict, huffman_root->root_dict);

    compress_file(input, output_Huffman, huffman_root, 0);


    fclose(input);
    fclose(output);
    fclose(output_Huffman);
    fclose(dict);

    return EXIT_SUCCESS;

    //marche très bien. RAS.
  }

  else if (choix == 2){
    FILE *input = open_file("my_file.txt", "r");
    FILE *output = open_file("output.txt", "w+");

    FILE *output_huffman = open_file("output_huffman.txt", "w+");
    FILE *dict = open_file("dict.txt", "w+");

    int len;
    Node* tab = add_by_dichotomie_v2(input, &len);
    print_occurrences(tab, 0, 0);
    quick_sorting(tab, 0, len-1);
    print_occurrences(tab, 0, 0);
    Node* Huffman_Tree = huffman_tree_from_occurrences(tab);
    Node_AVL* AVLTree = AVL_dico(Huffman_Tree);
    print_tree_AVL(AVLTree);
    encoding_v2(AVLTree, output_Huffman, input);
    write_AVL_in_dico(AVLTree, dict);
    free_tree_AVL(AVLTree);
    // ne fonctionne pas car erreur quick_sorting bien que les fonctins soient bonnes
  }
  else if (choix == 3){
    optimised_decoding(output_Huffman, dict, decoding);
    printf("\n \nNous avons decompresse le texte dans le fichier decodinc.txt pour voir le resultat.");
    // ne fonctionne pas a cause de decoding qui n'est pas ouvert comme un fichier text surement psq on a pas integrer fwrite :(
    // mais manque de temps pour finir. L'idee serait d'adapter la fonction E qui ecrit le dico  a notre fonction
  }

  return 0;
}



