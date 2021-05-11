//rimuovo i warning no secure
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

/*
* Ruoli del personale
*/
enum ruoli {
	CAPOCANTIERE,
	CARPENTIERE,
	MURATORE,
	INTONACATORE,
	IDRAULICO,
	ELETTRICISTA,
	PIASTRELISTA,
	IMBIANCHINO
}ruolo_ricoperto;

/*
* Tipologia di ville
*/
enum tipologie {
	CONDOMINIO,
	VILLA,
	UFFICIO,
	INDUSTRIALE,
	COMMERCIALE,
	AUTORIMESSA,
	PARCO,
	SCUOLA
}tipologia;


/*
* Struttura dei cantieri
*/
typedef struct cantieri {
	char codice[4];
	char citta[21];
	char via[31];
	int n_civico;
	int altezza;
	int mq;
	enum orientamenti {
        N,//Nord
        NE,//NORD-EST
        E,//EST
        SE,//SUD-EST
        S,//SUD
        SO,//SUD-OVEST
        O,//OVEST
        NO//NORD-OVEST
    } o
    ;
	time_t inizio_lavori;
	time_t fine_lavori;
	enum tipologie t;
    enum stati{
        PIANIFICATO,
        ATTIVO,
        SOSPESO,
        CONCLUSO
    } s;
}cantiere;

/*
* Struttura dei dipendenti
*/
typedef struct dipendenti {
	char codice_fiscale[17];
	char nome[31];
	char cognome[31];
	time_t dataDiNascita;
	char genere;
	int anni_esperienza;
	enum ruoli ruolo;
}dipendenti;

int main(void) {
	FILE* fPtr;

	if ((fPtr = fopen("cantieri.csv", "r")) == NULL) {
		printf("Impossibile aprire il file!");

		return 0;
	}

	const int MAX_CANTIERI = 100;
	const int MAX_DIPENDENTI = 50;

	dipendenti d[50];
	cantiere c[100];

	char* token;
	char* line;

    fscanf(fPtr,"%s", &line);
	token = strtok(&line, ",");
	printf("OK: %s", line);

	return 0;
}
