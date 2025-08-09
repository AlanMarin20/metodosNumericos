#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    double funcion = ((9.81*x)/14)*(1-exp(-(14/x)*7))-35;
    return  funcion;
}

int main(int argc, char const *argv[]){
    double a = 0, b = 0; 
    double tolerancia = 1e-5;
    
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
        iter++;
        c = (a * f(b) - b * f(a))/(f(b) - f(a));
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
    printf("La raiz es: %.12f, con error de: %.14f\n",c ,error);
    printf("Cantidad de iteraciones para encontrarlo: %d\n",iter);
    
}   