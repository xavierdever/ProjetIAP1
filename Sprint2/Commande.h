#pragma once
#ifndef COMMANDE_H
#define COMMANDE_H

#include "Table.h"

/* FICHIER EN TETE INFORMATIONS COMMAND*/

// Structure pour stocker les informations

typedef struct {
	char	nomTable[lgMot + 1];
	unsigned int NbChps;
	char	champs[max_champs][lgMot + 1];
}Commande;

Commande*	recup_commande(Commande* info, char command[lgMax]);

#endif COMMAND_H