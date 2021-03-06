#pragma once
#pragma once
#ifndef COMMANDE_H
#define COMMANDE_H

#include "TableSp1.h"

/* FICHIER EN TETE INFORMATIONS COMMAND*/

// structure pour stocker les informations

typedef struct {
	char	nomTable[lgMot + 1];
	unsigned int NbChps;
	char	champs[max_champs][lgMot + 1];
}Commande;

void recup_commande(Commande* info, char command[lgMax]);

#endif COMMAND_H
