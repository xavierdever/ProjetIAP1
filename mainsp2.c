#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <io.h>
#include "Commande.h"
#include "Table.h"
#pragma warning(disable: 4996)



Table	*insert_enregistrement(Commande *info, Table *data, int nb_reg) {
	for (unsigned int i = 2, j = 0; i < info->NbChps; ++i, ++j) {
		strcpy(data->reg[nb_reg].enregistrement[j], info->champs[i]);
	}
	strcpy(data->reg[nb_reg].nomEnregistrement, data->reg[nb_reg].enregistrement[0]);
	return (data);
}

//fonction d'insertion des données dans la table
Table	*create_table(Table* data, Commande* info) {
	unsigned int	cpt, sch; // cpt pour les deux informations par champs , sch pour se deplacer dans les champs

	strcpy(data->nom, info->nomTable);										// copie du nom de la table recu en commande 
	data->nbChamps = atoi(info->champs[2]);									// copie du nombre de champs recu en commande

																			//boucle for pour remplir le tableau de structure Schema
	for (cpt = 3, sch = 0; cpt < info->NbChps; cpt += 2, sch += 1) {
		strcpy(data->schema[sch].champNom, info->champs[cpt]);				// copie du nom du champs
		strcpy(data->schema[sch].champType, info->champs[cpt + 1]);			// copie du type du champs
	}
	return (data);															// renvoi de la table de donnée chargée
}

//fonction d'affichage de la table de données
int	afficher_schema(Table *data, char nomTable[lgMot]) {
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


Commande*	recup_commande(Commande* info, char command[lgMax]) {
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
	return (info);
}

/* FONCTION PRINCIPALE */

int main() {
	Table*		data;			// déclaration d'un pointeur sur Table (structure)
	Commande*	info;			// déclaration d'un pointeur sur Commande (structure)
	char	command[lgMax];		// déclation d'un tableau de char stocker la commande
	int		ret, nb_reg = 0;	// ret pour le strcmp() , nb_reg pour le nombre d'enregistrement actuels
	_Bool	exist = false; 		// booléen pour existence d'une table


								//allocation mémoire
	data = malloc(sizeof(Table));
	info = malloc(sizeof(Commande));

	// démarage de la boucle infinie pour l'interpréteur de commande
	while (1) {
		printf(">");							// impression du prompt
		gets(command);							// recupération de la commande
		info = recup_commande(info, command);	// traitement de la commande

												//conditions pour vérifier quelle fonctions éxécuter
		if ((ret = strcmp(info->champs[0], "Create_table")) == 0) {
			//vérification non existence de la table
			if (data->nom != NULL && ((ret = strcmp(info->champs[1], data->nom)) == 0) || exist == true) {
				printf("Table existante\n");
				continue;
			}
			data = create_table(data, info);
			exist = true;
		}
		//affichage de la table
		else if ((ret = strcmp(info->champs[0], "Afficher_schema")) == 0) {
			afficher_schema(data, info->champs[1]);
		}
		//sortie du gestionnaire
		else if ((ret = strcmp(info->champs[0], "Exit")) == 0) {
			exit(0);
		}
		else if ((ret = strcmp(info->champs[0], "Insert_enregistrement")) == 0) {
			data = insert_enregistrement(info, data, nb_reg);
			++nb_reg;
		}
	}
	system("pause");
	return (0);
}