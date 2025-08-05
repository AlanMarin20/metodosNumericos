#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    return x;
}

int main(int argc, char const *argv[]){
    double a = 0, b = 0; 
    double tolerancia = 1e-6;
    
    printf("Ingrese a: ");
    scanf("%lf", &a);
    printf("Ingrese b: ");
    scanf("%lf", &b);

    if (f(a) * f(b) > 0) { //NO esta la raiz en el intervalo
        printf("El intervalo [%.2f, %.2f] no tiene raiz\n", a, b);
        exit(1); 
    }    

    double c = 0, error = 0, cviejo = 0;
    int iter = 0;

    do {
        c = (a + b) / 2;
        if (f(a) * f(c) > 0){
            a = c;
        }else if (f(a) * f(c) < 0){
            b = c;
        }
        else{
            printf("c= %.10f es la raiz\n", c);
        }
        error = fabs(c - cviejo);
        cviejo = c;
    }while (error > tolerancia);
    printf("La raiz es: %.10f, con error de: %.12f",c ,error);
    
}   

