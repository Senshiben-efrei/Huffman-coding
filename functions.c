#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "headers.h"

char *NaN = "NaN";
char *_NULL = "NULL";
char *NEWLINE = "LF/NL";
char *TAB = "TAB";
char *SPACE = "SPACE";
char *DEL = "DEL";
char *ALT = "ALT";
char *SPECIAL = "CHR";



// Fonctions utiles

char fgetc_ascii(FILE *file)
{
    char chr = fgetc(file);
    int curr_char = (int)chr;
    if (curr_char < -1 || curr_char > 255)
    {
        curr_char = 0;
    }
    chr = (char)curr_char;
    return chr;
}

char *display_char(char chr)
{
    int c = (int)chr;
    char *new_chr = NULL;

    switch (c)
    {
    case 0:
        new_chr = _NULL;
        break;

    case 10:
        new_chr = NEWLINE;
        break;

    case 9:
        new_chr = TAB;
        break;

    case 32:
        new_chr = SPACE;
        break;

    case 127:
        new_chr = DEL;
        break;

    case 255:
        new_chr = ALT;
        break;

    default:
        if (c < 0 || c > 255)
        {
            new_chr = NaN;
        }
        else if (c < 32)
        {
            new_chr = malloc(strlen(SPECIAL) + 2);
            sprintf(new_chr, "%s%02d", SPECIAL, c);
        }
        else
        {
            new_chr = malloc(2*sizeof(char));
            new_chr[0] = (char)c;
            new_chr[1] = '\0';
        }
    }

    return new_chr;
}


