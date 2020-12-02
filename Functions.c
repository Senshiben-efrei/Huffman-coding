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
        printf("%c : %d -> ", actuel->letter, actuel->occ);
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

// G : fonction qui compresse un fichier texte
//     Le fichier d’entree ne sera pas modifie, un autre fichier, contenant le texte compresse sera cree







// I : fonction qui, par recherche dichotomique, ajoute a un tableau de nœuds une occurrence
//     quand le caractere a deja ete trouve, ou qui ajoute le nœud du caractere sinon

/*
int get_length(Element* root)
{
    //todo
}

Element* get_element(Element* root, int index)
{
    if ((root != NULL) && (index < 0))
    {
        for(int i=1; i<=index; i++)
        {
            if root[i]
            }
    }


}


Element* occurrence_dichotomique (char* text)      // To pass an entire array to a function, only the name of the array is passed as an argument
{

    if(strlen(text)>0)
    {
        int n_elements = 0;
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

*/

int MAX_TAB = 255;

List_Node* add_by_dichotomie_v2 (char* my_file)
{
    //Open the text file
    FILE* file = fopen(my_file, "r");
    if(file==NULL)
    {
        printf("\n OPENING ERROR : FILE MY_FILE \n");
        exit(EXIT_FAILURE);
    }

    //Create and initialize the tab
    Node** tab = malloc(MAX_TAB*sizeof(Node*));
    int idx = 0;
    for(idx=0; idx<MAX_TAB; idx++)
    {
        tab[idx] = malloc(sizeof(Node));
        tab[idx]->letter = idx;
        tab[idx]->occ = 0;
        tab[idx]->left = NULL;
        tab[idx]->right = NULL;
    }
    int cpt = 0;
    int curr_char = fgetc(file);
    int lower_bnd = 0;
    int upper_bnd = MAX_TAB-1;
    int idx = -1;
    int middle;

    //Add occurrences to my tab by dichotomy
    while(curr_char != EOF)
    {
        lower_bnd = 0;
        upper_bnd = MAX_TAB-1;
        idx = -1;
        while((lower_bnd<=upper_bnd)&&(idx == -1))
        {
            middle = (upper_bnd+lower_bnd)/2;
            if(curr_char < tab[middle]->letter)
            {
                upper_bnd = middle-1;
            }
            else if (curr_char > tab[middle]->letter)
            {
                lower_bnd = middle+1;
            }
            else
            {
                idx = middle;
            }
        }
        if(tab[idx]->occ == 0)
        {
            cpt += 1;
        }
        tab[idx]->occ += 1;
        curr_char = fgetc(file);
    }

    //Create the end tab (to return)
    Node** end_tab = malloc(cpt*sizeof(Node*));
    int j = 0;
    for(idx = 0; idx<cpt ; idx++)
    {
        while (tab[j]->occ == 0)
        {
            j = j+1;
        }
        end_tab[idx] = tab[j];
        j+=1;
    }

    List_Node* list_node = malloc(sizeof(List_Node));
    list_node->tab = end_tab;
    list_node->size_tab = cpt;
    //Close the file
    free(tab);
    fclose(file);
    return list_node;
}

void print_Tab_of_DoubleNode (List_Node* list)
{

    int idx = 0;
    for (idx = 0 ; idx<list->size_tab ; idx++)
    {
        printf("\n%c : %d", list->tab[idx]->letter, list->tab[idx]->occ);
    }
}


// J : fonction qui trie un tableau de noeuds en fonction des occurrencess

void swap(Node* a, Node* b)
{
    Node* temp = malloc(sizeof(Node));
    temp->left = a->left;
    temp->right = a->right;
    temp->letter = a->letter;
    temp->occ = a->occ;

    a->left = b->left;
    a->right = b->right;
    a->letter = b->letter;
    a->occ = b->occ;

    b->left = temp->left;
    b->right = temp->right;
    b->letter = temp->letter;
    b->occ = temp->occ;

    free(temp);
}

// fast sorting technique


void quick_sorting (List_Node* list, int first, int last)
{
    Node** tab = list->tab;
    int pivot, i, j;
    if(first < last)
    {
        pivot = first; //On definit le pivot au debut
        i = first;
        j = last;
        while(i<j)
        {
            while((tab[i]->occ >=  tab[pivot]->occ)&&(i<last))  // on cherche un element plus large que le pivot a gauche
            {
                i++;
            }
            while(tab[j]->occ < tab[pivot]->occ)   // on cherche un element plus petit que le pivot a droite
            {
                j--;
            }
            if(i<j)    // s'ils existent, on les echange
            {
                swap(tab[i], tab[j]);
            }
        }
        swap(tab[pivot], tab[j]);
        quick_sorting(list, first, j-1);  //on repete l'operation jusqu'a obtenir les deux sub-tables
        quick_sorting(list, j+1, last);
    }
}

void quick_sorting_caller(List_Node* list)
{
    quick_sorting(list, 0, (list->size_tab)-1);
}




