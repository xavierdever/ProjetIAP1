#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CommandeSp4.h"
#include "TableSp4.h"
#pragma warning(disable: 4996)

// Fonction de suppression d'un enregistrement
// [in] data -> table de donn�e stockant les enregistrements
// [in] info -> informations sur la commande
void delete_enregistrement(Table* data, int nb_reg, const Commande* info) {
	int tmp = atoi(info->champs[2]) - 1;
	for (tmp; tmp < nb_reg; tmp++) {
		data->reg[tmp] = data->reg[tmp + 1];
	}
}

//	Fonction d'affichage d'un seul enregistrement
// [in] data -> table de donn�e stockant les enregistrements
// [in] info -> informations sur la commande
void afficher_enregistrement(const Table *data, const Commande *info) {
	int	reg_num;

	reg_num = atoi(info->champs[2]);
	printf("%d ", reg_num);
	for (int i = 0; i < data->nbChamps; ++i) {
		printf("%s ", data->schema[i].champType);
		printf("%s ", data->reg[reg_num - 1].enregistrement[i]);
	}
	printf("\n");
}

//	Fonction d'insertion de l'enregistrement
// [in-out] data -> table de donn�e qui va stocker les enregistrements
// [in] info -> informations s�par�es de la commande
void insert_enregistrement(const Commande *info, Table *data, const int nb_reg) {
	for (unsigned int i = 2, j = 0; i < info->NbChps; ++i, ++j) {
		strcpy(data->reg[nb_reg].enregistrement[j], info->champs[i]);
	}
	strcpy(data->reg[nb_reg].nomEnregistrement,
		data->reg[nb_reg].enregistrement[0]);
}

// Fonction d'affichage de l'enregistrement
// [in] data -> table donn�e stockant les enregistrements
// [in] nb_reg -> nombre total d'enregistrements actuels

void afficher_enregistrements(const Table* data, const int nb_reg) {
	for (int tmp = 0; tmp < nb_reg; tmp++) {								// tmp sert a enumerer les enregistrements, nb_reg etant le nombre d'enregistrements
		printf("%d ", tmp + 1);
		for (int aux = 0; aux < data->nbChamps; aux++) {					// aux sert a enumerer les champs a afficher
			printf("%s ", data->schema[aux].champType);						// On affiche le type de l'enregistrement
			printf("%s ", data->reg[tmp].enregistrement[aux]);				// On affiche le nom de l'enregistrement en question
		}
		printf("\n");
	}
}

// Fonction d'insertion des donn�es dans la table
// [in-out] data -> table donn�e qui va �tre "remplie"
// [in] info -> informations s�par�es de la commande

void	create_table(Table* data, const Commande* info) {
	unsigned int	cpt, sch, ret;											// cpt pour les deux informations par champs , sch pour se deplacer dans les champs
	data->nb_reg = 0;
	if (data->nom != NULL && ((ret = strcmp(info->champs[1], data->nom)) == 0)) { // V�rification non existence de la table
		printf("Table existante\n");
		return;
	}
	strcpy(data->nom, info->nomTable);										// Copie du nom de la table recu en commande 
	data->nbChamps = atoi(info->champs[2]);									// Copie du nombre de champs recu en commande
	for (cpt = 3, sch = 0; cpt < info->NbChps; cpt += 2, sch += 1) {		// Boucle for pour remplir le tableau de structure Schema
		strcpy(data->schema[sch].champNom, info->champs[cpt]);				// Copie du nom du champs
		strcpy(data->schema[sch].champType, info->champs[cpt + 1]);			// Copie du type du champs
	}
}

// Fonction d'affichage de la table de donn�es
// [in] data -> table de donn�e
// [in] nomTable -> nom de la table � afficher
int afficher_schema(const Table *data, const char nomTable[lgMot]) {
	unsigned int i, ret;													// i pour les schema, ret pour le strcmp()
																			// Verification de l'existence de la table
	if ((ret = strcmp(data->nom, nomTable)) != 0) {
		printf("Table inconnue\n");
		return 1;
	}
	printf("%s %d\n", data->nom, data->nbChamps);							// Impression du nom et du nombre de champs
																			// Boucle d'impression des informations pour chaque champs
	for (i = 0; i < data->nbChamps - 1; i++) {
		printf("%s %s\n", data->schema[i].champNom, data->schema[i].champType);
	}
	return 0;
}

