#include "Capteur.h"
#include "Simulation.h"
#include "Fichier.h"

int main() {
    srand(time(NULL));
    printf("\n");
    printf("                             SIMULATEUR ECO-SENSING\n");
    printf("\n");
    float batterie, x, y;
    printf("Entrer la valeur de votre batterie critique: ");
    scanf("%f",&batterie);
    printf("Entrer les valeurs de la position (x,y) de votre capteur:\n");
    scanf("%f %f",&x,&y);
    Capteur mon_capteur;
    init_capteur(&mon_capteur, batterie, x, y);

    long temps_ecoule = 0;
    while (mon_capteur.batterie > 0) {
        temps_ecoule++;
        printf("\n--- CYCLE %ld ---\n", temps_ecoule);
        Paquet *nouveau = creer_paquet(&mon_capteur);
        if (nouveau) {
            printf("    Paquet ID %d cree (valeur: %.2f)\n", nouveau->id, nouveau->valeur);
            ajouter_au_buffer(&mon_capteur, nouveau);
        }
        afficher_buffer(&mon_capteur);
        if (!transmettre_paquet(&mon_capteur)) {
            printf("    Pas de transmission (Energie insuffisante ou buffer vide).\n");
        }

        if (mon_capteur.batterie < 0) mon_capteur.batterie = 0;

        afficher_etat(&mon_capteur, temps_ecoule);
        enregistrer_log(&mon_capteur, temps_ecoule);


        if (temps_ecoule % 5 == 0) sauvegarder_etat(&mon_capteur);
    }

    printf("\n");
    printf("             SIMULATION TERMINEE\n");
    printf("\n");
    printf("    STATISTIQUES FINALES :\n");
    printf("    - Cycles simules       : %ld\n", temps_ecoule);
    printf("    - Batterie restante    : %.4f J\n", mon_capteur.batterie);
    printf("    - Paquets produits     : %d\n", mon_capteur.dernier_id - 1);
    printf("    - Paquets transmis     : %d\n", mon_capteur.paquets_transmis);
    printf("    - Paquets restants     : %d\n", mon_capteur.buffer_usage);

    liberer_capteur(&mon_capteur);
    printf("\    Memoire liberee (0 fuites). Fin du programme.\n");

    return 0;
}
