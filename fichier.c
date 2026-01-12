#include "Fichier.h"

void enregistrer_log(Capteur *c, long temps) {
    if (c->fichier_log) {
        fprintf(c->fichier_log, "%ld\t\t%.2f\t\t%d\t\t\t\t\t%d\n",temps, c->batterie, c->buffer_usage, c->paquets_transmis);
    }
}

void sauvegarder_etat(Capteur *c) {
    FILE *f = fopen("save.bin", "wb");
    if (!f) return;
    fwrite(&c->batterie, sizeof(float), 1, f);
    fwrite(&c->paquets_transmis, sizeof(int), 1, f);
    fclose(f);
}

