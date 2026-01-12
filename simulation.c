#include "Simulation.h"

float cout_transmission(Capteur *c) {
    float distance = sqrt(c->x * c->x + c->y * c->y);
    return 0.05f + 0.01f * (distance * distance);
}

int transmettre_paquet(Capteur *c) {
    float cout = cout_transmission(c);
    if (c->batterie < 0) { c->batterie = 0;
            printf("    Condition d'arret : le capteur est considere comme mort");
        }
    if (c->buffer_tete == NULL || c->batterie < cout) {c->batterie -= CONSO_BASE; return 0;}

    Paquet *a_envoyer = c->buffer_tete;
    c->batterie -= cout;
    c->paquets_transmis++;
    c->buffer_tete = a_envoyer->suivant;
    if (c->buffer_tete == NULL) c->buffer_queue = NULL;

    printf("     Paquet ID %d transmis (cout: %.3f J)\n", a_envoyer->id, cout);
    free(a_envoyer);
    c->buffer_usage--;
    return 1;
}

void afficher_etat(Capteur *c, long temps) {
    printf("\n   ETAT DU CAPTEUR (Cycle %ld)    \n", temps);
    printf("Batterie: %.2f J | Transmis: %d\n", c->batterie, c->paquets_transmis);
}


