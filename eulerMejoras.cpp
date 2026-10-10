
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funcion diferencial: y' = f(x,y)
double f(double x, double y) {
    return cos(x * y);
}

int main() {
    double x0, y0, xf, h;
    int n, metodo;

    printf("Ingrese x0: ");
    scanf("%lf", &x0);
    printf("Ingrese y0: ");
    scanf("%lf", &y0);
    printf("Ingrese xf: ");
    scanf("%lf", &xf);
    printf("Ingrese el numero de subintervalos n: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("n debe ser un entero positivo.\n");
        return 1;
    }

    printf("\nSeleccione el metodo:\n");
    printf("1. Euler simple\n");
    printf("2. Euler mejorado (Heun)\n");
    printf("3. Euler mejorado (Punto medio)\n");
    printf("Ingrese el metodo: ");
    scanf("%d", &metodo);

    if(metodo < 1 || metodo > 3) {
        printf("Entre 1 y 3 GIL.\n");
        return 1;
    }

    h = (xf - x0) / n;
    double x[n+1], y[n+1];

    // Condiciones iniciales
    x[0] = x0;
    y[0] = y0;

    // Calculo de la solucion
    for(int i = 0; i < n; i++) {

        x[i+1] = x[i] + h;

        switch(metodo) {
            //-------- Euler simple --------
            case 1:
                y[i+1] = y[i] + h * f(x[i], y[i]);
                break;

            //-------- Euler mejorado: Heun --------
            case 2: {
                double yt = y[i] + h * f(x[i], y[i]);

                y[i+1] = y[i] + (h/2.0) *
                         (f(x[i], y[i]) + f(x[i+1], yt));
                break;
            }
            //-------- Euler mejorado: Punto medio --------
            case 3: {
                double xm = (x[i] + x[i+1]) / 2.0;
                double ym = y[i] + (h/2.0) * f(x[i], y[i]);

                y[i+1] = y[i] + h * f(xm, ym);
                break;
            }
        }
    }

    // Ajustar el ultimo punto al limite final
    x[n] = xf;

    // Grabar los puntos en grafico.txt
    FILE *fp = fopen("grafico.txt", "w");

    if(fp == NULL) {
        printf("No se pudo crear grafico.txt\n");
        return 1;
    }

    for(int i = 0; i <= n; i++) {
        fprintf(fp, "%.6f %.6f\n", x[i], y[i]);
    }

    fclose(fp);

    printf("\nResultado de la aproximacion:\n");
    printf("x = %.6f\n", x[n]);
    printf("y = %.6f\n", y[n]);
    printf("Los puntos se guardaron en grafico.txt\n");

    return 0;
}
