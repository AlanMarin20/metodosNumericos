#include <iostream> 
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    double tolerancia = 1e-5;
    FILE *fp = fopen("matriz.txt", "r");
    if (!fp) {
        printf("No se pudo abrir 'matriz.txt'\n");
        return 1;
    }
    //-------- Leo la dimension de la matriz --------
    fscanf(fp, "%d", &n);
    double a[n][n], b[n], x[n], x_old[n];
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) fscanf(fp, "%lf", &a[i][j]);
        fscanf(fp, "%lf", &b[i]);
    }
    fclose(fp);

    //-------- Chequear diagonal dominante --------
    int dominante = 1;
    for(int i=0;i<n;i++){
        double suma = 0.0;
        for(int j=0;j<n;j++){
            if(j != i) suma += fabs(a[i][j]);
        }
        if(fabs(a[i][i]) < suma){
            dominante = 0;
            printf("Fila %d no cumple diagonal dominante: |a_ii|=%.2f < sum|a_ij|=%.2f\n", i+1, fabs(a[i][i]), suma);
        }
    }
    if(dominante) printf("La matriz es diagonal dominante.\n");

    //-------- Inicializar vector x --------
    for(int i=0;i<n;i++) x[i] = 0.0;

    int iter = 0;
    double error;

    //-------- GaussSeidel --------
    do {
        iter++;
        error = 0.0;

        //--- Guardo los valores viejos ---
        for(int i=0;i<n;i++){
            x_old[i] = x[i];
        } 
        //--- Calculo x con la formula de Gauss Seidel ---
        for(int i=0;i<n;i++){
            double suma = 0.0;
            //--- Uso los valores nuevos x[j] ---
            for(int j=0;j<i;j++) {
                suma += a[i][j] * x[j];
            }
            //--- Uso los valores viejos x_old[j] como en Jacobi ---
            for(int j=i+1;j<n;j++) {
                suma += a[i][j] * x_old[j];
            }

            x[i] = (b[i] - suma) / a[i][i];
        }
        //-------- Calculo el error --------
        double sum_cuadrados = 0.0;
        for(int i=0;i<n;i++) {
            sum_cuadrados += pow(x[i]-x_old[i], 2);
        }
        error = sqrt(sum_cuadrados);

    } while(error > tolerancia && iter < 10000);

    printf("\nSolucion por GaussSeidel (despues de %d iteraciones):\n", iter);
    for(int i=0;i<n;i++) {
        printf("x[%d] = %.6f\n", i+1, x[i]);
    }
    printf("Con error de %.8f\n", error);
    return 0;
}