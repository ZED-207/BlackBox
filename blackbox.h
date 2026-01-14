#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 10
#define TEMP_CRITIQUE 110.0f
#define CRASH_FILE "crash.bin"

// Structure d'une trame d'enregistrement
typedef struct Frame {
    long timestamp;
    float vitesse;
    float temperature_moteur;
    struct Frame *suivant;
} Frame;

// Structure de la boîte noire
typedef struct {
    Frame *debut;
    int nb_frames;
} BoiteNoire;

// Prototypes - Gestion mémoire
BoiteNoire* creer_boite_noire(void);
void enregistrer_cycle(BoiteNoire *b, float v, float t);
void liberer_boite_noire(BoiteNoire *b);

// Prototypes - Simulation physique
void simuler_vehicule(BoiteNoire *b);
float calculer_temperature(float temp_actuelle, float vitesse, float dt);

// Prototypes - Fichiers binaires
void dump_memory(BoiteNoire *b);
void analyser_crash(void);

// Prototypes - Utilitaires
void afficher_etat(BoiteNoire *b, float v, float t);

#endif
