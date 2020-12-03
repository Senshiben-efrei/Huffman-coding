#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers.h"

void afficherListe(Element *list)
{
    if (list == NULL)
    {
        printf("Erreur");
        return;
    }

    Element *actuel = list;

    do
    {
        printf("\n %c : %d  ", actuel->letter, actuel->occ);
        actuel = actuel->next;
    }
    while (actuel != NULL);

    printf("NULL\n");
}


void afficher_caracteres(FILE** ftpr, char *Translation)
{
    int counter = 0;
    if ((*ftpr = fopen("Texte->txt", "r")) == NULL)
    {
        printf("Erreur, le fichier n'est pas disponible->");
        return 0;
    }
    fscanf(*ftpr, "%[^\n]", Translation);
    fclose(*ftpr);
    while (*Translation)
    {
        counter = counter + 1;
        ++Translation;
    }
    printf("Le nombre de caracteres dans Texte->txt est: %d", counter);
}



// C : fonction qui renvoie une liste contenant chaque caractere present dans le texte,
//     ainsi que le nombre d’occurrences de ce caractere->

int check_letter(Element* list, char letter)
{
    int idx = -1, compt = 0;    //if idx return the position, else -1
    if (list != NULL)
    {
        Element* temp = list;
        while (temp != NULL)
        {
            if (temp->letter == letter)
            {
                idx = compt;
            }
            temp = temp->next;
            compt ++;
        }
    }
    return idx;
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
            int idx_occ = check_letter(list_occ, text[i]);
            if(idx_occ == -1)
            {
                temp->next = new_letter(text[i]);
                temp = temp->next;
            }
            else
            {
                Element* temp = list_occ;
                while((temp != NULL) && (idx_occ>0))
                {
                    temp = temp->next;
                    idx_occ --;
                }
                temp->occ ++;
            }
        }
        return list_occ;
    }
    return NULL;
}


// D : fonction qui renvoie un arbre de Huffman, à partir d’une liste d’occurrences

void insert_node_element(Element* root, Element* to_insert)
{
    Element* curr = root;
    if (to_insert->node->size > root->node->size)
    {
        Element* temp = root->next;
        root->next = to_insert;
        to_insert->next = temp;
        swap(root, to_insert);
    }
    else
    {
        while(curr->next->node->size > to_insert->node->size)
        {
            if (curr->next == NULL)
            {
                printf("Erreur ...");
                return;
            }
            curr = curr->next;
        }
        Element* temp = curr->next;
        curr->next = to_insert;
        to_insert->next = temp;
    }
}

Node* Huffman_Tree(Element* root)
{
    quick_sorting_caller(root);
    Element* curr = root;
    curr->node = malloc(sizeof(Node));
    curr->node->letter = curr->letter;
    curr->node->size = curr->occ;
    curr->node->left = NULL;
    curr->node->right = NULL;

    while(curr->next != NULL)
    {
        curr = curr->next;
        curr->node = malloc(sizeof(Node));
        curr->node->letter = curr->letter;
        curr->node->size = curr->occ;
        curr->node->left = NULL;
        curr->node->right = NULL;
    }

    int curr_list_size = list_size(root);
    Node* root_node = curr->node;
    while(curr_list_size > 1)
    {
        printf("curr_list_size : %d \n", curr_list_size);
        Element* first = get_element(root, curr_list_size-1);
        Element* second = get_element(root, curr_list_size-2);

        Element* sum_node = malloc(sizeof(Element));
        sum_node->letter = NULL;
        sum_node->occ = -1;
        sum_node->node = malloc (sizeof(Node));
        sum_node->node->letter = NULL;
        sum_node->node->size = first->node->size + second->node->size;
        sum_node->node->left = first->node;
        sum_node->node->right = second->node;

        insert_node_element(root, sum_node);
        get_element(root, curr_list_size-3)->next = NULL;
        first->next = NULL;
        second->next = NULL;
        curr_list_size = curr_list_size-2;
        root_node = sum_node;
    }
    printf("curr_list_size : %d \n", curr_list_size);  // VERFIER SIZE LAST NODE
    return root_node;
}

// It does reverse inorder traversal
void print2DUtil(Node *root, int space)
{
// Base case
    if (root == NULL)
        return;

// Increase distance between levels
    space += 5;

// Process right child first
    print2DUtil(root->right, space);

// Print current node after space
// count
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("(%c, %d)\n", root->letter, root->size);

// Process left child
    print2DUtil(root->left, space);
}


// Wrapper over print2DUtil()
void print2D(struct Node *root)
{
// Pass initial space count as 0
    print2DUtil(root, 0);
}




// G : fonction qui compresse un fichier texte
//     Le fichier d’entree ne sera pas modifie, un autre fichier, contenant le texte compresse sera cree


