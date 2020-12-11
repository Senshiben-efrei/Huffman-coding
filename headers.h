#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>



// Structures

typedef struct Node
{
    int letter;                //  Contained letter in (= -1 if no letter is contained)
    int size;                  //  Weight/Occurence of the node
    struct Node *left, *right; //  Pointers to the nodes below this Node
    char *code;
    struct Element *element_ref;
} Node;

typedef struct Element_node
{
    Node * data;
    struct Element_node * next;

} Element_node;


typedef struct Element
{
    int letter;           //  Contained letter
    struct Element *next; //  Pointer to the next element
    int occ;              //  Number of occurrences of the letter
    Node *node;           //  Associated Node structure
} Element;

typedef struct HuffmanTree
{
    Node *root_node;
    Element *root_dict;
} HuffmanTree;


typedef struct Node_AVL
{
    char letter;
    int code[100];
    struct Node_AVL* left;
    struct Node_AVL* right;
} Node_AVL;

typedef struct Queue
{
    Element_node * data;
} Queue;

// fonctions utiles

char fgetc_ascii(FILE *file);
char *display_char(char chr);
Element *get_element(Element *root, int index);
char get_char_from_display_char(char *display_chr);
void print_node(Node *node);
void print_element(Element *element, int display_code, int elem_or_node);
void print_occurrences(Element *root, int display_code, int elem_or_node);


//A

void trad_fic(FILE * f,int * nbre_cara, Element_node ** add_l);
char * hexa_to_binary(char actuel);
void character_number(int * nbre_cara);
Element_node* create_elem(char cara);
void add_elem(char cara,Element_node** l);
void afficher_liste(Element_node* maListe);



//B
void afficher_caracteres(FILE** ftpr, char *Translation);


//C

int idx_letter(Element *root, char letter);
Node *new_node(int letter, int occ, Node *left, Node *right, Element *element_ref);
Element *new_element(int letter);
Element *get_occurrences(char *text);



// D

char *insert_char_in_front(char c, char *curr_string);
void swap(Element *a, Element *b);
void new_compare(int *comparer_curr, int *comparer_to_insert, Element *curr, Element *to_insert, int node_or_elem, int size_or_letter);
void insert_elem(Element *to_insert, Element *after, int insert_before);
Element *insert_elem_desc(Element *root, Element *to_insert, int node_or_elem, int size_or_letter, int verbose);
void print_tree_2D(Node *root, int space);
void print_tree_2D_wrapper(struct Node *root);



// E : fonction qui stocke dans un fichier txt le dictionnaire issu de l’arbre de Huffman

void new_code(char zero_or_one, Node *node);
void propagate_new_code(char zero_or_one, Node *node);
Element *copy_elems_shallow_nodes(Element *root);
HuffmanTree *huffman_tree_from_occurrences(Element *root);
void write_huffman_dict(FILE *dict_file, Element *dict);



//F

FILE *open_file(char *file, char *mode);
int char_to_binary(int word);
int nb_char_in_file(FILE *input_file, int verbose);
void file_to_binary_file(FILE *input_file, FILE *output_file, int verbose);


// G

Element *find_elem_in_dict(Element *dict, char *value, int letter_or_code);
void compress_file(FILE *input, FILE *output, HuffmanTree *huffman_tree, int verbose);


// H

Node ** trad_fic_tab(FILE * f, int * nbre_cara, int * nbre_chara_diff);
void add_tab_elem( Node *** add_tab, char cara, int * nbre_cara, int * nbre_chara_diff);
Node * create_node_v1(Node **tree, char cara);
int verif_existent_carac(Node ** add_tab, char cara, int * min, int * middle, int * max);
void  print_tab(Node **tab, int nbre_cara);



// I

int len(Element *root);
Element *get_occurrences_by_dichotomy(FILE *input_file, int verbose);
Node* add_by_dichotomie_v2 (FILE* imput, int *len);




//J

void quick_sorting(Element *root, int first, int last);
void quick_sorting_wrapper(Element *root);



// K

Element_node * Tab_to_element(Node ** tab, int nbre_chara_diff );
Queue* create_queue();
int is_empty(Queue* q);
void enqueue(Queue * q, Node * val);
Node * dequeue(Queue * q);
Node * compare_min_queue(Queue * q1, Queue *q2 );
Node * create_Node_fused_v2( Queue * q1, Queue * q2 );
void afficherListe_Node(Element_node *liste);
Node * create_queue_Huffman_tree(Queue * q1, Queue * q2, Element_node * l_element);


// L

void add_node_BST(Node_AVL** tree, const char letter, const int* code, int code_index);
int bf(const Node_AVL* tree);
void right_rotation(Node_AVL** tree);
void left_rotation(Node_AVL** tree);
void balance(Node_AVL** tree);
void add_node_AVL(Node_AVL** tree, const char letter, int* code, int code_index);
void code_from_tree(const Node* tree, int* code, int* code_index, Node_AVL** AVL);
Node_AVL* AVL_dico (const Node* tree);
void fill_dico(const Node_AVL* tree, const FILE* file);
void write_AVL_in_dico(Node_AVL* tree, char* dico);
Node_AVL* create_node_AVL(const char letter, const int* code, int code_index);
void print_tree_AVL(const Node_AVL *tree);
void free_tree_AVL (const Node_AVL* tree);


// M
char* copy2(const char* chaine);
char* find_code (const Node_AVL* tree, const char c);
void encoding_v2 (const Node_AVL* tree, const char* Huffman, const char* input);


// N
Node* create_node(char c, int oc);
char* copy(const char* chaine);
void add_element(char* code, Node** Huffman_tree, const char letter, int pos);
Node* Huffman_tree_from_dico (const char* dico);
void optimised_decoding(const char* output_Huffman, const char* dict, const char* decoding);
void free_Tree(const Node* node);



#endif // HEADERS_H_INCLUDED

