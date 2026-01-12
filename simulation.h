#ifndef SIMULATION_H
#define SIMULATION_H

#include "Capteur.h"
#include <math.h>

#define CONSO_BASE 0.01f

float cout_transmission(Capteur *c);
int transmettre_paquet(Capteur *c);
void afficher_etat(Capteur *c, long temps);

#endif

