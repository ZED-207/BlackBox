#include "blackbox.h"

// Sauvegarde d'urgence de la mémoire
void dump_memory(BoiteNoire *b) {
    printf("\n");
    printf("-------------------------------------------|\n");
    printf("|   DUMP MEMOIRE EN COURS...               |\n");
    printf("--------------------------------------------\n");

    FILE *f = fopen(CRASH_FILE, "wb");
    if (!f) {
        fprintf(stderr, "Erreur : Impossible de créer %s\n", CRASH_FILE);
        return;
    }

    fwrite(&b->nb_frames, sizeof(int), 1, f);

    Frame *courant = b->debut;
    int count = 0;
    while (courant != NULL) {
        fwrite(&courant->timestamp, sizeof(long), 1, f);
        fwrite(&courant->vitesse, sizeof(float), 1, f);
        fwrite(&courant->temperature_moteur, sizeof(float), 1, f);
        courant = courant->suivant;
        count++;
    }

    fclose(f);
    printf(" %d frames sauvegardees dans %s\n", count, CRASH_FILE);
    printf(" Analyse post-mortem disponible\n");
}

// Analyse du fichier crash
void analyser_crash(void) {
    printf("\n");
    printf("--------------------------------------------\n");
    printf("|   ANALYSE POST-MORTEM                     |\n");
    printf("|-------------------------------------------|\n");

    FILE *f = fopen(CRASH_FILE, "rb");
    if (!f) {
        fprintf(stderr, "Erreur : Fichier %s introuvable\n", CRASH_FILE);
        fprintf(stderr, "Aucun crash enregistré.\n");
        return;
    }

    int nb_frames;
    fread(&nb_frames, sizeof(int), 1, f);

    if (nb_frames == 0) {
        printf("Aucune donnée enregistrée.\n");
        fclose(f);
        return;
    }

    printf("\n Analyse des %d dernières secondes :\n\n", nb_frames);

    float somme_vitesse = 0.0f;
    float temp_max = 0.0f;

    printf("%-12s | %-12s | %-15s\n", "Timestamp", "Vitesse", "Température");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < nb_frames; i++) {
        long timestamp;
        float vitesse, temperature;

        fread(&timestamp, sizeof(long), 1, f);
        fread(&vitesse, sizeof(float), 1, f);
        fread(&temperature, sizeof(float), 1, f);

        printf("%-12ld | %8.1f km/h | %10.1f C",
               timestamp, vitesse, temperature);

        if (temperature > 100.0f) {
            printf(" erreur");
        }
        printf("\n");

        somme_vitesse += vitesse;
        if (temperature > temp_max) {
            temp_max = temperature;
        }
    }

    fclose(f);

    float vitesse_moyenne = somme_vitesse / nb_frames;

    printf("\n");
    printf("-------------------------------------------\n");
    printf("  STATISTIQUES\n");
    printf("-------------------------------------------\n");
    printf("  Vitesse moyenne    : %.2f km/h\n", vitesse_moyenne);
    printf("  Température max    : %.2f %cC", temp_max,248);
    if (temp_max > TEMP_CRITIQUE) {
        printf(" [CRITIQUE]");
    }
    printf("\n");
    printf("----------------------------------------\n");
}