Element* get_element(Element* root, int index)
{

    if (index>=0)
    {
        Element* curr = root;
        for(int i = 0; i<index; i++)
        {
            if (curr->next != NULL)
            {
                curr = curr->next;
            }
            else
            {
                return NULL;
            }
        }
        return curr;
    }
    else
    {
        return NULL;
    }

}

int	list_size(Element* root)
{
    Element* curr = root;
    int i;
    for(i=1; curr->next!=NULL ; i++)
    {
        curr = curr->next;
    }
    return i;
}

int MAX_TAB = 255;

Element* add_by_dichotomie_v2 (char* my_file)
{
    //Open the text file
    FILE* file = fopen(my_file, "r");
    if(file==NULL)
    {
        printf("\n OPENING ERROR : FILE MY_FILE \n");
        exit(EXIT_FAILURE);
    }

    //Create and initialize the tab
    Element* root = malloc(sizeof(Element));
    Element* curr = root;
    curr->letter = 0;
    curr->occ = 0;
    curr->next = NULL;
    for(int idx=1; idx<MAX_TAB; idx++)
    {
        curr->next = malloc(sizeof(Element));
        curr = curr->next;
        curr->letter = idx;
        curr->occ = 0;
        curr->next = NULL;
    }


    int cpt = 0;
    int curr_char = fgetc(file);
    int lower_bnd, upper_bnd, idx, middle;

    //Add occurrences to my tab by dichotomy
    while(curr_char != EOF)
    {
        lower_bnd = 0;
        upper_bnd = MAX_TAB-1;
        idx = -1;
        while((lower_bnd<=upper_bnd)&&(idx == -1))
        {
            middle = (upper_bnd+lower_bnd)/2;
            if(curr_char < get_element(root, middle)->letter)
            {
                upper_bnd = middle-1;
            }
            else if (curr_char > get_element(root, middle)->letter)
            {
                lower_bnd = middle+1;
            }
            else
            {
                idx = middle;
            }
        }
        if(get_element(root, idx)->occ == 0)
        {
            cpt += 1;
        }
        get_element(root, idx)->occ += 1;
        curr_char = fgetc(file);
    }

    //Create the end tab (to return)
    Element* end_tab = malloc(sizeof(Element));
    int j = 0;
    while (get_element(root, j)->occ == 0)
    {
        j = j+1;
    }
    Element* new_elem = get_element(root, j);
    end_tab->letter = new_elem->letter;
    end_tab->occ = new_elem->occ;
    curr = end_tab;

    j+=1;

    for(idx = 1; idx<cpt ; idx++)
    {
        while (get_element(root, j)->occ == 0)
        {
            j = j+1;
        }
        new_elem = get_element(root, j);
        curr->next = malloc(sizeof(Element));
        curr->next->letter = new_elem->letter;
        curr->next->occ = new_elem->occ;
        curr = curr->next;
        j+=1;
    }

    //Close the file
    free(root);
    fclose(file);
    return end_tab;
}

void print_occurences(Element* root)
{

    int idx = 0;
    Element* curr = root;
    printf("\n %c : %d", curr->letter, curr->occ);
    while(curr->next != NULL)
    {
        curr = curr->next;
        printf("\n %c : %d", curr->letter, curr->occ);
    }
}


// J : fonction qui trie un tableau de noeuds en fonction des occurrencess

void swap(Element* a, Element* b)
{
    Element* temp = malloc(sizeof(Element));
    temp->letter = a->letter;
    temp->occ = a->occ;
    a->letter = b->letter;
    a->occ = b->occ;
    b->letter = temp->letter;
    b->occ = temp->occ;

    free(temp);
}

// fast sorting technique


void quick_sorting (Element* root, int first, int last)
{
    int pivot, i, j;
    if(first < last)
    {
        pivot = first; //On definit le pivot au debut
        i = first;
        j = last;
        while(i<j)
        {
            while((get_element(root, i)->occ >=  get_element(root, pivot)->occ)&&(i<last))  // on cherche un element plus large que le pivot a gauche
            {
                i++;

            }
            while(get_element(root, j)->occ < get_element(root, pivot)->occ)   // on cherche un element plus petit que le pivot a droite
            {
                j--;
            }
            if(i<j)    // s'ils existent, on les echange
            {
                swap(get_element(root, i), get_element(root, j));

            }

        }

        swap(get_element(root, pivot), get_element(root, j));
        quick_sorting(root, first, j-1);  //on repete l'operation jusqu'a obtenir les deux sub-tables
        quick_sorting(root, j+1, last);
    }
}

void quick_sorting_caller(Element* root)
{
    quick_sorting(root, 0, list_size(root)-1);
}




