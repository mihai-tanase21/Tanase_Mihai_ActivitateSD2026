#include<stdio.h>
#include<malloc.h>

struct Film {
	int id;
	int durata;
	char* denumire;
	float buget;
	char varstaMinima;
};
struct Film initializare(int _id, int _durata, const char* _denumire, float _buget, char _varstaMinima) {
	struct Film s;
	s.id = _id;
	s.durata = _durata;
	s.denumire = malloc((strlen(_denumire) + 1) * sizeof(char));
	strcpy(s.denumire, _denumire);
	s.buget = _buget;
	s.varstaMinima = _varstaMinima;
	//initializare structura 
	return s;
}

struct Film copyFilm(struct Film s) {
	return initializare(s.id, s.durata, s.denumire, s.buget, s.varstaMinima);
}

void afisare(struct Film s) {
	printf("ID: %d\n", s.id);
	printf("Nume %s\n", s.denumire);
	printf("Durata in minute: %d\n", s.durata);
	printf("Buget: %.2f\n", s.buget);
	printf("Varsta minima: %d\n", s.varstaMinima);
	//afisarea tuturor atributelor.
}

void afisareVector(struct Film* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
		afisare(vector[i]);
	//afisarea elementelor din vector apeland functia afisare
}

struct Film* copiazaPrimeleNElemente(struct Film* vector, int nrElemente, int nrElementeCopiate) {
	struct Film* vectorNou = malloc(nrElementeCopiate * sizeof(struct Film));
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = copyFilm(vector[i]);
	}
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	//struct Film *vectorNou=NULL;

	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {
	for (int i = 0; i < *(nrElemente); i++) {
		free((*vector)[i].denumire);

	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
	//dezalocam elementele din vector si vectorul
}

void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMaxim, struct Film** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie)
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget < bugetMaxim)
			(*dimensiune)++;
	}
	(*vectorNou) = malloc((*dimensiune) * sizeof(struct Film));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[k].buget < bugetMaxim) {
			(*vectorNou)[k] = copyFilm(vector[i]);
			k++;
		}
	}
}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* numeCautat) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Film s;
	s.id = -1;
	s.denumire = NULL;
	for (int i = 0; i < nrElemente; i++) {
		if (!strcmp(vector[i].denumire, numeCautat))
			return vector[i];
	}

	return s;
}



int main() {
	struct Film f1 = initializare(1, 120, "Dune", 20.6, 14);
	afisare(f1);

	int nrFilme = 3;
	struct Film* filme = malloc(nrFilme * sizeof(struct Film));

	filme[0] = f1;
	*(filme + 1) = initializare(2, 360, "James Bond", 16.1, 12);
	filme[2] = initializare(3, 240, "Star Wars", 50.6, 12);

	afisareVector(filme, nrFilme);
	int nrFilmeCopiate = 2;

	struct Film* vectorNou;
	vectorNou = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);
	afisareVector(vectorNou, nrFilmeCopiate);

	dezalocare(&vectorNou, &nrFilmeCopiate);
	afisareVector(vectorNou, nrFilmeCopiate);

	struct Film* vectorIeftin;
	float prag = 50;
	int dimIeftin;
	copiazaAnumiteElemente(filme, nrFilme, prag, &vectorIeftin, &dimIeftin);
	afisareVector(vectorIeftin, dimIeftin);


	afisare(getPrimulElementConditionat(filme, nrFilme, "Dune"));

	dezalocare(&filme, &nrFilme);
	return 0;
}