// Fonction de r�cup�ration de la commande et de s�paration des informations
// [in-out] info -> informations sur la commandes
// [in] command -> commande r�cup�r�e depuis l'entr�e standard
void recup_commande(Commande* info, const char command[lgMax]) {
	unsigned int i, k = 0, j = 0;											// i pour parcourir l'entree utilisateur dans la boucle l.44, k indique les colonnes de la table champs, j indique les ligne de cette table
																			// Boucle de parcourt de l'entree utilisateur
	for (i = 0; i < strlen(command); i++) {
		// Separation des arguments de l'entree utilisateur par les espaces
		if (command[i] == ' ') {
			info->champs[j][k] = '\0';										// Ajout d'un signal de fin de chaine de caractere
			k = 0;															// Mise a zero de k pour ecrire a partir de la premiere colonne de champs							
			j++;															// Incrementation de j pour changer de ligne dans la table champs
		}
		else {
			info->champs[j][k] = command[i];								// Copie du caractere dans la table champs dans le cas o� le caractere lu n'est pas un espace
			k++;
		}
	}
	info->champs[j][k] = '\0';
	strcpy(info->nomTable, info->champs[1]);
	info->NbChps = j + 1;
	return;
}

_Bool delete_table(Table* data) {
	data->nb_reg = 0;
	return false;
}

/* FONCTION PRINCIPALE */

int main() {
	Table		data;														// D�claration d'un pointeur sur Table (structure)
	Commande	info;														// D�claration d'un pointeur sur Commande (structure)
	char	command[lgMax];													// D�clation d'un tableau de char stocker la commande
	int		ret;															// ret pour le strcmp() , nb_reg pour le nombre d'enregistrement actuels
	_Bool	exist = false; 													// Bool�en pour existence d'une table


																			// D�marage de la boucle infinie pour l'interpr�teur de commande
	while (1) {
		gets(command);														// Recup�ration de la commande
		recup_commande(&info, command);										// Traitement de la commande
																			// Conditions pour v�rifier quelle fonctions �x�cuter
		if ((ret = strcmp(info.champs[0], "Create_table")) == 0 && exist != true) {
			create_table(&data, &info);
			exist = true;
		}
		// Affichage de la table
		else if ((ret = strcmp(info.champs[0], "Afficher_schema")) == 0) {
			afficher_schema(&data, info.champs[1]);
		}
		// Ajout d'enregistrement
		else if ((ret = strcmp(info.champs[0], "Insert_enregistrement")) == 0) {
			insert_enregistrement(&info, &data, data.nb_reg);
			data.nb_reg++;
		}
		// Afficher les enregistrements
		else if ((ret = strcmp(info.champs[0], "Afficher_enregistrements")) == 0) {
			afficher_enregistrements(&data, data.nb_reg);
		}
		// Afficher un enregistrement
		else if ((ret = strcmp(info.champs[0], "Afficher_enregistrement")) == 0) {
			afficher_enregistrement(&data, &info);
		}
		// Supprimer un enregistrement
		else if ((ret = strcmp(info.champs[0], "Delete_enregistrement")) == 0) {
			delete_enregistrement(&data, data.nb_reg, &info);
			data.nb_reg--;
		}
		// Supprime une table
		else if ((ret = strcmp(info.champs[0], "Delete_table")) == 0) {
			exist = delete_table(&data);
		}
		else if ((ret = strcmp(info.champs[0], "Select_enregistrement")) == 0) {
			select_enregistrement(&data, &info);
		}
		// Sortie du gestionnaire
		else if ((ret = strcmp(info.champs[0], "Exit")) == 0) {
			exit(0);
		}
	}
	system("pause");
	return (0);
}