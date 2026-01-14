#include "blackbox.h"
#include <math.h>
#include <ctype.h>

// Calcul de la température du moteur
float calculer_temperature(float temp_actuelle, float vitesse, float dt) {
    const float TEMP_AMBIANTE = 20.0f;
    const float TAUX_CHAUFFE = 0.05f;
    const float TAUX_REFROIDISSEMENT = 0.03f;

    float chauffe = vitesse * TAUX_CHAUFFE * dt;
    float refroidissement = (temp_actuelle - TEMP_AMBIANTE) * TAUX_REFROIDISSEMENT * dt;
    float nouvelle_temp = temp_actuelle + chauffe - refroidissement;

    if (nouvelle_temp < TEMP_AMBIANTE) {
        nouvelle_temp = TEMP_AMBIANTE;
    }

    return nouvelle_temp;
}

// Affichage de l'état du véhicule
void afficher_etat(BoiteNoire *b, float v, float t) {
    printf("\n");

    printf("  TABLEAU DE BORD\n");

    printf("  Vitesse          : %.1f km/h\n", v);
    printf("  Temperature      : %.1f %cC", t,248);

    if (t > 100.0f) {
        printf(" ALERTE");
    }
    printf("\n");
    printf("  Memoire utilisee : %d/10 frames\n", b->nb_frames);

}

// Simulation principale du véhicule
void simuler_vehicule(BoiteNoire *b) {
    float vitesse = 0.0f;
    float temperature = 20.0f;
    float dt = 1.0f;
    int secondes = 0;


    printf("  SIMULATION BOITE NOIRE - DEMARRAGE    \n");


    while (1) {
        secondes++;
        printf("\n\n>>> Seconde %d <<<\n", secondes);

        afficher_etat(b, vitesse, temperature);

        printf("\nAction : [A]Accelerer | [F]Freiner | [Q]Quitter : ");
        char action;
        scanf(" %c", &action);
        action = toupper(action);

        switch (action) {
            case 'A':
                vitesse += 20.0f;
                if (vitesse > 200.0f) vitesse = 200.0f;
                printf(" Acceleration : %.1f km/h\n", vitesse);
                break;
            case 'F':
                vitesse -= 30.0f;
                if (vitesse < 0.0f) vitesse = 0.0f;
                printf(" Freinage : %.1f km/h\n", vitesse);
                break;
            case 'Q':
                printf("\n Arret demande par l'utilisateur\n");
                enregistrer_cycle(b, vitesse, temperature);
                dump_memory(b);
                return;
            default:
                printf("Action invalide, maintient la vitesse\n");
        }

        temperature = calculer_temperature(temperature, vitesse, dt);
        enregistrer_cycle(b, vitesse, temperature);

        if (temperature > TEMP_CRITIQUE) {
            printf("\n");

            printf("    ALERTE CRITIQUE                   \n");
            printf("   SURCHAUFFE MOTEUR : %.1f%cC           \n", temperature,248);
            printf(" ARRET D'URGENCE                       \n");

            dump_memory(b);
            return;
        }

        if (vitesse == 0.0f && secondes > 1) {
            printf("\n Vehicule a l'arret complet\n");
            dump_memory(b);
            return;
        }
    }
}
