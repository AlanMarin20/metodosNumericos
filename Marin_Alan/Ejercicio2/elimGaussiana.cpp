#include <iostream> 
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    FILE *fp = fopen("matriz.txt", "r");
    if (!fp) {
        printf("No se pudo abrir 'matriz.txt'\n");
        return 1;
    }
    //-------- Leo la dimension de la matriz --------
    fscanf(fp, "%d", &n);
    double a[n][n], b[n], x[n];

    //-------- Leo matriz A y vector b --------
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%lf", &a[i][j]);
        }
        fscanf(fp, "%lf", &b[i]);
    }
    fclose(fp);
    
    //-------- Muestro la matriz leida --------
    printf("A|b:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%8.2f ", a[i][j]);
        printf(" | %8.2f\n", b[i]);
    }
    //-------- TRIANGULACION --------
    for (int k = 0; k < n - 1; k++) {
        //-------- Pivoteo parcial --------
        if (fabs(a[k][k]) < 1e-2) {
            int maxRow = k;
            double maxVal = fabs(a[k][k]);
            for (int i = k + 1; i < n; i++) {
                if (fabs(a[i][k]) > maxVal) {
                    maxVal = fabs(a[i][k]);
                    maxRow = i;
                }
            }
            if (maxRow != k) {
                for (int j = 0; j < n; j++) {
                    double tmp = a[k][j];
                    a[k][j] = a[maxRow][j];
                    a[maxRow][j] = tmp;
                }
                double tmpb = b[k];
                b[k] = b[maxRow];
                b[maxRow] = tmpb;
                printf("Pivoteo parcial: fila %d <-> fila %d\n", k+1, maxRow+1);
            }
        }
        //-------- Fin pivoteo parcial --------
        for (int i = k + 1; i < n; i++) {
            double m = a[i][k] / a[k][k];
            for (int j = k; j < n; j++) {
                a[i][j] -= m * a[k][j];
            }
            b[i] -= m * b[k];
        }
    }
    //-------- Muestro matriz despues del pivoteo --------
    printf("\nMatriz triangular superior (A|b):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%8.2f ", a[i][j]);
        printf(" | %8.2f\n", b[i]);
    }

    //-------- RETROSUSTITUCION --------
    for (int i = n - 1; i >= 0; i--) {
        double suma = b[i];
        for (int j = i + 1; j < n; j++) suma -= a[i][j] * x[j];
        x[i] = suma / a[i][i];
    }
    //-------- Muestro vector x --------
    printf("\nSolucion del sistema:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.2f\n", i+1, x[i]);
    }
return 0;
}