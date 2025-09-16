#include <stdio.h>

int main() {
    FILE *fp = fopen("puntos.txt", "r");
    if (!fp){
        printf("No se pudo abrir 'puntos.txt'\n");
        return 1;
    }
    int n;
    fscanf(fp, "%d", &n);   // Leo cantidad de puntos

    double x[n], y[n];
    for (int i = 0; i < n; i++) {//Leo el archivo y guardo en arreglos
        fscanf(fp, "%lf %lf", &x[i], &y[i]);
    }
    fclose(fp);

    double x_eval;
    printf("Ingrese el valor de x a evaluar: ");
    scanf("%lf", &x_eval);

    //-------- Calculo Pn(x_eval) --------
    double suma = 0.0;

    for (int k = 0; k < n; k++) {
        double prod = 1.0;   // En 1 para multiplicar

        for (int i = 0; i < n; i++) {
            if (i != k) {
                prod *= (x_eval - x[i]) / (x[k] - x[i]); //Formula productora
            }
        }

        suma += y[k] * prod;
    }

    printf("\nEl valor interpolado en x=%.2f es: %.2f\n", x_eval, suma);

    return 0;
}