#include <stdio.h>
#include <stdlib.h> 	//für exit
#include <errno.h>	    //für errno und perror
#include <string.h> 	//für strncpy und strcmp

//definiert die maximale Länge von Namen von Produkten
#define MAX_LAENGE 100

//TODO: Definiere hier ein typedef struct für die Elemente der Liste.
// Nenne es "PreisListenElement", so dass es als Datentyp von den Funktionen weiter unten
// akzeptiert wird.
typedef struct _PreisListenElement {
char name[MAX_LAENGE];
float preis;
struct _PreisListenElement *naechstes;
}PreisListenElement;

// Dies ist die gesonderte Wurzel der verketteten Liste mit einem Zeiger auf das
// erste Element der Liste und einem Zähler für die Anzahl der Elemente
typedef struct PreisListe
{
     PreisListenElement *erstes;
	int laenge;
} PreisListe;



/* Diese Funktion gibt eine initialisierte Liste zurück.
 * In dieser Funktion wird:
 * 1. die Liste deklariert
 * 2. der Liste Speicher zugewiesen
 * 3. Membervariablen des struct ggfs. initialisiert
 *
 * Rückgabewert: die initialisierte Liste
 */
PreisListe *erzeugeNeueListe()
{
	PreisListe *liste = calloc(1, sizeof(PreisListe));

	liste->erstes = NULL;
	liste->laenge = 0;
	return liste;
}

/* Diese Funktion fügt ein Element vorne an einer bestehenden Liste an.
 * Parameter sind:
 * - ein Zeiger auf die Liste,
 * - ein Zeiger auf den Namen des neuen Elementes
 * - ein Zeiger auf den Preis des neuen Elementes
 */
void elementAnfuegen(PreisListe *liste, const char *name, float preis){
 

PreisListenElement *neuesSegment = calloc(1, sizeof(PreisListenElement));
// TODO: neues preisliste element erstellen, parameter übergeen,  speicher alluzieren
strcpy(neuesSegment->name,name);
neuesSegment->preis=preis;
neuesSegment->naechstes=liste->erstes;
liste->erstes=neuesSegment;
liste->laenge=liste->laenge+1;  

}
/* Diese Funktion leert die Liste und gibt den Speicher frei,
 * das heißt all der Speicher, der für die Listenelemente reserviert
 * wurde, muss hier freigegeben werden. Überprüfe mit valgrind ob es gelungen ist.
 */
void listeLeeren(PreisListe *liste)
{

	PreisListenElement *element = liste->erstes;
	while(element != NULL)
	{
		// TODO: Falls Du für Elemente in der Liste Speicher mit malloc/calloc
		// angefordert hast, musst Du diesen Speicher hier ebenfalls freigeben!
		PreisListenElement *naechstesElement = element->naechstes;
		free(element);
		element = naechstesElement;
	}
	liste->erstes = NULL;

}

/*Diese Funktion sucht den Preis für einen Namen in der Liste. Parameter sind:
 * - ein Zeiger auf die Liste
 * - ein Zeiger auf den String des Namens
 *
 * Rückgabewert: NULL, wenn der Name nicht gefunden wird ansonten ein Zeiger auf den
 * Preis.
 */
float *suchePreis(PreisListe *liste, const char *name)
{
float *returnwertPtr = NULL;

PreisListenElement *aktuellesElement= liste->erstes;

				while(aktuellesElement->name !=NULL){
									if (strcmp (aktuellesElement->name,name)==0){
											returnwertPtr = (float*) calloc(1, sizeof(float));
											*returnwertPtr= aktuellesElement->preis;
											return returnwertPtr;			
														    }
						      aktuellesElement=aktuellesElement->naechstes;
								   }
return NULL;

    //TODO: "Laufe" durch alle Elemente und vergleiche den Namen
    //(Parameter) mit den Namen in der Liste. Gib entweder den entsprechenden Preis zurück oder falls nichts gefunden wird NULL.
}

/* Diese Funktion gibt alle Elemente aus. Parameter sind:
 * - Ein Zeiger auf die Liste
 */
