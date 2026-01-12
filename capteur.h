#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_MAX 5

typedef struct Paquet {
    int id;
    float valeur;
    long timestamp;
    struct Paquet *suivant;
} Paquet;

typedef struct Capteur {
    float batterie;
    float x, y;
    Paquet *buffer_tete;
    Paquet *buffer_queue;
    int buffer_usage;
    int dernier_id;
    int paquets_transmis;
    FILE *fichier_log;
} Capteur;

void init_capteur(Capteur *c, float batterie, float x, float y);
void liberer_capteur(Capteur *c);
Paquet* creer_paquet(Capteur *c);
void ajouter_au_buffer(Capteur *c, Paquet *nouveau);
void afficher_buffer(Capteur *c);

#endif

