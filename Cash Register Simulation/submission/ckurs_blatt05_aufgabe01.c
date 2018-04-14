#include <stdio.h>
#include <stdlib.h> 	//für exit
#include <errno.h>	//für errno und perror
#include <string.h> 	//für strncpy und strcmp

//definiert die maximale Anzahl an Zeilen für sowohl die Preisliste wie auch die Einkaufsliste
#define MAX_ZEILEN 100
//definiert die maximale Länge von Namen von Einkaufsgütern
#define MAX_LAENGE 100

//liest die Preisliste in die Arrays namen und preise ein und gibt die Anzahl gelesener Zeilen (= Elemente) zurück
//Bei einem Fehler wird -1 zurückgegeben
int lese_preisliste(const char* dateiname, char namen[MAX_ZEILEN][MAX_LAENGE], float preise[MAX_ZEILEN])
{
int i = 0;
FILE*file= fopen(dateiname, "r");
if(file==NULL){
return -1;
}

//while schleife liest preise in preise und namen in namen
while(!feof(file)) { 
	if (fscanf(file,"%s %f",&namen[i][0],&preise[i]) !=2) break;
	
	printf("In Preisliste %s, %f \n", namen[i],preise [i]);
	i++;
	}

fclose(file);
return 	i;
		   }

//analog zur lese_preisliste Funktion, jedoch werden ganze Zahlen gelesen.
int lese_einkaufsliste(const char* dateiname, char namen[MAX_ZEILEN][MAX_LAENGE], int anzahl[MAX_ZEILEN])
{
int i = 0;


FILE*file= fopen(dateiname, "r");
if(file==NULL){
return -1;
}
while(!feof(file)) { 
	fscanf(file,"%s %d ",&namen[i][0],&anzahl[i]);
	
	printf("in Einkaufsliste %s, %d \n", namen[i],anzahl [i]);
	i++;
	}
fclose(file);
return 	i;
	
}



//Relativ einfache Funktion welche für jedes Einkaufsgut den entsprechenden Preis sucht
//Beachtet, dass dies auch on-the-fly während des Einlesens der Einkaufsliste erfolgen kann (siehe spätere Musterlösungen)
float berechneGesamtpreis(	int anzahlElementePreisliste, 
				char namenPreisliste[MAX_ZEILEN][MAX_LAENGE], 
				float preisePreisliste[MAX_ZEILEN],
				int anzahlElementeEinkaufsliste,
				char namenEinkaufsliste[MAX_ZEILEN][MAX_LAENGE], 
				int anzahlenEinkaufsliste[MAX_ZEILEN])
{


int i = 0;
int j = 0;
int z= 0;
float quittung= 0;


for(i=0;i<anzahlElementeEinkaufsliste;++i){ // für jedes Elemnt
for(j=0;j<anzahlElementePreisliste;++j) {
if(strcmp(namenEinkaufsliste[i],namenPreisliste[j])==0){
quittung += anzahlenEinkaufsliste[i]*preisePreisliste[j];
}
}
}


//for ( z=anzahlElementeEinkaufsliste; i<z; i++){
//j=0;
//while(namenEinkaufsliste[i][0] =! namenPreisliste[j][0]) {
//j++;
//}
//quittung = preisePreisliste[j]*anzahlenEinkaufsliste[i]+quittung;
//}
	



return quittung;	
}






int main (int argc, char *argv[]){ 
int anzahlElementePreisliste=0;
int anzahlElementeEinkaufsliste=0;
float endpreis=0;

	if (argc!=3){
		
		printf ("usage: %s <preisliste> <einkaufsliste>\n", argv[0]);
		exit(2);
	}

	const char* preislisteDatei = argv[1];
	const char* einkaufslisteDatei= argv[2];
	char namen[MAX_ZEILEN][MAX_LAENGE];
	 float preise[100];
        char einkaufsliste[MAX_ZEILEN][MAX_LAENGE];
	int anzahl[100];
	// Ihr Code
	anzahlElementePreisliste= lese_preisliste(argv[1],namen,preise);
	anzahlElementeEinkaufsliste= lese_einkaufsliste(argv[2],einkaufsliste,anzahl);


	endpreis=berechneGesamtpreis (anzahlElementePreisliste,namen,preise,anzahlElementeEinkaufsliste,einkaufsliste,anzahl);

	printf("Der Betrag ist : %f ", endpreis);

	return 0;

}
