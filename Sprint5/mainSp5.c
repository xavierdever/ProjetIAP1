/* Nom du ficher :			Auteurs :
Groupe :				Date de création :
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CommandeSp5.h"
#include "TableSp5.h"

#pragma warning(disable: 4996)

typedef enum {DATE, FLOAT, INT, TEXT, ERR}Type;

void convert_to_date(const char dateStr[lgMot + 1], Date* date) {
	char mot[lgMot + 1];

	date->jour = atoi(strncpy(mot, dateStr, 2)); 
	date->mois = atoi(strncpy(mot, dateStr+3, 2));
	date->annee = atoi(strncpy(mot, dateStr+6, 4));
}

void	select_date(Table* data, const Commande* info) {
	unsigned int d = 0, reg_num = 0;
	Date	datedeb, datefin;
	convert_to_date(info->champs[2], &datefin);
	convert_to_date(info->champs[3], &datedeb);

	for (; d < data->nb_reg && reg_num < data->nb_reg; ++d, ++reg_num) {
		if ((datedeb.annee < data->reg[reg_num].date[d].annee) &&
			(datefin.annee > data->reg[reg_num].date[d].annee)) {
			//print
		}
		else if ((datedeb.annee == data->reg[reg_num].date[d].annee) ||
			(datefin.annee == data->reg[reg_num].date[d].annee)) {
			if ((datedeb.mois < data->reg[reg_num].date[d].mois) ||
				(datefin.mois > data->reg[reg_num].date[d].mois)) {
				//print
			}
			else if ((datedeb.mois == data->reg[reg_num].date[d].mois) ||
				(datefin.mois == data->reg[reg_num].date[d].mois)) {
				if ((datedeb.jour < data->reg[reg_num].date[d].jour) ||
					(datefin.jour > data->reg[reg_num].date[d].jour)) {
					//print
				}
			}
		}
	}
}

Type	get_type(char nomChamps[lgMot+1], Table* data) {

	for (unsigned int i = 0; i < data->nbChamps; ++i) {
		if (strcmp(nomChamps, data->schema[i].champNom) == 0) {
			if (strcmp(data->schema[i].champType, "DATE") == 0) {
				return DATE;
			}
			else if (strcmp(data->schema[i].champType, "TEXT") == 0) {
				return TEXT;
			}
			else if (strcmp(data->schema[i].champType, "INT") == 0) {
				return INT;
			}
			else if (strcmp(data->schema[i].champType, "FLOAT") == 0) {
				return FLOAT;
			}
		}
	}
	return ERR;
}

void select_enregistrement(Table* data, Commande* info) {
	Type	ret;

	ret = get_type(info->champs[2], data);
	switch (ret) {
		case DATE:
			select_date(data, info);
			break;
		case TEXT:
			printf("type text\n");
			break;
		case INT:
			printf("type INT\n");
			break;
		case FLOAT:
			printf("type FLOAT\n");
			break;
		default:
			printf("err\n");
			break;
	}
}

// Fonction de suppression d'un enregistrement
// [in] data -> table de donnée stockant les enregistrements
// [in] info -> informations sur la commande
void delete_enregistrement(Table* data, int nb_reg, const Commande* info) {
	int tmp = atoi(info->champs[2]) - 1;
	if (strcmp(data->nom, info->champs[1]) != 0) {
		printf("table inconnue\n");
		return;
	}
	for (tmp; tmp < nb_reg; tmp++) {
		data->reg[tmp] = data->reg[tmp + 1];
	}
}

//	Fonction d'affichage d'un seul enregistrement
// [in] data -> table de donnée stockant les enregistrements
// [in] info -> informations sur la commande
void afficher_enregistrement(const Table *data, Commande * info, unsigned int reg_num) {
	int	d = 0;
	if (strcmp(data->nom, info->champs[1]) != 0) {
		printf("table inconnue\n");
		return;
	}
	printf("%d ", reg_num);
	for (int i = 0; i < data->nbChamps; ++i) {
		printf("%s ", data->schema[i].champType);
		if (strcmp(data->schema[i].champType, "DATE") == 0) {
			printf("%u/%02d/%d ", data->reg[reg_num - 1].date[d].jour,
				data->reg[reg_num - 1].date[d].mois,
				data->reg[reg_num - 1].date[d].annee);
			d++;
		}
		else
			printf("%s ", data->reg[reg_num - 1].enregistrement[i]);
	}
	printf("\n");
}

//	Fonction d'insertion de l'enregistrement
// [in-out] data -> table de donnée qui va stocker les enregistrements
// [in] info -> informations séparées de la commande
void insert_enregistrement(const Commande *info, Table *data, const int nb_reg) {
	int d = 0;
	char mot[lgMot + 1];
	if (strcmp(data->nom, info->champs[1]) != 0) {
		printf("table inconnue\n");
		return;
	}
	for (unsigned int i = 2, j = 0; i < info->NbChps; ++i, ++j) {
		if (strncmp(data->schema[j].champType, "DATE", 4) == 0) {
			convert_to_date(info->champs[i], &data->reg[nb_reg].date[d]);
			d++;
		}
		else
			strcpy(data->reg[nb_reg].enregistrement[j], info->champs[i]);
	}
	strcpy(data->reg[nb_reg].nomEnregistrement,
		data->reg[nb_reg].enregistrement[0]);
}

// Fonction d'affichage de l'enregistrement
// [in] data -> table donnée stockant les enregistrements
// [in] nb_reg -> nombre total d'enregistrements actuels
void afficher_enregistrements(const Table* data, const Commande* info, const int nb_reg) {
	int d = 0;
	if (strcmp(data->nom, info->champs[1]) != 0) {
		printf("table inconnue\n");
		return;
	}
	for (int tmp = 0; tmp < nb_reg; tmp++) {								// tmp sert a enumerer les enregistrements, nb_reg etant le nombre d'enregistrements
		printf("%d ", tmp + 1);
		for (int aux = 0; aux < data->nbChamps; aux++) {					// aux sert a enumerer les champs a afficher
			printf("%s ", data->schema[aux].champType);						// On affiche le type de l'enregistrement
			if (strcmp(data->schema[aux].champType, "DATE") == 0) {
				printf("%u/%02u/%d ", data->reg[tmp].date[aux].jour,
					data->reg[tmp].date[aux].mois,
					data->reg[tmp].date[aux].annee);
			}
			printf("%s ", data->reg[tmp].enregistrement[aux]);				// On affiche le nom de l'enregistrement en question
		}
		printf("\n");
	}
}

// Fonction d'insertion des données dans la table
// [out] data -> table de donnée qui va être "remplie"
// [in] info -> informations séparées de la commande
void	create_table(Table* data, const Commande* info) {
	unsigned int	cpt, sch, ret;											// cpt pour les deux informations par champs , sch pour se deplacer dans les champs

	if (data->nom != NULL && ((ret = strcmp(info->champs[1], data->nom)) == 0)) { // Vérification non existence de la table
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

// Fonction d'affichage de la table de données
// [in] data -> table de donnée
// [in] nomTable -> nom de la table à afficher
int afficher_schema(const Table *data, const char nomTable[lgMot]) {
	unsigned int i, ret;													// i pour les schema, ret pour le strcmp()
																			// Verification de l'existence de la table
	if ((ret = strcmp(data->nom, nomTable)) != 0) {
		printf("Table inconnue\n");
		return 1;
	}
	printf("%s %d\n", data->nom, data->nbChamps);							// Impression du nom et du nombre de champs
	for (i = 0; i < data->nbChamps; i++) {									// Boucle d'impression des informations pour chaque champs
		printf("%s %s\n", data->schema[i].champNom, data->schema[i].champType);
	}
	return 0;
}


// Fonction de récupération de la commande et de séparation des informations
// [in-out] info -> informations sur la commandes
// [in] command -> commande récupérée depuis l'entrée standard
void recup_commande(Commande* info, const char command[lgMax]) {
	unsigned int i, k = 0, j = 0;				// i pour parcourir l'entree utilisateur dans la boucle l.44, k indique les colonnes de la table champs, j indique les ligne de cette table

												// boucle de parcourt de l'entree utilisateur
	for (i = 0; i < strlen(command); i++) {
		// separation des arguments de l'entree utilisateur par les espaces
		if (command[i] == ' ') {
			while (command[i] == ' ' && command[i + 1] == ' ')
				i++;
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
_Bool delete_table(Table* data) {
	data->nb_reg = 0;
	return false;
}

/* FONCTION PRINCIPALE */

int main() {
	Table		data;														// Déclaration d'un pointeur sur Table (structure)
	Commande	info;														// Déclaration d'un pointeur sur Commande (structure)
	char	command[lgMax];													// Déclation d'un tableau de char stocker la commande
	int		ret;															// ret pour le strcmp() , nb_reg pour le nombre d'enregistrement actuels
	_Bool	exist = false; 													// Booléen pour existence d'une table
																			// Démarage de la boucle infinie pour l'interpréteur de commande
	while (1) {
		gets(command);														// Recupération de la commande
		recup_commande(&info, command);										// Traitement de la commande
																			// Conditions pour vérifier quelle fonctions éxécuter
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
			afficher_enregistrements(&data, &info, data.nb_reg);
		}
		// Afficher un enregistrement
		else if ((ret = strcmp(info.champs[0], "Afficher_enregistrement")) == 0) {
			afficher_enregistrement(&data, &info, atoi(info.champs[2]));
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