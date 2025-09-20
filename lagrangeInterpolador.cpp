#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("puntos.txt", "r");
    if (!fp){
        printf("No se pudo abrir 'puntos.txt'\n");
        return 1;
    }
    int n;
    fscanf(fp, "%d", &n);   // Leo cantidad de puntos

    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%lf %lf", &x[i], &y[i]);
    }
    fclose(fp);

    // -------- Construir polinomio de Lagrange --------
    double coef[n]; // coeficientes acumulados del polinomio final
    for (int i = 0; i < n; i++) coef[i] = 0.0;

    // Recorro cada L_k
    for (int k = 0; k < n; k++) {
        // Base de L_k: arranco con polinomio = 1
        double base[n];
        for (int i = 0; i < n; i++) base[i] = 0.0;
        base[0] = 1.0;

        double denom = 1.0;

        for (int i = 0; i < n; i++) {
            if (i != k) {
                denom *= (x[k] - x[i]);

                // multiplico el polinomio base por (x - x[i])
                for (int j = n-1; j >= 1; j--) {
                    base[j] = base[j-1] - x[i]*base[j];
                }
                base[0] = -x[i]*base[0];
            }
        }

        // Normalizo y multiplico por y[k]
        for (int j = 0; j < n; j++) {
            base[j] = base[j] * y[k] / denom;
            coef[j] += base[j];
        }
    }

    // -------- Mostrar el polinomio --------
    printf("\nPolinomio interpolador de Lagrange (forma expandida):\n");
    for (int j = n-1; j >= 0; j--) {
        if (coef[j] != 0.0) {
            if (j == 0) printf("%.6f ", coef[j]);
            else if (j == 1) printf("%.6f x + ", coef[j]);
            else printf("%.6f x^%d + ", coef[j], j);
        }
    }
    printf("\n");

    // -------- Preguntar si evaluar --------
    char opcion;
    printf("\n¿Desea evaluar el polinomio? (s/n): ");
    scanf(" %c", &opcion);

    while (opcion == 's' || opcion == 'S') {
        double x_eval, valor = 0.0;
        printf("Ingrese el valor de x a evaluar: ");
        scanf("%lf", &x_eval);

        for (int j = 0; j < n; j++) {
            double pot = 1.0;
            for (int k = 0; k < j; k++) pot *= x_eval;
            valor += coef[j] * pot;
        }

        printf("P(%.6f) = %.6f\n", x_eval, valor);

        printf("\n¿Desea evaluar otro punto? (s/n): ");
        scanf(" %c", &opcion);
    }

    return 0;
}