Element *get_element(Element *root, int index)
{
    if (index >= 0)
    {
        Element *curr = root;
        for (int i = 0; i < index; i++)
        {
            if (curr->next != NULL)
            {
                curr = curr->next;
            }
            else
            {
                exit(EXIT_FAILURE);
            }
        }
        return curr;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

char get_char_from_display_char(char *display_chr)
{
    if (strlen(display_chr) == 1)
    {
        return *display_chr;
    }
    else if (strlen(display_chr) == 0)
    {
        return -1;
    }
    else
    {
        if (strcmp(display_chr, NaN)  == 0)
        {
            return -1;
        }
        else if (strcmp(display_chr, _NULL) == 0)
        {
            return 0;
        }
        else if (strcmp(display_chr, NEWLINE) == 0)
        {
            return 10;
        }
        else if (strcmp(display_chr, TAB) == 0)
        {
            return 9;
        }
        else if (strcmp(display_chr, SPACE) == 0)
        {
            return 32;
        }
        else if (strcmp(display_chr, DEL) == 0)
        {
            return 127;
        }
        else if (strcmp(display_chr, ALT) == 0)
        {
            return 255;
        }
        else if (strlen(display_chr) == strlen(SPECIAL) + 2 && strncmp(SPECIAL, display_chr, strlen(SPECIAL)) == 0)
        {
            int chr;
            sscanf(display_chr, "%s%02d", ((char*)0), &chr);
            return ((char)chr);
        }
    }
}

void print_node(Node *node)
{
    Node *left = node->left;
    Node *right = node->right;

    if (left != NULL)
    {
        if (left->letter == -1)
        {
            printf("(%d) <- ", left->size);
        }
        else
        {
            printf("(%s, %d) <- ", display_char(left->letter), left->size);
        }
    }
    else
    {
        printf("  NULL  <- ");
    }

    if (node->letter == -1)
    {
        printf("(%d)", node->size);
    }
    else
    {
        printf("(%s, %d)", display_char(node->letter), node->size);
    }

    if (right != NULL)
    {
        if (right->letter == -1)
        {
            printf(" -> (%d)", right->size);
        }
        else
        {
            printf(" -> (%s, %d)", display_char(right->letter), left->size);
        }
    }
    else
    {
        printf(" ->  EOF");
    }
}

void print_element(Element *element, int display_code, int elem_or_node)
{
    if (elem_or_node)
    {
        if (display_code)
        {
            printf("-> %s: %d (%s)\n", display_char(element->node->letter), element->node->size, element->node->code);
        }
        else
        {
            printf("-> %s: %d\n", display_char(element->node->letter), element->node->size);
        }
    }
    else
    {
        if (display_code)
        {
            printf("-> %s: %d (%s)\n", display_char(element->letter), element->occ, element->node->code);
        }
        else
        {
            printf("-> %s: %d\n", display_char(element->letter), element->occ);
        }
    }
}

void print_occurrences(Element *root, int display_code, int elem_or_node)
{
    if (root == NULL)
    {
        printf("Error: The linked list of occurrences is empty.");
        return;
    }
    printf("\n");
    Element *curr = root;
    do
    {
        print_element(curr, display_code, elem_or_node);
        curr = curr->next;
    }
    while (curr != NULL);

    printf("-> EOF\n");
}



// A :  fonction qui lit un texte dans un fichier, et qui le traduit en son équivalent 0 et 1 dans un autre fichier


void trad_fic(FILE * f,int * nbre_cara, Element_node ** add_l)
{
    FILE* trad = NULL;

    trad = fopen("traduction.txt","r+");
    char * binaire = malloc(sizeof(char)*9);
    char actuel;

    if(f!=NULL)
    {
        actuel = fgetc(f);
        while(actuel!=EOF)
            //do
        {

            character_number(nbre_cara);
            //    actuel = fgetc(f);
            if (actuel!=-1 && actuel!=10)
            {
                add_elem(actuel,add_l);
                binaire = hexa_to_binary(actuel);
                fputs(binaire,trad);
            }
            actuel = fgetc(f);
        }//while(actuel!=EOF);
        afficher_liste((*add_l));
        (*nbre_cara)--; //psq do whhile donc un caractere en plus
    }
    fclose(trad);

}

char * hexa_to_binary(char actuel)
{
    int i;
    int j;

    char * octet = malloc(sizeof(char)*9);

    for(i=0 ; i<8 ; i++)
    {
        int p=1;

        for(j=7-i ; j>0 ; j--)
        {
            p=2*p;
        }

        if(actuel-p>=0)
        {
            actuel = actuel -p;
            octet[i]='1';
        }
        else
        {
            octet[i]='0';
        }

    }
    octet[8]='\0';
    return octet;
}


void character_number(int * nbre_cara)
{
    (*nbre_cara)++;
}


Element_node* create_elem(char cara)
{
    Element_node* nouv_el = (Element_node*)malloc(sizeof(Element_node));
    nouv_el->data->size = 1;
    nouv_el->data->letter = cara;
    nouv_el->data->left = NULL;
    nouv_el->data->right = NULL;
    nouv_el->next = NULL;
    return (nouv_el);
}

void add_elem(char cara ,Element_node** l)
{

    if((*l)==NULL)
    {
      Element_node * nouv_el = malloc(sizeof(Element_node));
      nouv_el->data = malloc(sizeof(Node));
      nouv_el->data->left=NULL;
      nouv_el->data->right=NULL;

      (nouv_el ->data->size)=1;
      nouv_el->data->letter= cara;

      nouv_el->next = NULL;

     (*l)=nouv_el;

    }
    else
    {
        Element_node * temp=(*l);


        while((temp->next!=NULL)&&(temp->data->letter != cara))
        {
            temp=temp->next;
        }
        if (temp->data->letter ==cara)
        {
            temp->data->size ++;
        }
        else
        {
            Element_node* nouv_el = malloc(sizeof(Element_node));
            nouv_el ->data = malloc(sizeof(Node));
            nouv_el->data->left=NULL;
            nouv_el->data->right=NULL;

            nouv_el ->next = temp->next;
            nouv_el->data->letter = cara;
            nouv_el->data->size = 1;
            temp->next = nouv_el;
        }
    }

}

void afficher_liste(Element_node* maListe)
{
	Element_node* temp;
	temp = maListe;
	while (temp != NULL)
    {
		printf("%c-> %d\n", temp->data->letter,temp->data->size);
		temp = temp->next;
	}
    printf("NULL\n");
}



// B : fonction qui affiche le nombre de caractères dans un fichier txt

// Afficher_caracteres will count the characters from the provided from the Texte.txt

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





// C : Fonction qui renvoie une liste contenant chaque caractere present dans le texte,
//     ainsi que le nombre d’occurrences de ce caractere.

int idx_letter(Element *root, char letter)
{
    if (root != NULL)
    {
        Element *curr = root;
        for (int i = 0; curr != NULL; i++)
        {
            if (curr->letter == letter)
            {
                return i;
            }
            curr = curr->next;
        }
    }
    return -1;
}

Node *new_node(int letter, int occ, Node *left, Node *right, Element *element_ref)
{
    Node *node = malloc(sizeof(Node));
    node->letter = letter;
    node->size = occ;
    node->left = left;
    node->right = right;
    node->code = "";
    node->element_ref = element_ref;
    return node;
}

Element *new_element(int letter)
{
    Element *new = malloc(sizeof(Element));
    new->next = NULL;
    new->letter = letter;
    new->occ = 1;
    new->node = new_node(-1, -1, NULL, NULL, new);

    return new;
}

// To pass an entire array to a function, only the name of the array is passed as an argument
Element *get_occurrences(char *text)
{
    int text_length = strlen(text), idx_occ;
    if (text_length > 0)
    {
        Element *root = new_element(text[0]);
        Element *curr = root;
        for (int i = 1; i <= text_length - 1; i++)
        {
            idx_occ = idx_letter(root, text[i]);
            if (idx_occ == -1)
            {
                curr->next = new_element(text[i]);
                curr = curr->next;
            }
            else
            {
                get_element(root, idx_occ)->occ++;
            }
        }
        return root;
    }
    return NULL;
}




// D : Fonction qui renvoie un arbre de Huffman, à partir d’une liste d’occurrences

char *insert_char_in_front(char c, char *curr_string)
{
    int new_len = strlen(curr_string) + 1;
    char *new_string = malloc(new_len * sizeof(char));
    new_string[0] = c;

    for (int i = 1; i <= new_len; i++)
    {
        if (i == new_len)
        {
            new_string[i] = '\0';
        }
        else
        {
            new_string[i] = curr_string[i - 1];
        }
    }
    return new_string;
}

void swap(Element *a, Element *b)
{
    Element *temp = malloc(sizeof(Element));

    temp->letter = a->letter;
    temp->occ = a->occ;
    temp->node = a->node;

    a->letter = b->letter;
    a->occ = b->occ;
    a->node = b->node;
    a->node->element_ref = a;

    b->letter = temp->letter;
    b->occ = temp->occ;
    b->node = temp->node;
    b->node->element_ref = b;
}

void new_compare(int *comparer_curr, int *comparer_to_insert, Element *curr, Element *to_insert,
                 int node_or_elem, int size_or_letter)
{
    if (size_or_letter)
    {
        if (node_or_elem)
        {
            *comparer_curr = curr->letter;
            *comparer_to_insert = to_insert->letter;
        }
        else
        {
            *comparer_curr = curr->node->letter;
            *comparer_to_insert = to_insert->node->letter;
        }
    }
    else
    {
        if (node_or_elem)
        {
            *comparer_curr = curr->occ;
            *comparer_to_insert = to_insert->occ;
        }
        else
        {
            *comparer_curr = curr->node->size;
            *comparer_to_insert = to_insert->node->size;
        }
    }
}

void insert_elem(Element *to_insert, Element *after, int insert_before)
{
    Element *temp = after->next;
    after->next = to_insert;
    to_insert->next = temp;
    if (insert_before)
    {
        swap(after, to_insert);
    }
}

//adding an element to a sorted descending array without diturbing the order

Element *insert_elem_desc(Element *root, Element *to_insert, int node_or_elem, int size_or_letter, int verbose)
{
    if (verbose)
    {
        printf("\n*** insert_elem_desc (%s, %s) ***", (node_or_elem ? "elem" : "node"), (size_or_letter ? "letter" : "size"));
    }

    Element *curr = root;
    int comparer_curr, comparer_to_insert;
    new_compare(&comparer_curr, &comparer_to_insert, curr, to_insert, node_or_elem, size_or_letter);

    if (comparer_to_insert > comparer_curr)
    {
        if (verbose)
        {
            if (node_or_elem)
            {
                printf("\n to_insert (%s, %d) greater than root (%s, %d): inserting and swapping", display_char(to_insert->letter),
                       to_insert->occ, display_char(root->letter), root->occ);
            }
            else
            {
                printf("\n to_insert [");
                print_node(to_insert->node);
                printf("] greater than root [");
                print_node(root->node);
                printf("]: inserting and swapping");
            }
        }
        insert_elem(to_insert, root, 1);
        if (verbose)
        {
            printf("\n************************\n");
        }
        return root;
    }
    else
    {
        while (comparer_curr > comparer_to_insert)
        {
            if (curr->next == NULL)
            {
                if (node_or_elem)
                {
                    printf("\nreached the end of the occurrences: inserting at the end");
                }
                else
                {
                    printf("\nreached the end of the occurrences: inserting at the end");
                }
                curr->next = to_insert;
                if (verbose)
                {
                    printf("\n************************\n");
                }
                return to_insert;
            }
            else
            {
                if (verbose)
                {
                    if (node_or_elem)
                    {
                        printf("\nto_insert (%s, %d) smaller than curr (%s, %d): continuing", display_char(to_insert->letter),
                               to_insert->occ, display_char(curr->letter), curr->occ);
                    }
                    else
                    {
                        printf("\nto_insert [");
                        print_node(to_insert->node);
                        printf("] smaller than [");
                        print_node(curr->node);
                        printf("]: continuing");
                    }
                }
                curr = curr->next;
                new_compare(&comparer_curr, &comparer_to_insert, curr, to_insert, node_or_elem, size_or_letter);
            }
        }
        if (verbose)
        {
            if (node_or_elem)
            {
                printf("\nto_insert (%s, %d) greater than or equal to curr (%s, %d): inserting", display_char(to_insert->letter), to_insert->occ,
                       display_char(curr->letter), curr->occ);
            }
            else
            {
                printf("\n to_insert [");
                print_node(to_insert->node);
                printf("] greater than or equal to curr [");
                print_node(curr->node);
                printf("]: inserting");
            }
        }
        insert_elem(to_insert, curr, 1);
        if (verbose)
        {
            printf("\n************************\n");
        }
        return to_insert;
    }
}

int SPACING = 10;

// Displays a tree with the leaves first, going back to the root

void print_tree_2D(Node *root, int space)
{
    if (root == NULL)
        return;

    space += SPACING;

    // Process right children first
    print_tree_2D(root->right, space);

    // Display the current node
    printf("\n");
    for (int i = SPACING; i < space; i++)
        printf(" ");

    if (root->letter == -1)
    {
        printf("(%d)\n", root->size);
    }
    else
    {
        printf("(%s, %d)\n", display_char(root->letter), root->size);
    }

    // Process left children afterwards
    print_tree_2D(root->left, space);
}

void print_tree_2D_wrapper(struct Node *root)
{
    print_tree_2D(root, 0);
}




// E : fonction qui stocke dans un fichier txt le dictionnaire issu de l’arbre de Huffman.

void new_code(char zero_or_one, Node *node)
{
    node->code = insert_char_in_front(zero_or_one, node->code);
}

void propagate_new_code(char zero_or_one, Node *node)
{
    new_code(zero_or_one, node);
    if (node->left != NULL)
    {
        propagate_new_code(zero_or_one, node->left);
    }

    if (node->right != NULL)
    {
        propagate_new_code(zero_or_one, node->right);
    }
}

Element *copy_elems_shallow_nodes(Element *root)   // convient mieux ici qu'une deep copy
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        Element *new_root = new_element(root->letter);
        new_root->occ = root->occ;
        new_root->node = root->node;
        new_root->next = copy_elems_shallow_nodes(root->next);
        return new_root;
    }
}

