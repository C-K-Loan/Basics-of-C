#include <stdio.h>

//Wir benutzen long long int, da die Zahlen exponentiell wachsen
//Die folgende Implementierung hat eine exponentielle Laufzeit.
 long long int fibonacci(int n) {

	//Behandlung der Basisfälle: n == 1 und n == 2
 if (n == 1||n== 2){
 return 1;

}
 else {
	//Berechne ansonsten Fib(n) durch Addition von Fib(n-1) und Fib(n-2)
 return fibonacci(n-1) + fibonacci(n-2);
 }
}

int main(){

	//die ersten N Fibonacci Zahlen sollen ausgegeben werden
	int N = 20;
	int i2 = 1;
	printf("Die ersten %d Fibonacci Zahlen sind:\n", N);

	//Ausgabe der ersten N Fibonacci Zahlen
	for(int i = 1; i<=N;i++){

	printf("fib(%d) = %llu\n", i, fibonacci(i2));
	i2++;
	
}
	return 0;
}

