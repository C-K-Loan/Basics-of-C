#include <stdio.h>
#include <stdlib.h>  // für exit und atoi
#include <errno.h>   // für errno und perror
#include <string.h>  // für strncpy und strcmp


// Definiert die maximale Länge der Namen von Produkten
#define MAX_LAENGE 100




/* Diese Funktion liest die Preisliste ein. 
 * Als parameter wird folgendes übergeben:
 * - die (maximale) Anzahl an einzulesenden Preisen
 * - der Dateiname der Preisliste
 * - zwei Arrays, in denen zeilenweise der Name
 * 	 sowie der Preis gespeichert werden soll
 * 
 * WICHTIG:
 * Die übergebene Variable namenArray enthält initial nur 
 * NULL-Pointer. Es muss mittels malloc bzw. calloc Speicher reserviert 
 * werden, in welchen die eingelesenen Namen geschrieben werden. 
 * Im namenArray sollen dann nur die Verweise auf diese	Speicherbereiche
 * gespeichert werden. */		
int lese_preisliste(int maximaleAnzahlPreise, const char* dateiname, char* namen[], float preise[])
{

char namenTemp [100];

int i = 0;
FILE*file= fopen(dateiname, "r");
if(file==NULL){
return -1;
}

//while schleife liest preise in preise und namen in namen
while(!feof(file)) { 
	if (fscanf(file,"%s %f",namenTemp,&preise[i]) !=2) break;
	namen[i]= (char*) calloc(strlen(namenTemp)+1, sizeof(char));
	strcpy(namen[i],namenTemp);
	i++;
	}

fclose(file);
return 	i;
}





// Der Funktion wird folgendes uebergeben:
// * die Anzahl an Elementen in der Preisliste, 
// * die entsprechenden Namen und Preise jeweils als Array 
// * Dateiname der Einkaufsliste
float berechneGesamtpreis(	int anzahlElementePreisliste, 
				char* namenPreisliste[], 
				float preisePreisliste[],
				const char* einkaufslisteDatei)
{


int j = 0 ;
float quittung = 0 ;
int mengeTemp = 0 ;
char einkaufproduktTemp[100];
FILE*einkaufptr= fopen(einkaufslisteDatei, "r");
if(einkaufptr==NULL){
return -1;
}


while (fscanf(einkaufptr,"%s %d",einkaufproduktTemp,&mengeTemp)!=EOF) {
  for(j=0; j<anzahlElementePreisliste; j++) {
  
    if (strcmp(einkaufproduktTemp,namenPreisliste[j]) ==0 ){break;}
  }
  quittung=quittung + mengeTemp*preisePreisliste[j];
}
fclose(einkaufptr);

return quittung;
}
//Diese Funktion gibt den zuvor allozierten Speicher frei.
//Insbesondere die Speicherbereiche die für einzelne Namen reserviert
//wurden, müssen freigegeben werden.
void bereinigeSpeicher(	int anzahlGespeicherterProdukte, 
			char* namenArray[], 
			float preisArray[])
{
	//gib den Speicher für das preisArray frei
	free(preisArray);
	//gib den Speicher für die einzeln allozierten Namen frei
	for(int i = 0; i < anzahlGespeicherterProdukte; i++)
	{
		if(namenArray[i] != NULL)
		{
			//Sofern der i-te Name auf einen (hoffentlich) gültigen
			//Speicherbereich verweist, geben wir diesen Speicher frei
			free(namenArray[i]);
		}
	}
	//gib danach den Speicher für das Array frei, in dem die Verweise
	//auf die einzelnen Namen gespeichert wurden
	free(namenArray);
}





int main (int argc, char *argv[]){

	if (argc!=4){
		printf ("verwendung: %s <preisliste> <laenge der preisliste> <einkaufsliste> \n", argv[0]);
		exit(2);
	}

	const char* preislisteDatei = argv[1];
	int maximaleAnzahlPreise = atoi(argv[2]);
	const char* einkaufslisteDatei = argv[3];

	//Hinweis: 	calloc ist eine Erweiterung von malloc, welche in den reservierten
    //			Speicher initial Nullen schreibt. 			

	//Alloziere ein Array von Floats, um dort die Preise zu speichern
	float* preisArray = calloc(maximaleAnzahlPreise, sizeof(float));
	
	//Alloziere ein Array von Zeichenketten, also char*
	//Insbesondere hier ist die Verwendung von calloc wichtig, damit
	//alle enthaltenen Enthaltenen char Pointer zu Beginn gleich NULL sind!
	char ** namenArray = calloc(maximaleAnzahlPreise, sizeof(char*));

	//lies die Preisliste ein
	int anzahlElementePreisliste = lese_preisliste(maximaleAnzahlPreise, preislisteDatei, namenArray, preisArray);

	if(anzahlElementePreisliste < 0)
	{
		//falls ein Fehler aufgetreten ist, wird das Programm ohne Umwege verlassen
		printf("Abbruch des Programms");
		
		//auch wenn das Programm auf Grund eines Fehlers beendet wird,
		//muss der Speicher freigegeben werden.
		bereinigeSpeicher(maximaleAnzahlPreise, namenArray, preisArray);
		
		exit(1);
	}

	//berechne den Gesamtpreis, indem die eingelesene Preisliste sowie der Dateiname der
	//Einkaufsliste übergeben wird
	float gesamtpreis = berechneGesamtpreis(anzahlElementePreisliste, namenArray, preisArray, einkaufslisteDatei);

	//Gib den Gesamtpreis auf 2 Nachkommastellen genau an.
	printf("Der Gesamtpreis beträgt %.2f.\n\tHaben Sie eine Paybackkarte?\n", gesamtpreis);
	
	//Gib den Speicher frei, der durch malloc bzw. calloc reserviert wurde.
	bereinigeSpeicher(anzahlElementePreisliste, namenArray, preisArray);

	//Beende das Programm ohne Fehler
	return 0;
}
