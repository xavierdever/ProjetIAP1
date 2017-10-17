#include <stdlib.h>
#include <stdio.h>
#include <string.h>	
#include <stdbool.h>
#include <io.h>
#include "CommandeSp1.h"
#include "TableSp1.h"
#pragma warning(disable: 4996)

//fonction d'insertion des données dans la table
void create_table(Table* data, Commande* info) {
	unsigned int	cpt, sch; // cpt pour les deux informations par champs , sch pour se deplacer dans les champs

	strcpy(data->nom, info->nomTable);										// copie du nom de la table recu en commande 
	data->nbChamps = atoi(info->champs[2]);									// copie du nombre de champs recu en commande

																			//boucle for pour remplir le tableau de structure Schema
	for (cpt = 3, sch = 0; cpt < info->NbChps; cpt += 2, sch += 1) {
		strcpy(data->schema[sch].champNom, info->champs[cpt]);				// copie du nom du champs
		strcpy(data->schema[sch].champType, info->champs[cpt + 1]);			// copie du type du champs
	}
}

//fonction d'affichage de la table de données
int	afficher_schema(const Table *data, const char nomTable[lgMot]) {
	unsigned int i, ret; // i pour les schema, ret pour le strcmp()

						 // verification de l'existence de la table
	if ((ret = strcmp(data->nom, nomTable)) != 0) {
		printf("Table inconnue\n");
		return 1;
	}
	// impression du nom et du nombre de champs
	printf("%s %d\n", data->nom, data->nbChamps);
	//boucle d'impression des informations pour chaque champs
	for (i = 0; i < data->nbChamps - 1; i++) {
		printf("%s %s\n", data->schema[i].champNom, data->schema[i].champType);
	}
	return 0;
}

void recup_commande(Commande* info, char command[lgMax]) {
	unsigned int i, k = 0, j = 0;				// i pour parcourir l'entree utilisateur dans la boucle l.44, k indique les colonnes de la table champs, j indique les ligne de cette table

												// boucle de parcourt de l'entree utilisateur
	for (i = 0; i < strlen(command); i++) {
		// separation des arguments de l'entree utilisateur par les espaces
		if (command[i] == ' ') {
			info->champs[j][k] = '\0';			// ajout d'un signal de fin de chaine de caractere
			k = 0;								// mise a zero de k pour ecrire a partir de la premiere colonne de champs							
			j++;								// incrementation de j pour changer de ligne dans la table champs
		}

		// copie du caractere dans la table champs dans le cas où le caractere lu n'est pas un espace
		else {
			info->champs[j][k] = command[i];
			k++;
		}
	}
	info->champs[j][k] = '\0';
	strcpy(info->nomTable, info->champs[1]);
	info->NbChps = j + 1;
}

/* FONCTION PRINCIPALE */

int main() {
	Table		data;			// déclaration d'une variable structurée de type Table
	Commande	info;			// déclaration d'une variable de type Commande
	char	command[lgMax];		// déclation d'un tableau de char pour stocker la commande
	int		ret;				// ret pour le strcmp()
	_Bool	exist = false; 		// booléen pour existence d'une table

	// démarage de la boucle infinie pour l'interpréteur de commande
	while (1) {
		gets(command);							// recupération de la commande
		recup_commande(&info, command);			// traitement de la commande
												//conditions pour vérifier quelle fonctions éxécuter
		if ((ret = strcmp(info.champs[0], "Create_table")) == 0) {
			//vérification non existence de la table
			if (data.nom != NULL && ((ret = strcmp(info.champs[1], data.nom)) == 0) || exist == true) {
				printf("Table existante\n");
				continue;
			}
			create_table(&data, &info);
			exist = true;
		}
		//affichage de la table
		else if ((ret = strcmp(info.champs[0], "Afficher_schema")) == 0) {
			afficher_schema(&data, info.champs[1]);
		}
		//sortie du gestionnaire
		else if ((ret = strcmp(info.champs[0], "Exit")) == 0) {
			exit(0);
		}
	}
	system("pause");
	return (0);
}