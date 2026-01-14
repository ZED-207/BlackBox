#include "blackbox.h"
#include <string.h>

// Création de la boîte noire
BoiteNoire* creer_boite_noire(void) {
    BoiteNoire *b = (BoiteNoire*)malloc(sizeof(BoiteNoire));
    if (!b) {
        fprintf(stderr, "Erreur allocation boite noire\n");
        exit(1);
    }
    b->debut = NULL;
    b->nb_frames = 0;
    return b;
}

// Enregistrement cyclique avec buffer circulaire
void enregistrer_cycle(BoiteNoire *b, float v, float t) {
    // 1. Créer une nouvelle frame
    Frame *nouvelle = (Frame*)malloc(sizeof(Frame));
    if (!nouvelle) {
        fprintf(stderr, "Erreur allocation frame\n");
        return;
    }
    
    nouvelle->timestamp = time(NULL);
    nouvelle->vitesse = v;
    nouvelle->temperature_moteur = t;
    nouvelle->suivant = NULL;
    
    // 2. Si la boîte est vide
    if (b->debut == NULL) {
        b->debut = nouvelle;
        b->nb_frames = 1;
        printf(" Enregistrement Frame [%ld] (Memoire : 1/10)\n", nouvelle->timestamp);
        return;
    }
    
    // 3. Rotation si buffer plein (10 frames)
    if (b->nb_frames >= MAX_FRAMES) {
        Frame *ancienne = b->debut;
        b->debut = b->debut->suivant;  // Recâbler AVANT le free
        free(ancienne);
        b->nb_frames--;
        printf("  Rotation : Frame ancienne ecrasee\n");
    }
    
    // 4. Ajouter à la fin de la liste
    Frame *courant = b->debut;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouvelle;
    b->nb_frames++;
    
    printf(" Enregistrement Frame [%ld] (Memoire : %d/10)\n", 
           nouvelle->timestamp, b->nb_frames);
}

// Libération de toute la mémoire
void liberer_boite_noire(BoiteNoire *b) {
    Frame *courant = b->debut;
    while (courant != NULL) {
        Frame *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    free(b);
    printf("\n Memoire liberee\n");
}