HuffmanTree *huffman_tree_from_occurrences(Element *root)
{
    quick_sorting_wrapper(root);
    Element *curr = root;
    curr->node = new_node(curr->letter, curr->occ, NULL, NULL, curr);

    while (curr->next != NULL)
    {
        curr = curr->next;
        curr->node = new_node(curr->letter, curr->occ, NULL, NULL, curr);
    }

    Element *dict = copy_elems_shallow_nodes(root);  //on garde l'ordre des occurrences tout en pouvant modifier ses elements
    // grace aux prpagate_new_code
    int curr_len = len(root);
    while (curr_len > 1)
    {
        Element *first = get_element(root, curr_len - 1);
        Element *second = get_element(root, curr_len - 2);

        propagate_new_code('0', first->node);
        propagate_new_code('1', second->node);

        Element *sum_elem = malloc(sizeof(Element));
        sum_elem->letter = -1;
        sum_elem->occ = -1;
        sum_elem->node = new_node(-1, first->node->size + second->node->size, first->node, second->node, sum_elem);
        insert_elem_desc(root, sum_elem, 0, 0, 0);

        get_element(root, curr_len - 2)->next = NULL;
        first->next = NULL;
        second->next = NULL;
        curr_len = curr_len - 1;
    }
    HuffmanTree *huffman_tree = malloc(sizeof(HuffmanTree));
    huffman_tree->root_dict = dict;
    huffman_tree->root_node = root->node;

    return huffman_tree;
}

char *delim = ": ";
char *separator = "\n";

