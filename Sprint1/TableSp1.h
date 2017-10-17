#pragma once
#ifndef TABLE H
#define TABLE_H

# define max_champs 25
# define lgMot 30
# define lgMax 80
# define max_reg 100

/* FICHIER EN TETE POUR TABLE DONNEES*/

// structure pour stocker les informations des champs
typedef	struct {
	char champNom[lgMot + 1];
	char champType[lgMot + 1];
}Champ;

//structure pour stocker la table de données, ses champs et ses informations
typedef struct {
	char	nom[lgMot + 1];
	Champ	schema[max_champs];
	unsigned char	nbChamps;
}Table;

#endif TABLE_H#pragma once

