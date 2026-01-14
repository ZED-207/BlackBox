#include "blackbox.h"

void afficher_menu(void)
{

    printf("\n");
    printf("      BLACKBOX - Enregistreur de Vol \n");
    printf("         Projet Groupe 4 - 2025 \n");
    printf("\n");
    printf("  1. Demarrer la simulation\n");
    printf("  2. Analyser le dernier crash\n");
    printf("  3. Quitter\n");
    printf("\n");
    printf("Choix : ");
}

int main(void)
{
    int choix;

    while (1)
        {
        afficher_menu();

        if (scanf("%d", &choix) != 1)
        {
            // Nettoyer le buffer en cas d'entrée invalide
            while (getchar() != '\n');
            printf("\n Entree invalide. Veuillez entrer un nombre.\n");
            continue;
        }

        switch (choix)
        {
            case 1:
                {
                // Créer une nouvelle boîte noire
                BoiteNoire *boite = creer_boite_noire();

                // Lancer la simulation
                simuler_vehicule(boite);

                // Libérer la mémoire
                liberer_boite_noire(boite);


                printf("\n");
                printf(" SIMULATION TERMINEE  \n");
                printf("\n");
                break;
            }

            case 2:
                // Analyser le fichier crash.bin
                analyser_crash();
                break;

            case 3:
                printf("\n Au revoir !\n\n");
                return 0;

            default:
                printf("\n  Choix invalide. Veuillez selectionner 1, 2 ou 3.\n");
        }
    }

    return 0;
}
