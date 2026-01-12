#include "Capteur.h"

void init_capteur(Capteur *c, float batterie, float x, float y) {
    c->batterie = batterie;
    c->x = x; c->y = y;
    c->buffer_tete = NULL;
    c->buffer_queue = NULL;
    c->buffer_usage = 0;
    c->dernier_id = 1;
    c->paquets_transmis = 0;
    c->fichier_log = fopen("log.txt", "w");
    if (c->fichier_log) fprintf(c->fichier_log, "Temps\tBatterie\tPaquets en attente\tPaquets Transmis\n");
}

void ajouter_au_buffer(Capteur *c, Paquet *nouveau) {
    if (c->buffer_usage >= BUFFER_MAX) {
        Paquet *ancien = c->buffer_tete;
        printf("\n==============================================\n");
        printf("ALERTE : Memoire saturee.\n");
        printf("Suppression du paquet ID [%3d] (free)\n", ancien->id);
        printf("==============================================\n");
        c->buffer_tete = ancien->suivant;
        if (c->buffer_tete == NULL) c->buffer_queue = NULL;
        free(ancien);
        c->buffer_usage--;
    }
    if (c->buffer_tete == NULL) {
        c->buffer_tete = nouveau;
        c->buffer_queue = nouveau;
    } else {
        c->buffer_queue->suivant = nouveau;
        c->buffer_queue = nouveau;
    }
    c->buffer_usage++;
}

Paquet* creer_paquet(Capteur *c) {
    Paquet *nouveau = (Paquet*)malloc(sizeof(Paquet));

    if (!nouveau) return NULL;
    nouveau->id = c->dernier_id++;
    nouveau->valeur = (float)(rand() % 10001) / 100.0f;
    nouveau->timestamp = time(NULL);
    nouveau->suivant = NULL;
    return nouveau;
}

void liberer_capteur(Capteur *c) {
    Paquet *courant = c->buffer_tete;
    while (courant) {
        Paquet *suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    if (c->fichier_log) fclose(c->fichier_log);
}
void afficher_buffer(Capteur *c) {
    printf("\n   CONTENU DU BUFFER (%d/%d)  \n", c->buffer_usage, BUFFER_MAX);
    Paquet *courant = c->buffer_tete;
    int i = 1;
    while (courant != NULL) {
        printf("  %d. ID: [%3d] | Valeur: %6.2f\n", i++, courant->id, courant->valeur);
        courant = courant->suivant;
    }
    if (c->buffer_usage == 0) {
        printf("  (Buffer vide)\n");
    }
    printf("----------------------------------\n");
}

