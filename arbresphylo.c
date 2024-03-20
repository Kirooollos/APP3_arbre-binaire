#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"
#include <stdbool.h>

info *parcour_arbre(arbre n,info *inf){
   if(n->gauche==NULL){
      if(n->droit==NULL){
      }
      else{
         parcour_arbre(n->droit,inf);
         inf->nb_carac ++;
         
      }
   }
   else if (n->droit==NULL){
      if (n->gauche==NULL){
         
      }
      else{
         parcour_arbre(n->gauche,inf);
         inf->nb_carac ++;
      }
      
   }
   else{
      parcour_arbre(n->gauche, inf);
      parcour_arbre(n->droit, inf);
      inf->nb_carac++;
      inf->nb_esp++;
   }
   return inf;
   
}





void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
   // Allouer de la mémoire pour la structure info
   info *inf = (info*)malloc(sizeof(info));

   if (inf == NULL) {
      fprintf(stderr, "Erreur d'allocation mémoire pour info.\n");
      exit(EXIT_FAILURE);
   }

   // Initialiser les membres de la structure info
   inf->nb_esp = 1;
   inf->nb_carac = 0;

   // Appeler la fonction parcour_arbre
   if (racine != NULL) {
      parcour_arbre(racine, inf);

      // Assigner les valeurs aux pointeurs en sortie
      *nb_esp = inf->nb_esp ;
      *nb_carac = inf->nb_carac;
   } else {
      *nb_esp = 0;
      *nb_carac = 0;
   }

   // Afficher les résultats
   printf("nombre de caractere : %d.\nnombre d'espece : %d. \n", *nb_carac, *nb_esp);

   // Libérer la mémoire allouée pour info
   free(inf);
}






/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{
   if(racine == NULL){
      return 1;
   }
   if(strcmp(racine->valeur,espece)==0){
      return 0 ;

   }else{
      if(rechercher_espece(racine->droit,espece,seq)==0 ){
         ajouter_tete(seq,racine->valeur);
         return 0 ;
      }
      if(rechercher_espece(racine->gauche,espece,seq)==0){
         return 0 ;
      }
           
   }
   return 1;

}

bool est_feuille(arbre a){
   if(a==NULL){
      return false;
   }
   if(a->gauche==NULL && a->droit==NULL){
      return true;
   }
   return false;

}

noeud *cree_new(char *val){
   noeud *n = (noeud*)malloc(sizeof(noeud));
   n->valeur=val;
   n->gauche=NULL;
   n->droit=NULL;
   return n;

}





/* ACTE III-A
Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {
   if((*a) == NULL){
      if(seq == NULL){
         (*a) = cree_new(espece);
         return 0;
      }else{
         (*a) = cree_new(seq->val);
         ajouter_espece(&((*a)->droit),espece,seq->suivant);
      }
   }
   if((*a)->valeur == NULL){
      if(seq != NULL){
         (*a)->valeur = malloc( strlen (seq->val) +1 );
         strcpy((*a)->valeur,seq->val);
         (*a)->gauche  = NULL;
         (*a)->droit = NULL;
         (*a)->droit = nouveau_noeud();
         
         ajouter_espece(&((*a)->droit),espece,seq->suivant); 
      }else{
         
         (*a)=cree_new(espece);
         
         return 0;
         
      }
      

   }
   else if(est_feuille(*a)){
      
      if(seq == NULL){
         //there is a espece already -> can't find diff
         printf("Ne peut ajouter %s: possède les mêmes caractères que %s.\n",espece,(*a)->valeur);
         return 1;
      }else{
     
         
         // add the existing element to the left and then replace the value with the next character
         char temp[100000];

         strcpy(temp,(*a)->valeur);
         
         (*a)->gauche = cree_new(temp);
         strcpy((*a)->valeur,seq->val);
         
         if(seq != NULL && seq->suivant == NULL){
            (*a)->droit = cree_new(espece);
         }else{
            
            (*a)->droit = nouveau_noeud();
            
            ajouter_espece(&((*a)->droit),espece,seq->suivant);
         }
      }

      
   }else
   {
      
      if(seq == NULL){
        
         if((*a)->gauche == NULL){
            (*a)->gauche = nouveau_noeud();
            ajouter_espece(&((*a)->gauche),espece,seq);

            return 0;
         }else{
            ajouter_espece(&((*a)->gauche),espece,seq);
         }
         
      }else{
         if(strcmp((*a)->valeur,seq->val)==0){
            ajouter_espece(&((*a)->droit),espece,seq->suivant);

         }else{
            ajouter_espece(&((*a)->gauche),espece,seq);
         }
      }
      
   }
   return 0;

}

/*ACTE III-B
 Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */

int hauteur_max(arbre a){
   int hg,hd;
   if(a==NULL){
      return -1;
   }
   hg=hauteur_max(a->gauche);
   hd=hauteur_max(a->droit);
   if(hg>hd){
      return hg+1;
   }
   else{
      return hd+1;
   }

}

void affiche_niveau(arbre a, int niveau,FILE* fout ){ //affiche les caracteristiques qui se trouvent dans un niveau donné 
    if (a == NULL)
      return;
   if (niveau == 1){
      if(!est_feuille(a)){
         fprintf(fout,"%s ", a->valeur);
         
      }
   }
   else if (niveau > 1)
   {
      affiche_niveau(a->gauche, niveau-1,fout);
      affiche_niveau(a->droit, niveau-1,fout);
   }
}



void afficher_par_niveau (arbre racine, FILE* fout) {
   //printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
   int h = hauteur_max(racine);
   int i;
   for (i=1; i<=h; i++)
   {
      affiche_niveau(racine, i,fout);
      fprintf(fout,"\n");

   }
}



// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
