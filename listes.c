#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
   //printf ("<<<<< À faire: fonction init_liste_vide fichier " __FILE__ "\n >>>>>");
    /* a completer */
    L->tete=NULL;
}

void liberer_liste(liste_t* L) {
   //printf ("<<<<< À faire: fonction liberer_liste fichier " __FILE__ "\n >>>>>");
    /* a completer */
     if(L !=NULL){
        cellule_t *prev = L->tete;
        cellule_t *temp ;
        while (prev!=NULL){
            temp = prev;
            prev = prev->suivant;
            free(temp);
            
        }
    }
}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
   //printf ("<<<<< À faire: fonction ajouter_tete fichier " __FILE__ " >>>>>\n");
    /* a completer */
    if(L == NULL){
        return 1;
    }
    cellule_t *new;
    new = malloc (sizeof(cellule_t));
    new->val = c;
    new->suivant = L->tete;
    L->tete = new;
    return 0;
}


