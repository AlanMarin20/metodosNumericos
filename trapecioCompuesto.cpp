//-------- FALTA CUANDO NO HAY FUNCION --------

#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    double funcion = pow(x,2);
    return funcion;
}

int main(void) {
    double a, b, h, suma, integral;
    int n;

    printf("Ingrese limite inferior a: ");
    scanf("lf", &a);
    printf("Ingrese limite superior b: ");
    scanf("lf", &b);
   
    if (a == b) {
        printf("Intervalo nulo (a == b). Integral = 0\n");
        return 0;
    }

    printf("Ingrese numero de subintervalos n (entero > 0): ");
    scanf("d", &n);

    h = (b - a) / n;
    suma = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        suma += f(xi);
    }

    integral = ((b - a)/2) * suma;

    printf(" Integral aprox = %.12f\n", integral);

    return 0;
}