void listeAusgeben(PreisListe *liste)
{
	PreisListenElement *element = liste->erstes;
	printf ("Preisliste hat %d Elemente.\n", liste->laenge);
	while(element != NULL)
	{

		printf("Einkaufsgut %s hat den Preis %.2f\n", element->name, element->preis);
		element = element->naechstes;
	}
}


/* Diese Funktion liest die Preise aus der Datei ein.
 * Als Parameter wird folgendes übergeben:
 * - der Dateiname der Preisliste
 * - Die Preisliste
 *
 * Rückgabewert: Die Anzahl der Zeilen der Preisliste
 *
 * WICHTIG: Benutze die Funktion elementAnfuegen um neue Einträge zur Liste hinzufügen.
 * TIPP: Den Rückgabewert der Funktion kannst du für Fehlerbehandlung verwenden. Er
 * spielt ansonsten keine Rolle mehr für diese Aufgabe.
 */
int lese_preisliste(const char *dateiname, PreisListe *liste) {
char nameTemp[99];
float preisTemp=0;
int i= 0;
FILE *preisPtr= fopen(dateiname,"r");
 while(!feof(preisPtr)){
	fscanf(preisPtr,"%s %f ", nameTemp, &preisTemp);
 	elementAnfuegen(liste,nameTemp,preisTemp);
	i++;
							  }
fclose(preisPtr);
    // TODO: Lies die Datei wieder wie bei der letzten Aufgabe ein und
	// füge die Produktnamen und Preise diesmal in die Liste ein.
	return i;
}


/* Diese Funktion iteriert über die Einkaufsliste und benutzt die Liste, um den
 * Gesamtpreis zu berechnen. Mitgegeben werden als Parameter:
 * - die Preisliste
 * - der Namen der Einkaufsdatei
 *
 * Rückgabewert: Der gesamtpreis als float
 */
float berechneGesamtpreis(PreisListe *l, const char *einkaufslisteDatei)
{
	FILE *einkaufPtr=fopen(einkaufslisteDatei,"r");
	if(einkaufPtr==NULL){

		return -1;
			}
	//char *einkaufproduktTemp=calloc(100,sizeof(char));
	char einkaufproduktTemp[100];
	int mengeTemp=0;
	float gesamtpreis=0;
	float preisTemp=0;
	float *preisPtr;
		while(!feof(einkaufPtr)&& einkaufPtr!=0)	{

					 fscanf(einkaufPtr,"%s %d ",einkaufproduktTemp,&mengeTemp);
					 preisPtr=suchePreis(l,einkaufproduktTemp);
					if(preisPtr!=NULL){				
 					preisTemp= *preisPtr;
					gesamtpreis+=mengeTemp*preisTemp;
					free(preisPtr);
						}
					else {
					 printf("Produkt ist nicht vorhanden!");	}
					}


 	fclose(einkaufPtr);
	return gesamtpreis;
}


int main (int argc, char *argv[]){

	if (argc!=3){
        // HINEWIS: Es gibt wieder nur zwei Eingabeparameter!
		printf ("usage: %s <preisliste> <einkaufsliste>\n", argv[0]);
		exit(2);
	}

	const char *preislisteDatei = argv[1];
	const char *einkaufslisteDatei = argv[2];

    //Hier wird die Liste erzeugt!
	PreisListe *liste = erzeugeNeueListe();

    //Die Preisliste wird in die liste eingelesen.
	int anzahlElementePreisliste = lese_preisliste(preislisteDatei, liste);

    // Optionale Fehlerbehandlung.
	if(anzahlElementePreisliste < 0)
	{
		printf("Abbruch des Programms.\n");
		exit(1);
	}

    // Optionale Darstellung der Liste.
	printf("Ausgabe der eingelesenen Preisliste:\n");
	listeAusgeben(liste);

    // Berechnung des Preises.
	float gesamtpreis = berechneGesamtpreis(liste, einkaufslisteDatei);

    // Das Ausgabe Format des Ergebnises ist nur der reine Preis.
	printf("%.2f\n", gesamtpreis);

    // Die Liste wird nicht mehr gebraucht, daher wird der benutzte Speicher freigegeben.
	listeLeeren(liste);

	// Die Wurzel brauchen wir jetzt auch nicht mehr.
	free(liste);
	return 0;

}