void write_huffman_dict(FILE *dict_file, Element *dict)
{
    Element *curr_elem = dict;
    char *buffer;
    char *curr_char;
    char *curr_code;
    int length;

    char *string_format = malloc(sizeof(char) * (4 + strlen(delim) + strlen(separator)));
    sprintf(string_format, "%s%s%s%s", "%s", delim, "%s", separator);

    if (dict_file != NULL && curr_elem != NULL)
    {
        while (curr_elem != NULL)
        {

            curr_char = display_char(curr_elem->letter);  //associe un nom aux caracteres speciaux
            curr_code = curr_elem->node->code;
            length = strlen(curr_char) + strlen(delim) + strlen(curr_code) + strlen(separator);

            buffer = malloc(length * sizeof(char)); //recuperer le resultat de sprintf avec des tailles variables
            sprintf(buffer, string_format, curr_char, curr_code);
            fwrite(buffer, 1, length, dict_file); //ecrire le fichier ligne par ligne

            curr_elem = curr_elem->next;
        }
        fseek(dict_file, 0, SEEK_SET); // pour se déplacer/revenir au début d'un fichier
    }
}



// F : fonction qui traduit un texte en une suite binaire basée sur un dictionnaire de Huffman.


FILE *open_file(char *file, char *mode)
{
    FILE *input_file = fopen(file, mode);
    if (input_file == NULL)
    {
        // Si fopen n'arrive pas a ouvrir le fichier
        printf("Error: input file cannot be opened."); // Message d'erreur
        exit(EXIT_FAILURE);                            // Arrêt du programme
    }
    return input_file;
}

int char_to_binary(int word)
{
    int res = 0, i = 1;
    while (word > 0)
    {
        //printf("%d %d %d\n", word % 2 , i, word);
        res = res + (i * (word % 2));
        word = word / 2;
        i = i * 10;
    }
    return res;
}

int nb_char_in_file(FILE *input_file, int verbose)
{
    int cpt = 0;
    char curr_char;
    if (verbose)
    {
        printf("\n*** nb_char_in_file ***\n");
    }
    if (input_file != NULL)
    {
        do
        {
            curr_char = fgetc(input_file);
            if (curr_char == EOF)
            {
                printf("Reached end of file.\n");
            }
            else
            {
                cpt++;
                if (verbose)
                {
                    printf("%s (%d)\n", display_char(curr_char), cpt);
                }
            }
        }
        while (curr_char != EOF);
    }
    fseek(input_file, 0, SEEK_SET);
    if (verbose)
    {
        printf("Got %d chars.", cpt);
        printf("\n***********************\n");
    }
    return cpt;
}

void file_to_binary_file(FILE *input_file, FILE *output_file, int verbose)
{
    if (input_file != NULL && output_file != NULL)
    {
        if (verbose)
        {
            printf("\n*** file_to_binary_file ***\n");
            printf("In binary: ");
        }

        char chr;
        int bin;
        do
        {
            chr = fgetc_ascii(input_file);
            bin = char_to_binary((int)chr);
            if (verbose)
            {
                printf("\n%s: %08d", display_char(chr), bin);
            }
            fprintf(output_file, "%08d", bin);
        }
        while (chr != EOF);

        fseek(input_file, 0, SEEK_SET);
        fseek(output_file, 0, SEEK_SET);
        if (verbose)
        {
            printf("\n***************************\n");
        }
    }
}



// G : fonction qui compresse un fichier texte
//     Le fichier d’entree ne sera pas modifie, un autre fichier, contenant le texte compresse sera cree


