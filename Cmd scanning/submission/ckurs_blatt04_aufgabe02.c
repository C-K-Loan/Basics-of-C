#include <stdio.h>

int main () {

float zahl = 0 ;
int i=1;
float a=0;
int c=0;
	while (i==1) {	
	printf("Gib eine Zahl ein:\n");	
 	i=scanf("%f", &zahl);
	if (i==1) {a=a+zahl;c++;}
	
	}
	
      printf("Der Mittelwert lautet: %.2f \n",a/c);
	return 0;
}
