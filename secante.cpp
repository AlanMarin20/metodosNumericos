#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    double funcion = cos(x) ;
    return  funcion;
}

int main(int argc, char const *argv[]){
    double x0 = 0, x1 = 0, x2 = 0, error = 0; 
    double tolerancia = 1e-5;
    int iter = 0;

    printf("Ingrese x0: ");
    scanf("%lf", &x0);
    printf("Ingrese x1: ");
    scanf("%lf", &x1);

    do {
        if((f(x1) - f(x0)) == 0){
            printf("Denominador igual que cero\n");
            exit(1);
        }
        iter++;
        if(fabs((f(x1) - f(x0))) < 1e-10){
            printf("Denominador muy chico\n");
            exit(2);
        }else{
            x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
            error = fabs(x1 - x0);
            x0 = x1;
            x1 = x2;
        }
    }while (error > tolerancia && iter < 10000);
    printf("\n\nLa raiz es: %.8f, con error de: %.10f\n",x2 ,error);
    printf("Cantidad de iteraciones para encontrarlo: %d\n",iter);
}   

