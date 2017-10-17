
#pragma once

#ifndef TABLE H
#define TABLE_H

# define max_champs 25
# define lgMot 30
# define lgMax 80
# define max_reg 100

/* FICHIER EN TETE POUR TABLE DONNEES*/

// Strcuture pour stocker les enregistrements
typedef struct {
	char	nomEnregistrement[lgMot];
	char	enregistrement[max_champs][lgMot];
}Donnees;


// Structure pour stocker les informations des champs
typedef	struct {
	char champNom[lgMot + 1];
	char champType[lgMot + 1];
}Champ;

// Structure pour stocker la table de données, ses champs et ses informations
typedef struct {
	char	nom[lgMot + 1];
	Donnees	reg[max_reg];
	Champ	schema[max_champs];
	unsigned int nbChamps;
}Table;

#endif TABLE_H

