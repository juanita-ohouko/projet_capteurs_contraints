#ifndef FICHIER_H
#define FICHIER_H

#include "Capteur.h"

void enregistrer_log(Capteur *c, long temps);
void sauvegarder_etat(Capteur *c);

#endif
