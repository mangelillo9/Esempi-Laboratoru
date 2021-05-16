/****************************************************************************
 * Copyright (C) 2021 by Mattia Leonardo Angelillo                          *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file main.h
 * @author Mattia Leonardo Angelillo
 * @date 14/05/2021
 * @brief Il file contiene la gestione dei cantieri di una società
 */

//rimuovo i warning no secure
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* sono i ruoli del personale
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

/**
* Sono le tipologie di ville
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

/**
* Sono gli orientamenti che può avere una villa
*/
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

/**
* Questa struct definisce le informazioni
* del singolo cantiere
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


/**
* Struttura dei dipendenti
*/
typedef struct dipendenti {
    /**
    * Questa variabile serve a controllare
    * se una determinata posizione dell'array
    * è stata popolata.
    * Il valore -1 indica che non è stato popolato
    * Il valore 0 indica che è stato popolato
    */
    int controllo;
	char codice_fiscale[17];
	char nome[31];
	char cognome[31];
	char dataDiNascita[11];//gg/mm/yyyy
	char genere;
	int anni_esperienza;
	enum ruoli ruolo;
}dipendenti;

/**
* Numero massimo dei dipendenti
*/
#define MAX_DIPENDENTI 50

//PROTOTIPI DI FUNZIONE
int menu();
void inserisci_utente();
void modifica_utente(struct dipendenti d[]);
void leggi_utenti(struct dipendenti d[]);
void stampa_utenti(struct dipendenti d[]);
int numero_dipendenti(struct dipendenti d[]);
void clear_screen();

int main(void) {
	FILE* fPtr;

	if ((fPtr = fopen("cantieri.csv", "r")) == NULL) {
		printf("Impossibile aprire il file!");

		return 0;
	}

    dipendenti  d[50];
    cantiere    c[100];

	int azione = menu();

    leggi_utenti(d);
    switch(azione){
        case 1://Nuovo utente
            inserisci_utente();
            break;
        case 2://Modifica di un utente
            modifica_utente(d);
            break;
    }

	return 0;
}

/**
* Questa funzione definisce il menu dell'applicazione.
* Deve essere lanciato all'inizio della funzione main.
*/
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
* Prima di utilizzare questa funzione bisogna
* aver riempito l'array degli utenti attraverso
* la funzione @see #leggi_utenti()
*
* Al termine della chiamata della funziona
* saranno stampati tutti gli utenti
*
* @see #dipendenti
* @param dipendenti[] Array dei dipendenti da stampare
*
*/
void stampa_utenti(struct dipendenti *d){
    for(int i=0;i<MAX_DIPENDENTI; i++){
        if(d[i].controllo == -1) continue;

        printf("#%d\nCodice Fiscale: %s\n", (i+1), d[i].codice_fiscale);
        printf("Nome: %s\n", d[i].nome);
        printf("Cognome: %s\n", d[i].cognome);
        printf("Data di nascita: %s\n", d[i].dataDiNascita);
        printf("Genere: %c\n", d[i].genere);
        printf("Anni di esperienza: %d\n", d[i].anni_esperienza);
        printf("\n");
    }
}

/**
* Questa funzione legge tutti gli utenti dal file .CSV
* e li salva all'interno dell'array prodotto dalla
* struct @see dipendenti.
*
* Al termine della funzione si avrà un array contenente tutti
* gli utenti registrati sul file CSV
*
* @param *dipendenti contiene le informazioni degli utenti
*                    recuperati dal file
* @return void Questa funzione non restituisce nulla
*/
void leggi_utenti(struct dipendenti *d){
    FILE* utentiFPtr;

	if ((utentiFPtr = fopen("utenti.csv", "r")) == NULL) {
		printf("Impossibile aprire il file degli gli utentu!");

		return;
	}

    char *token;
    char *line;

    for(int i=0;i<MAX_DIPENDENTI; i++){
        int res = fscanf(utentiFPtr, "%s", line);


        if(res == EOF){
            d[i].controllo = -1;
        }

        token = strtok(line, ",");

        strcpy(d[i].codice_fiscale, token);//Codice Fiscale

        //printf("%s\n", token);

        int cont = 2;//Parte da 2 perché il token 1 è già stato letto
        while( (token = strtok(NULL, ","))){
            d[i].controllo = 0;

            switch(cont ++){
                //Nome dell'utente
                case 2: strcpy(d[i].nome, token); break;
                //Cognome dell'utente
                case 3: strcpy(d[i].cognome, token); break;
                //Sesso dell'utente
                case 4: d[i].genere = token[0]; break;
                //Ruolo dell'utente
                //Il ruolo viene salvato come valore numerico intero
                //(a partire da 1) e quindi uso uno switch per poter
                //settare i valori dei ruoli in modo corretto
                case 5: {
                    switch(atoi(token)){
                        case 1: d[i].ruolo = CAPOCANTIERE;break;
                        case 2: d[i].ruolo = CARPENTIERE;break;
                        case 3: d[i].ruolo = MURATORE;break;
                        case 4: d[i].ruolo = INTONACATORE;break;
                        case 5: d[i].ruolo = IDRAULICO;break;
                        case 6: d[i].ruolo = ELETTRICISTA;break;
                        case 7: d[i].ruolo = PIASTRELISTA;break;
                        case 8: d[i].ruolo = IMBIANCHINO;break;
                    }

                    break;
                    //Data di nascita dell'utente}
                    case 6: strcpy(d[i].dataDiNascita, token);break;
                    //Anni di esperienza dell'utente
                    case 7: {
                        int i = atoi(token);
                        d[i].anni_esperienza = i;

                        break;
                    }
                }
            }
        }
    }
}


