//rimuovo i warning no secure
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

/*
* Ruoli del personale
*/
enum ruoli {
	CAPOCANTIERE = 1,
	CARPENTIERE,
	MURATORE,
	INTONACATORE,
	IDRAULICO,
	ELETTRICISTA,
	PIASTRELISTA,
	IMBIANCHINO
}ruoli;

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

enum orientamenti {
    N,//Nord
    NE,//NORD-EST
    E,//EST
    SE,//SUD-EST
    S,//SUD
    SO,//SUD-OVEST
    O,//OVEST
    NO//NORD-OVEST
} orientamenti;

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
    enum orientamenti o;
    char* inizio_lavori;
	char* fine_lavori;
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
	char* dataDiNascita;
	char genere;
	int anni_esperienza;
	enum ruoli ruolo;
}dipendenti;

#define MAX_DIPENDENTI 50

//PROTOTIPI
int menu();
void inserisci_utente();
void modifica_utente(dipendenti* d[]);


int main(void) {
	FILE* fPtr;

	if ((fPtr = fopen("cantieri.csv", "r")) == NULL) {
		printf("Impossibile aprire il file!");

		return 0;
	}

    dipendenti  d[50];
    cantiere    c[100];

	int azione = menu();

    switch(azione){
        case 1://Nuovo utente
            inserisci_utente();
            break;
        case 2://Modifica di un utente
            modifica_utente(&d);
            break;
    }

	return 0;
}

int menu(){
    printf("***************************************\n");
    printf("1) Inserisci nuovo utente\n");
    printf("2) Modifica un utente\n");
    printf("***************************************\n");

    int azione;
    printf("Azione: ");
    scanf("%d", &azione);

    return azione;
}

/**
* PROBLEMA DI GESTIONE DELLA MEMORIA, CORREGGERE
*/
void modifica_utente(dipendenti* d[]){
    FILE* utentiFPtr;

	if ((utentiFPtr = fopen("utenti.csv", "r")) == NULL) {
		printf("Impossibile aprire il file degli gli utentu!");

		return;
	}

    char* token;
	char* line;

    for(int i=0;i<MAX_DIPENDENTI; i++){
        fscanf(utentiFPtr,"%s", &line);

        int cont = 2;
        token = strtok(&line, ",");
        strcpy(d[i]->codice_fiscale, token);
        while(token!=NULL){
            token = strtok(NULL, ",");

            switch(cont ++){
                case 2: strcpy(d[i]->nome, token);break;
                case 3: strcpy(d[i]->cognome, token);break;
                case 4: strcpy(d[i]->genere, token);break;
                case 5: {
                    switch(atoi(token)){
                        case 1: d[i]->ruolo = CAPOCANTIERE;break;
                        case 2: d[i]->ruolo = CARPENTIERE;break;
                        case 3: d[i]->ruolo = MURATORE;break;
                        case 4: d[i]->ruolo = INTONACATORE;break;
                        case 5: d[i]->ruolo = IDRAULICO;break;
                        case 6: d[i]->ruolo = ELETTRICISTA;break;
                        case 7: d[i]->ruolo = PIASTRELISTA;break;
                        case 8: d[i]->ruolo = IMBIANCHINO;break;
                    }
                }
                case 6: strcpy(d[i]->dataDiNascita, token);break;
                case 7: d[i]->anni_esperienza = atoi(token);break;

            }
        }
    }
}

/**
* Salva i dipendenti sul file.
*/
void inserisci_utente(){
    FILE* utentiFPtr;

	if ((utentiFPtr = fopen("utenti.csv", "a+")) == NULL) {
		printf("Impossibile aprire/creare il file degli gli utentu!");

		return;
	}

    char cf[17], nome[31], cognome[31], genere;
    char* data_n;
    int anni_esperienza, ruolo;

    printf("Codice Fiscale: ");
    scanf("%s", &cf);

    printf("Nome: ");
    scanf("%s", &nome);

    printf("Cognome: ");
    scanf("%s", &cognome);

    printf("Genere: ");
    fflush(stdin);//Pulisco il buffer
    scanf("%c", &genere);

    printf("Ruolo: ");
    printf("1: CAPOCANTIERE\n2: CARPENTIERE\n");
    printf("3: MURATORE\n4: INTONACATORE\n");
    printf("5: IDRAULICO\n6: ELETTRICISTA\n");
    printf("7: PIASTRELLISTA\n8: IMBIANCHINO\n");
    scanf("%D", &ruolo);

    printf("Data di nascita: ");
    scanf("%s", &data_n);

    printf("Anni di esperienza: ");
    scanf("%d", &anni_esperienza);

    //Salvo i dati sul file
    fprintf(utentiFPtr, "%s,%s,%s,%c,%d,%s,%d\n", cf, nome, cognome, genere, ruolo, &data_n, anni_esperienza);
}






















