#include <stdio.h>
double wurzel(int n, float x);



int main()  {

printf("%d\n",wurzel(8,9) );

}


double wurzel(int n, float x){
if(n >= 1){
return 0.5* (wurzel(n-1,x) + x/(wurzel(n-1,x)));
}
else if (n== 0){
return 1;
}

}