Element *find_elem_in_dict(Element *dict, char *value, int letter_or_code)
{
    Element *curr_elem = dict;
    if (curr_elem != NULL)
    {
        while (curr_elem != NULL)
        {
            if (letter_or_code && strcmp(curr_elem->node->code, value) == 0)
            {
                return curr_elem; //si le code est egal a la value, on renvoie l'element current
            }
            else if (!letter_or_code && curr_elem->letter == value[0]) //quand le flag = 1 on compare la lettre a value[0]
            {
                return curr_elem;
            }
            else
            {
                curr_elem = curr_elem->next;
            }
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

void compress_file(FILE *input, FILE *output, HuffmanTree *huffman_tree, int verbose)
{
    if (input != NULL)
    {
        char curr_char;
        char *curr_code;
        Element *curr_elem;
        do
        {
            curr_char = fgetc_ascii(input); //recupere seulement les caracteres en ASCII
            if (curr_char == EOF)
            {
                if (verbose)
                {
                    printf("Reached end of file.\n");
                }
            }
            else
            {
                curr_elem = find_elem_in_dict(huffman_tree->root_dict, &curr_char, 0);
                curr_code = curr_elem->node->code;
                fwrite(curr_code, 1, strlen(curr_code), output);

                if (verbose)
                {
                    printf("Current character: %s (writing %s)\n", display_char(curr_char), curr_code);
                }
            }
        }
        while (curr_char != EOF); //do while va permettre de changer l'ordre des operations

        fseek(input, 0, SEEK_SET);
        fseek(output, 0, SEEK_SET);
    }
    else
    {
        printf("Error: could not read input file");
        exit(EXIT_FAILURE);
    }
}

/*void compress_file_wrapper(FILE *input, FILE *output) //simplifier l'appel de la fonction
{
    Element *occurrences = get_occurrences_by_dichotomy(input, 0);
    HuffmanTree *huffman_root = huffman_tree_from_occurrences(occurrences);

    compress_file(input, output, huffman_root, 0);
}
*/


// H : fonction qui decompresse un fichier texte a partir d’un arbre de Huffman.
// Le fichier d’entree ne sera pas modifie, un autre fichier, contenant le texte décompressé sera cree


Node ** trad_fic_tab(FILE * f, int * nbre_cara, int * nbre_chara_diff)
{
    FILE* trad = NULL;

    trad = fopen("traduction.txt","r+");
    char * binaire = malloc(sizeof(char)*9);
    char actuel;
    Node ** add_tab = malloc(sizeof(Node*));

    if(f!=NULL)
    {
        actuel = fgetc(f);
        while(actuel!=EOF)
            //do
        {
            (*nbre_cara)++;

            //    actuel = fgetc(f);
            if (actuel!=-1)
            {
                //   printf("NBRE CARA AVANT LA FONCTION [%d] ", (*nbre_cara));
                add_tab_elem(&add_tab,actuel, nbre_cara, nbre_chara_diff);
                binaire = hexa_to_binary(actuel);
                fputs(binaire,trad);
            }
            actuel = fgetc(f);



        }//while(actuel!=EOF);
        //print_tab((*add_tab), (*nbre_cara)); // ICI FAIRE UN AFFICHER TAB
        (*nbre_cara)--; //psq do whhile donc un caractere en plus

    }
    fclose(trad);
    return add_tab;

}

void add_tab_elem( Node *** add_tab, char cara , int * nbre_cara, int * nbre_chara_diff)
{
    int i=0;
    int min =0;
    int max =((*nbre_chara_diff)-1);
    int middle = (min+max)/2;

    if((*nbre_chara_diff)<2) //pour mettre les deux premier carac
    {
        if((*nbre_chara_diff)==0)
        {
            (*nbre_chara_diff)++;
            (*add_tab)[0]= create_node_v1((add_tab[0]), cara);

        }
        else if(cara== (*add_tab)[0]->letter)
        {
            (*add_tab)[0]->size++;
        }
        else
        {
            (*nbre_chara_diff)++;
            (*add_tab)= realloc(*add_tab,(*nbre_chara_diff)*sizeof(Node*));
            (*add_tab)[(*nbre_chara_diff)-1]= create_node_v1((add_tab[(*nbre_chara_diff)-1]), cara);
        }
    }
    else
    {
        if(verif_existent_carac(*add_tab,cara, &min,&middle,&max)==0)
        {
            (*nbre_chara_diff)++;
            (*add_tab)= realloc(*add_tab,(*nbre_chara_diff)*sizeof(Node*));

            for(i=(*nbre_chara_diff)-1; i>(min); i--) //mayb il faut faire -1
            {
                (*add_tab)[i]=(*add_tab)[i-1];
            }

                Node * new_node = create_node_v1(&new_node,cara);
                //printf("C L INDICE OU IL SERA INSERER [%d] pour [%c] ",min,(*add_tab)[middle]->letter);
                (*add_tab)[min]=new_node;
        }
    }
}


Node * create_node_v1(Node **tree, char cara)
{
    (*tree)= (Node*) malloc(sizeof(Node));
    (*tree)->size=1;
    (*tree)->letter = cara;
    (*tree)->left=NULL;
    (*tree)->right=NULL;

    return (*tree);

}

int verif_existent_carac(Node ** add_tab, char cara, int * min , int * middle, int * max)
{
    int trouver =0;

    while((*min)<=(*max)&&(trouver==0))
    {
        if(cara <(add_tab)[*middle]->letter)
        {
            (*max) = (*middle)-1;
        }
        else if(cara > (add_tab)[*middle]->letter)
        {
            (*min) = (*middle)+1;
        }
        else
        {
            trouver=1;
        }
        (*middle) = (*min+*max)/2;
    }

    if(trouver==1)
    {
        (add_tab)[*middle]->size++;
        return trouver;
    }
    else
    {
        return trouver;
    }

}




void print_tab(Node **tab, int nbre_cara)
{
    int i;

    for (i=0 ; i<nbre_cara ; i++)
    {
        printf("Caractère tab[%d]-> %c \n", nbre_cara, tab[i]->letter);
    }
}





// I : fonction qui, par recherche dichotomique, ajoute à un tableau de nœuds une occurrence
//     quand le caractère a déjà été trouvé, ou qui ajoute le nœud du caractère sinon.

int len(Element *root)
{
    Element *curr = root;
    int i;
    for (i = 1; curr->next != NULL; i++)
    {
        curr = curr->next;
    }
    return i;
}

// Add occurrences to a new tab (kept in descending order) by dichotomy
Element *get_occurrences_by_dichotomy(FILE *input_file, int verbose)
{
    if (verbose)
    {
        printf("\n*** get_occurrences_by_dichotomy ***\n");
    }

    char curr_char = fgetc_ascii(input_file);

    // Create and initialize the tab
    Element *root;
    if (curr_char == EOF)
    {
        printf("Error: file is empty.");
        exit(EXIT_FAILURE);
    }
    else
    {
        root = new_element(curr_char);
        if (verbose)
        {
            printf("Starting with character %s, adding with occurence: %d\n", display_char(curr_char), 1);
        }
        curr_char = fgetc_ascii(input_file);
    }

    int lower_bnd, upper_bnd, middle;
    Element *curr;

    int curr_len = 1;
    while (curr_char != EOF)
    {
        lower_bnd = 0;
        upper_bnd = curr_len - 1;
        middle = (upper_bnd + lower_bnd) / 2;
        curr = get_element(root, middle);
        if (verbose)
        {
            printf("\nSearching for the next letter: %s (%d) (lower bound: %d, upper bound: %d)", display_char(curr_char), curr_char, lower_bnd, upper_bnd);
        }
        while (lower_bnd < upper_bnd)
        {
            if (verbose)
            {
                printf("\nSearching... lower: %d, upper: %d, middle: %d", lower_bnd, upper_bnd, middle);
                printf("\nCurrent element: ");
                print_element(curr, 0, 0);
            }

            if (curr_char > curr->letter)
            {
                upper_bnd = middle - 1;
            }
            else if (curr_char < curr->letter)
            {
                lower_bnd = middle + 1;
            }
            else
            {
                lower_bnd = middle;
                upper_bnd = middle; //End the while loop
            }
            if (verbose)
            {
                printf("\nNearest index hasn't yet been reached; current index (idx: %d, letter: %s)\n", middle,
                       display_char(curr->letter));
                printf("New boundaries: (%d, %d)\n", lower_bnd, upper_bnd);
            }
            middle = (upper_bnd + lower_bnd) / 2;
            curr = get_element(root, middle);
        }

        if (verbose)
        {
            printf("\nNearest index reached: %d", middle);
            printf("\nCurrent element: ");
            print_element(curr, 0, 0);
        }
        if (curr->letter == curr_char)
        {
            if (verbose)
            {
                printf("Letter %s already exists, new occurence: %d\n", display_char(curr_char), curr->occ + 1);
            }
            curr->occ++;
        }
        else
        {
            if (verbose)
            {
                printf("Letter %s isn't in the list, adding with occurence: %d\n", display_char(curr_char), 1);
            }

            if (curr_char < curr->letter)
            {
                insert_elem(new_element(curr_char), curr, 0);
            }
            else
            {
                insert_elem(new_element(curr_char), curr, 1);
            }
            //insert_elem_desc(root, new_element(curr_char), 1, 1, 1);
            curr_len++;
        }

        curr_char = fgetc_ascii(input_file);
    }
    fseek(input_file, 0, SEEK_SET);

    if (verbose)
    {
        printf("\ngot occurrences:");
        print_occurrences(root, 0, 0);
        printf("\n***********************************\n");
    }

    return root;
}

int MAX_TAB = 255;

Node* add_by_dichotomie_v2 (FILE* my_file, int *len)
{
    //Open the text file
    FILE* file = fopen(my_file, "w");
    if(file==NULL)
    {
        printf("\n OPENING ERROR : FILE MY_FILE \n");
        exit(EXIT_FAILURE);
    }

    //Create and initialize the tab

   Node* tab = malloc(MAX_TAB*sizeof(Node));
   int idx = 0;
    for(int idx=1; idx<MAX_TAB; idx++)
    {
        tab[idx].letter = idx;
        tab[idx].size = 0;
        tab[idx].left = NULL;
        tab[idx].right = NULL;
    }

    int cpt = 0;
    int my_char = fgetc(file);
    int lower_bnd, upper_bnd, pos, middle;

    //Add occurrences to my tab by dichotomy
    while(my_char != EOF)
    {
        lower_bnd = 0;
        upper_bnd = MAX_TAB-1;
        pos = -1;
        while((lower_bnd<=upper_bnd)&&(pos == -1))
        {
            middle = (upper_bnd+lower_bnd)/2;
            if(my_char < tab[middle].letter)
            {
                upper_bnd = middle-1;
            }
            else if (my_char > tab[middle].letter)
            {
                lower_bnd = middle+1;
            }
            else
            {
                pos = middle;
            }
        }
        if(tab[pos].size == 0)
        {
            cpt += 1;
        }
        tab[pos].size += 1;
        my_char = fgetc(file);
    }

    //Create the end tab (to return)
    Node* end_tab = malloc(sizeof(Node));
    int j = 0;
    for(idx = 0; idx<cpt ; idx++){
        while (tab[j].size == 0)
    {
        j = j+1;
    }
    end_tab[idx] = tab[j];
    j+=1;
    }

    //Close the file
    free(tab);
    fclose(file);
    return end_tab;
}



// J : Fonction qui trie un tableau de noeuds en fonction des occurrences

// C Implementation of the Quick Sorting Algorithm for Linked List
void quick_sorting(Element *root, int first, int last)
{
    int pivot;
    if (first < last)
    {
        pivot = first; //On definit le pivot au debut
        int curr_pivot_occ = get_element(root, pivot)->occ;

        int i = first, j = last;
        while (i < j)
        {
            // On cherche un element plus grand que le pivot a gauche
            while ((get_element(root, i)->occ >= curr_pivot_occ) && (i < last))
            {
                i++;
            }

            // On cherche un element plus petit que le pivot a droite
            while (get_element(root, j)->occ < curr_pivot_occ)
            {
                j--;
            }

            // Si les deux éléments existent, on les échange
            if (i < j)
            {
                swap(get_element(root, i), get_element(root, j));
            }
        }

        swap(get_element(root, pivot), get_element(root, j));
        quick_sorting(root, first, j - 1); // On repete l'operation jusqu'a obtenir les deux sub-tables
        quick_sorting(root, j + 1, last);
    }
}

void quick_sorting_wrapper(Element *root)
{
    quick_sorting(root, 0, len(root) - 1);
}





// K :  fonction qui, en utilisant deux files, crée l’arbre de Huffman à partir d’un tableau
//      de noeuds trié par occurrences.


Element_node * Tab_to_element(Node ** tab, int nbre_chara_diff )
{
    Element_node* list =NULL;
    Element_node * temp=NULL;
    int i=0;

    if(tab!=NULL)
    {
        list= malloc(sizeof(Element_node));
        temp=list;
        while(i<nbre_chara_diff-1)
        {
            temp->data = tab[i];
            temp->next = malloc(sizeof(Element_node));
            temp=temp->next;
            i++;
        }
        temp->data=tab[i];

    }
    return list;
}


Queue* create_queue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = NULL;
    return q;
}

int is_empty(Queue* q)
{

    if(q->data == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(Queue * q, Node * val)
{
    Element_node * nouv_el = malloc(sizeof(Element_node));
    nouv_el->data = val;
    nouv_el->next = NULL;

    Element_node * temp;
    if(is_empty(q) == 0)
    {
        temp= q->data;
        while((temp->next !=NULL)&&(nouv_el->data->size > q->data->data->size))
        {
            temp=temp->next;
        }
        nouv_el->next = temp->next;
        temp->next = nouv_el;
    }
    else
    {
        q->data = nouv_el;
    }

}


Node * dequeue(Queue * q)
{
    if(is_empty(q)==0)
    {
        Element_node *old = q->data;
        q->data = q->data->next;
        Node * res = old->data;
        free(old);
        return res;
    }

}


Node * compare_min_queue(Queue * q1, Queue *q2 )
{
    Node * n;

    if(is_empty(q1)==0)
    {
        if(is_empty(q2)==1)
        {
            n= dequeue(q1);
        }
        else if (q1->data->data->size < q2->data->data->size)
        {
            n= dequeue(q1);
        }
        else if (q1->data->data->size > q2->data->data->size)
        {
            n= dequeue(q2);
        }
    }
    else
    {
        n =dequeue(q2); //PEUT ETRES ET Q2!=NULL
    }

    return n;
}


Node * create_Node_fused_v2( Queue * q1, Queue * q2 )
{
    Node * tree = malloc(sizeof(Node));

    tree->left = compare_min_queue(q1,q2);
    tree->right = compare_min_queue(q1,q2);

    tree->size = tree->left->size + tree->right->size;
    // tree->letter = NULL;

    return tree;
}

void afficherListe_Node(Element_node *liste)
{
    Element_node* temp=liste;
    //printf("VOICI la liste des noeuds : \n");
    while (temp != NULL)
    {
        printf("'%c' = ",temp->data->letter);
        printf("%d -> ", temp->data->size);
        temp = temp->next;
    }

}

Node * create_queue_Huffman_tree(Queue * q1, Queue * q2, Element_node * l_element)
{
    q1 = create_queue();
    q1->data = l_element;

    q2= create_queue();

    while((is_empty(q1)==0)||(q2->data->next!=NULL))
    {
        //printf("Q1:");
        // afficherListe_Node(q1->data);
        //printf("\n Q2: ");
        // afficherListe_Node(q2->data);
        //  printf("\n\n\n");

        Node * node_fused = create_Node_fused_v2(q1,q2);
        enqueue(q2, node_fused);
    }
    return q2->data->data;
}



// L : fonction qui organise les nœuds dans un AVL en fonction de l’ordre des caracteres presents.


void add_node_BST(Node_AVL** tree, const char letter, const int* code, int code_index)
{

    if(*tree == NULL)
    {
        *tree = create_node_AVL(letter, code, code_index);
    }
    else
    {
        if ((int)(*tree)->letter > (int)letter)
        {
            add_node_BST(&((*tree)->left), letter, code, code_index);
        }
        else if ((int)(*tree)->letter < (int)letter)
        {
            add_node_BST(&((*tree)->right), letter, code, code_index);
        }
    }
}


int depth(const Node_AVL* tree)
{
    if(tree == NULL)
    {
        return 0;//warning definition. -1 ou 0
    }
    else
    {
        int depth_left = depth(tree->left);
        int depth_right = depth(tree->right);
        if(depth_left > depth_right)
        {
            return 1 + depth_left;
        }
        else
        {
            return 1 + depth_right;
        }
    }
}

int bf(const Node_AVL* tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    else
    {
        return depth(tree->right) - depth(tree->left);
    }
}



void right_rotation(Node_AVL** tree)
{
    if (*tree != NULL)
    {
        Node_AVL* temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = *tree;
        *tree = temp;
    }
}

void left_rotation(Node_AVL** tree)
{
    if (*tree != NULL)
    {
        Node_AVL* temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = *tree;
        *tree = temp;
    }
}

void balance(Node_AVL** tree)
{
    if (*tree != NULL)
    {
        balance(&((*tree)->left));// Postfix
        balance(&((*tree)->right));

        int balance_factor = bf(*tree);
        if (balance_factor <= -2) // Cas left - ??
        {
            if(bf((*tree)->left) > 0) // left - right
            {
                left_rotation(&((*tree)->left));
            }
            right_rotation(tree);// left - left
        }
        else if (balance_factor >= 2) // Cas right - ??
        {
            if(bf((*tree)->right) < 0) // right - left
            {
                right_rotation(&((*tree)->right));
            }
            left_rotation(tree);// right - right
        }
    }
}


void add_node_AVL(Node_AVL** tree, const char letter, int* code, int code_index)
{
    add_node_BST(tree, letter, code, code_index);
    balance(tree);
}



void code_from_tree(const Node* tree, int* code, int* code_index, Node_AVL** AVL){
    if (tree != NULL){
        if (tree->left == NULL && tree->right == NULL){
            code[*code_index] = 2;
            add_node_AVL(AVL, tree->letter, code, *code_index);
        }
        code[*code_index] = 0;
        *code_index = *code_index + 1;
        code_from_tree(tree->left, code, code_index, AVL);
        *code_index = *code_index - 1;
        code[*code_index] = 1;
        *code_index = *code_index + 1;
        code_from_tree(tree->right, code, code_index, AVL);
        *code_index = *code_index - 1;
    }
}

Node_AVL* AVL_dico (const Node* tree){
    Node_AVL* new_tree = NULL;

    if(tree!=NULL){
        int* code = calloc(1, 100*sizeof(int));
        int code_index = 0;
        code_from_tree(tree, code, &code_index, &new_tree);
    }
    return new_tree;
}


void fill_dico(const Node_AVL* tree, const FILE* file){
    if(tree!=NULL){
        fprintf(file, "%c", tree->letter);
        int i = 0;
        while(tree->code[i] == 1 || tree->code[i] == 0){
            fprintf(file, "%d", tree->code[i]);
            i++;
        }
        fprintf(file, "\n");
        fill_dico(tree->left, file);
        fill_dico(tree->right, file);
    }
}


void write_AVL_in_dico(Node_AVL* tree, char* dico){
    FILE* file = NULL;
    file = fopen(dico, "w+");
    if(file != NULL){
        fill_dico(tree, file);
        fclose(file);
    }
}



Node_AVL* create_node_AVL(const char letter, const int* code, int code_index){
    Node_AVL* new_node = (Node_AVL*)malloc(sizeof(Node_AVL));
    new_node->letter = letter;
    int i = 0;
    while (code[i] != 2){
        new_node->code[i] = code[i];
        i++;
        code_index --;
    }
    new_node->code[i] = 2;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void print_tree_AVL(const Node_AVL *tree)
{
    if (tree != NULL){
        printf("\n");
        printf("(%c|", tree->letter);
        int i = 0;
        while (tree->code[i] == 1 || tree->code[i] == 0){
            printf("%d", tree->code[i]);
            i++;
        }
        printf(")");

        print_tree_AVL(tree->left);
        print_tree_AVL(tree->right);
    }
}


void free_tree_AVL (const Node_AVL* tree)
{
    if(tree != NULL){
        free_tree_AVL(tree->left);
        free_tree_AVL(tree->right);
        free(tree);
    }
}



// M : fonction qui compresse un fichier texte de façon optimisee. Le fichier d’entree
//     ne sera pas modifie, un autre fichier, contenant le texte compressé sera cree.

char* copy2(const char* chaine){
    char* code = calloc(1, strlen(chaine)*sizeof(char));
    int i = 0, j;
    for(j=1; j< strlen(chaine) ; j++){
        code[i] = chaine[j];
        i++;
    }
    return code;
}


// function to find the code in the AVL

char* find_code (const Node_AVL* tree, const char c)
{
    if((int)(tree->letter)==(int)c){
        char* final = calloc(1,100*sizeof(char));
        int i = 0;
        while(tree->code[i] != 2){
            if(tree->code[i]==1){
                final[i] = '1';
            }
            else {
                final[i] = '0';
            }
            i++;
        }
        return final;
    }
    else if ((int)(tree->letter)> (int)c){
        return find_code(tree->left, c);
    }
    else {
        return find_code(tree->right, c);
    }
}

void encoding_v2 (const Node_AVL* tree, const char* output, const char* input){
    FILE* fich = NULL;
    FILE* fich2 = NULL;
    fich = fopen(input, "r");
    int current_letter = 0;
    fich2 = fopen(output, "w");

    if(fich2 == NULL){
        printf("Error to open output.");
    }
    if(fich == NULL){
        printf("Errore to open input");
    }
    else {
        do{
            current_letter = fgetc(fich);
            if(current_letter >= 0){
                char *code = find_code(tree, (char)current_letter);
                fputs(code,fich2);
            }
        }while(current_letter != EOF);
        fclose(fich2);
    }
    fclose(fich);
}



// N : fonction qui decompresse un fichier texte a partir d’un fichier dictionnaire d’Huffman.
//     Le fichier texte d’entree ne sera pas modifié, un autre fichier, contenant le texte
//     décompresse sera cree.


// fonctions utiles

// to de create a new node

Node* create_node(char c, int oc){
    Node* new_tree = (Node*)malloc(sizeof(Node));
    new_tree->letter = c;
    new_tree->size = oc;
    new_tree->left = NULL;
    new_tree->right = NULL;
    return new_tree;
}


//to copy the code in the file

char* copy(const char* chaine){
    char* code = calloc(1, strlen(chaine)*sizeof(char));
    int i=0, j;
    for(j=2; j < strlen(chaine); j++){
        code[i] = chaine[j];
        i++;
    }
    return code;
}


// we recreate the Huffman tree and then we create a function add alement in the Huffman tree

void add_element(char* code, Node** Huffman_tree, const char letter, int pos){
    if (*Huffman_tree != NULL){  // if the node isn't void
        if(code[pos]== '0'){
            add_element(code, &((*Huffman_tree)->left), letter, (pos+1)); // go to left if we are on 0 in the code
        }
        else if(code[pos]== '1'){
            add_element(code, &((*Huffman_tree)->right), letter, (pos+1)); // go to right if we are on 1 in the code
        }
    }
    else{
        if(strlen(code) != pos){  // if we are not at the end of the code we go ahead
            *Huffman_tree = create_node(NULL, pos);
            if(code[pos]=='0'){
                add_element(code, &((*Huffman_tree)->left),letter, pos+1);
            }
            else if(code[pos]== '1'){
                add_element(code, &((*Huffman_tree)->right), letter, (pos+1));
            }
        }
        else {    // if we are at the end of the code we create a node at the position
            *Huffman_tree = create_node(letter, code[pos]);
        }
    }
}

// we recreate the Huffman tree from the dict file

Node* Huffman_tree_from_dico (const char* dict){

    Node* Huffman_tree = create_node(NULL, NULL);
    int MAX_SIZE = 100;

    FILE* fich = NULL;
    char chaine[MAX_SIZE];
    char* code = NULL;
    char letter;
    fich = fopen(dict, "r");

    if(fich == NULL){
        printf("\n Error to open dico");
    }
    else{
        while(fgets(chaine, MAX_SIZE, fich)!= NULL){
            if(chaine[0]!= '\n'){
                if(chaine[strlen(chaine)-1]=='\n'){
                    chaine[strlen(chaine)-1] = '\0';
                }
                code = copy(chaine);                  // we save the code
                letter = chaine[0];                   // we save the letter
                add_element(code, &Huffman_tree, letter , 0);  // we add the Huffman tree with the help of the
                                                      // code and a position in the code
            }

            else {                                    // pour le cas ou on a un retour a la ligne
                fgets(chaine, MAX_SIZE, fich);
                if(chaine[strlen(chaine)-1]=='\n'){
                    chaine[strlen(chaine)-1] = "\0";
                }
                code = copy2(chaine);
                add_element(code, &Huffman_tree, '\n', 0);   //'\n' = letter et 0 = pos

            }
        }
    }
    fclose(fich);
    return Huffman_tree;
}

void optimised_decoding(const char* output_Huffman, const char* dict, const char* decoding){
    // we open the Huffman file
    FILE* fic = fopen(output_Huffman, "r");
    if(fic==NULL){
        printf("\n  OPENING FAIL \n");
        exit(EXIT_FAILURE);
    }

    // we create or erase the decoding file to write the text inside
    FILE* dec = fopen(decoding, "w+");
    if(dec==NULL){
        printf("\n  OPENING FAIL \n");
        exit(EXIT_FAILURE);
    }


    // we create my_char to travel the file
    int my_char = fgetc(fic);
    Node* t = Huffman_tree_from_dico(dict);
    // print_tree_2D_wrapper(t);
    Node* temp = create_node(NULL, 0);
    temp = t;
    while(my_char != EOF){
        if(my_char == 48 && temp->left != NULL){
            temp = temp-> left;
        }
        else if(my_char == 49 && temp->left != NULL){
            temp = temp-> right;
        }

        if(temp->letter != NULL){
            fprintf(dec, "%c", temp->letter);
            temp = t;
        }
        my_char = fgetc(fic);
    }
    free_tree(t);
    fclose(fic);
    fclose(fic);
}

void free_tree(const Node* node)
{
    if(node!=NULL)
    {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }

}