/**
 * Prima di avviare questa funzione deve essere popolato
 * l'array contenente gli utenti richiamando la funzione
 * @see #leggi_utenti() .
 *
 * @param struct dipendenti è l'array contenente i dipendenti
 */
void modifica_utente(struct dipendenti *d){
    printf("############ PANNELLO DI MODIFICA DIPENDENTE ############\n\n");

    stampa_utenti(d);

    printf("Inserire il codice dell'utente da modificare.\n");
    printf("Non e' possibile modificare il codice fiscale\n");
    printf("Codice: ");

    int codice;
    scanf("%d", &codice);
    codice --;

    printf("Scegli il campo da modificare\n");
    printf("1) Nome\t\t\t2)Cognome\n3)Genere\t\t4)Ruolo\n5)Data di nascita\t6)Anni di esperienza\n");

    int scelta;
    printf("Scelta: ");
    scanf("%d", &scelta);

    switch(scelta){
    case 1:
        printf("Nome: ");
        scanf("%s", &d[codice].nome);

        break;
    }

    FILE *utentiPtr;
    if( (utentiPtr = fopen("utenti.csv", "w+")) == NULL ){
        printf("Impossibile aprire il file dei dipendenti!");

        return;
    }

    //SISTEMARE MODIFICA DEL FILE, POSIZIONARMI ALLA RIGA CORRETTA
    for(int i=0;i<numero_dipendenti(d);i ++){
        fprintf(utentiPtr, "%s,%s,%s,%c,%d,%s,%d\n", d[i].codice_fiscale,
                                                      d[i].nome,
                                                      d[i].cognome,
                                                      d[i].genere,
                                                      d[i].anni_esperienza,//Da modificare a dovere con giusta variabile
                                                      d[i].dataDiNascita,
                                                      d[i].anni_esperienza
               );
    }

    fclose(utentiPtr);
}

/**
* Salva i dipendenti sul file.
*
*
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
    scanf("%d", &ruolo);

    printf("Data di nascita: ");
    scanf("%s", &data_n);

    printf("Anni di esperienza: ");
    scanf("%d", &anni_esperienza);

    //Salvo i dati sul file
    fprintf(utentiFPtr, "%s,%s,%s,%c,%d,%s,%d\n", cf, nome, cognome, genere, ruolo, &data_n, anni_esperienza);

    fclose(utentiFPtr);
}

/**
* Conta il numero di dipendenti effettivamente
* Registrati sul file CSV.
*
* Per usare questa funzione bisogna prima utilizzare
* la funzione @see #leggi_dipendenti().
*
* Al termine dell'esecuzione la funzione restituisce
* il numero di dipendenti registrati.
*
* @param *dipendenti Array dei dipendenti
* @return int Numero dei dipendenti salvati
*             all'interno del file CSV.
*/
int numero_dipendenti(struct dipendenti *d){
    int cont=0;
    for(int i=0;i<MAX_DIPENDENTI; i++){
        if(d[i].controllo == -1){
            continue;
        }

        cont ++;
    }

    return cont;
}

/**
* Pulisce lo schermo del terminale.
* Questa funzione funziona solamente
* con il sistema operativo Windows
* in quanto viene richiamato il comando
* <b>cls</b>
*
* @param void
* @return void
*/
void clear_screen(){
    system("cls");
}


















