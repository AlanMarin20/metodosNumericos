#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("puntos.txt", "r");
    if (!fp) {
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

    //-------- Construir matriz --------
    double A[n][n], b[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(x[i], j);
        }
        b[i] = y[i];
    }

    //-------- Gauss con pivoteo --------
    for (int k = 0; k < n - 1; k++) {
        int maxRow = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(A[i][k]) > fabs(A[maxRow][k]))
                maxRow = i;
        }
        if (maxRow != k) {
            for (int j = 0; j < n; j++) {
                double temp = A[k][j];
                A[k][j] = A[maxRow][j];
                A[maxRow][j] = temp;
            }
            double tempb = b[k];
            b[k] = b[maxRow];
            b[maxRow] = tempb;
        }
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    //-------- Retrosustitución --------
    double coef[n];
    for (int i = n - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * coef[j];
        }
        coef[i] = sum / A[i][i];
    }

    //-------- Mostrar polinomio --------
    printf("\nPolinomio interpolador:\nP(x) = ");
    for (int i = 0; i < n; i++) {
        if (i == 0)
            printf("%.6f", coef[i]);
        else
            printf(" + (%.6f)*x^%d", coef[i], i);
    }
    printf("\n");

    //-------- Opcional propuesto por profe --------
    char opcion;
    printf("\n¿Queres evaluar el polinomio en un x? (S/N): ");
    scanf(" %c", &opcion);

    while (opcion == 'S' || opcion == 's') {
        double x_eval, resultado = 0.0;
        printf("Ingrese el valor de x: ");
        scanf("%lf", &x_eval);

        for (int i = 0; i < n; i++) {
            resultado += coef[i] * pow(x_eval, i);
        }
        printf("P(%.4f) = %.2f\n", x_eval, resultado);

        printf("\n¿Queres evaluar con otra x? (S/N): ");
        scanf(" %c", &opcion);
    }

    return 0;
}