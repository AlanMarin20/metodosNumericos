#include <stdio.h>
#include <math.h>

// Función que se va a integrar
double f(double x) {
    double f = pow(x,2) + 1;
    return f;
}

// Segunda derivada de la función: f''(x)
double fpp(double x) {
    double derivada = 2.0; //Derivada SEGUNDA
    return derivada; 
}

int main() {
    double a, b, h, x, suma, I, error;
    int n, i;

    printf("Ingrese el limite inferior (a): ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior (b): ");
    scanf("%lf", &b);
    printf("Ingrese el numero de subintervalos (n): ");
    scanf("%d", &n);

    // Algoritmo de Integración
    h = (b - a) / n;
    suma = f(a) + f(b);

    for (i = 1; i <= n - 1; i++) {
        x = a + i * h;
        suma = suma + 2 * f(x);
    }

    I = (h / 2.0) * suma;

    double max_fpp = fpp(a); // Para f''(x) constante o conocida en el intervalo
    error = -1.0 / 12.0 * (pow(b - a, 3) / pow(n, 2)) * max_fpp;

    printf("\nEl resultado de la integral es: %f\n", I);
    printf("El error estimado es: %f\n", error);

    return 0;
}