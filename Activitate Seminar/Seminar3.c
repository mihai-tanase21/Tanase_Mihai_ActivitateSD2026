#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
	printf("\nID Masina: %d", masina.id);
	printf("\nNr usi: %d", masina.nrUsi);
	printf("\nPret: %f", masina.pret);
	printf("\nModel: %s", masina.model);
	printf("\nNumele Soferului: %s", masina.numeSofer);
	printf("\nSerie: %c", masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	(*nrMasini)++;
	Masina* aux = malloc(sizeof(Masina) * (*nrMasini));
	for (int i = 0; i < (*nrMasini) - 1; i++) {
		aux[i] = (*masini)[i]; //shallow copy
	}
	aux[(*nrMasini) - 1] = masinaNoua;
	free(*masini);
	*masini = aux;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;

	char linie[50];
	fgets(linie, 50, file);
	char delimitatori[3] = ",\n";
	Masina masina;
	masina.id = atoi(strtok(linie, delimitatori));
	masina.nrUsi = atoi(strtok(NULL, delimitatori));
	masina.pret = atof(strtok(NULL, delimitatori));

	char* model = strtok(NULL, delimitatori);
	masina.model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);

	char* nume = strtok(NULL, delimitatori);
	masina.numeSofer = malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(masina.numeSofer, nume);

	char* serie = strtok(NULL, delimitatori);
	masina.serie = serie[0];

	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	*nrMasiniCitite = 0;
	Masina* masini = NULL;

	while (!feof(f)) {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(f));
	}

	fclose(f);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0; i < nrMasini; i++) {
		free((*vector)[i]->model);
		free((*vector)[i]->numeSofer);
	}
	free(*vector);
}

int main() {

	int nr = 0;
	Masina* masini = citireVectorMasiniFisier("masini.txt", &nr);
	afisareVectorMasini(masini, nr);

	return 0;
}