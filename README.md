# Huffman-coding

	L’objectif de ce projet est d’implémenter un algorithme de compression. Cela signifie que l’on cherche à réduire la place que prend une information, sans perte de données.
Nous travaillerons ici sur des fichiers textes.
Le codage de Huffman repose sur la traduction en un code court d’un caractère, en fonction de sa fréquence d’apparition. Plus un caractère apparaît souvent dans le texte à coder, plus sa traduction sera courte.
Vous savez peut-être qu’un caractère est codé sur un octet. Cela signifie que pour chaque caractère d’un texte, il nous faut 8 bits en mémoire. Un texte de 100 caractères va donc prendre 800 bits en mémoire. Comment faire alors pour réduire ce chiffre ?

Organisation de functions.c :

Partie 1 : De la lettre au bit

A) ⭐⭐: Écrire une fonction qui lit un texte dans un fichier, et qui le traduit en son équivalent 0 et 1 dans un autre fichier.
B) ⭐: Écrire une fonction qui affiche le nombre de caractères dans un fichier txt.


Partie 2 : Le code de Huffman version naïve

C) ⭐⭐: Ecrire une fonction qui renvoie une liste contenant chaque caractère présent dans le texte, ainsi que le nombre d’occurrences de ce caractère.
D) ⭐⭐⭐: Ecrire une fonction qui renvoie un arbre de Huffman, à partir d’une liste d’occurrences.
E) ⭐⭐: Écrire une fonction qui stocke dans un fichier txt le dictionnaire issu de l’arbre de Huffman.
F) ⭐⭐: Écrire une fonction qui traduit un texte en une suite binaire basée sur un dictionnaire de Huffman.
G) ⭐: Écrire une fonction qui compresse un fichier texte. Le fichier d’entrée ne sera pas modifié, un autre fichier, contenant le texte compressé sera créé.
H) ⭐⭐: Écrire une fonction qui décompresse un fichier texte à partir d’un arbre de Huffman. Le fichier d’entrée ne sera pas modifié, un autre fichier, contenant le texte décompressé sera créé.


Partie 3 : Optimisation

I) ⭐⭐: Écrire une fonction qui, par recherche dichotomique, ajoute à un tableau de nœuds une occurrence quand le caractère a déjà été trouvé, ou qui ajoute le nœud du caractère sinon.
J) ⭐⭐: Écrire une fonction qui trie un tableau de noeuds en fonction des occurrences.
K) ⭐⭐⭐: Écrire une fonction qui, en utilisant deux files, crée l’arbre de Huffman à partir d’un tableau de noeuds trié par occurrences.
L) ⭐⭐⭐⭐: Écrire une fonction qui organise les nœuds dans un AVL en fonction de l’ordre des caractères présents.
M) ⭐⭐: Écrire une fonction qui compresse un fichier texte de façon optimisée. Le fichier d’entrée ne sera pas modifié, un autre fichier, contenant le texte compressé sera créé. 
N) ⭐⭐: Écrire une fonction qui décompresse un fichier texte à partir d’un fichier dictionnaire d’Huffman. Le fichier texte d’entrée ne sera pas modifié, un autre fichier, contenant le texte décompressé sera créé.





