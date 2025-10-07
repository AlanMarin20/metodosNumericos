#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *fp = fopen("puntos.txt", "r");
    if (!fp) {
        printf("No se pudo abrir 'puntos.txt'\n");
        return 1;
    }

    int n;  // Leo cantidad de puntos
    fscanf(fp, "%d", &n);

    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%lf %lf", &x[i], &y[i]);
    }
    fclose(fp);

    int m = n - 1;       // cantidad de intervalos
    int N = 4 * m;       // cantidad de incógnitas

    double a[N][N], b[N], sol[N];

    // inicializo en 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) a[i][j] = 0.0;
        b[i] = 0.0;
        sol[i] = 0.0;
    }

    //-------- Primeras 2n filas --------
    for (int k = 0; k < m; k++) {
        for (int j = 0; j < 4; j++) {
            a[2*k][4*k + j]     = pow(x[k],   3 - j);
            a[2*k+1][4*k + j]   = pow(x[k+1], 3 - j);
        }
        b[2*k]   = y[k];
        b[2*k+1] = y[k+1];
    }

    //-------- n-1 ecuaciones derivadas primeras en internos --------
    for (int k = 0; k <= m - 2; k++) {
        double xp1 = x[k+1];
        for (int j = 0; j <= 2; j++) {
            double coeff = (3 - j) * pow(xp1, 2 - j);
            a[2*m + k][4*k + j]     += coeff;
            a[2*m + k][4*(k+1) + j] -= coeff;
        }
        b[2*m + k] = 0.0;
    }

    //-------- n-1 ecuaciones derivadas segundas en internos --------
    for (int k = 0; k <= m - 2; k++) {
        double xp1 = x[k+1];
        a[3*m - 1 + k][4*k + 0]     += 3.0 * xp1;
        a[3*m - 1 + k][4*k + 1]     += 1.0;
        a[3*m - 1 + k][4*(k+1) + 0] -= 3.0 * xp1;
        a[3*m - 1 + k][4*(k+1) + 1] -= 1.0;
        b[3*m - 1 + k] = 0.0;
    }

    //-------- derivadas en frontera --------
    a[4*m - 2][0] = 3.0 * x[0];
    a[4*m - 2][1] = 1.0;
    b[4*m - 2] = 0.0;

    a[4*m - 1][4*(m-1) + 0] = 3.0 * x[m];
    a[4*m - 1][4*(m-1) + 1] = 1.0;
    b[4*m - 1] = 0.0;

    //-------- Gauss con pivoteo --------
    for (int k = 0; k < N; k++) {
        int maxRow = k;
        double maxVal = fabs(a[k][k]);
        for (int i = k+1; i < N; i++) {
            if (fabs(a[i][k]) > maxVal) {
                maxVal = fabs(a[i][k]);
                maxRow = i;
            }
        }
        if (maxRow != k) {
            for (int j = k; j < N; j++) {
                double tmp = a[k][j];
                a[k][j] = a[maxRow][j];
                a[maxRow][j] = tmp;
            }
            double tmpb = b[k];
            b[k] = b[maxRow];
            b[maxRow] = tmpb;
        }
        for (int i = k+1; i < N; i++) {
            double factor = a[i][k] / a[k][k];
            for (int j = k; j < N; j++) {
                a[i][j] -= factor * a[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    for (int i = N-1; i >= 0; i--) {
        double s = b[i];
        for (int j = i+1; j < N; j++) s -= a[i][j] * sol[j];
        sol[i] = s / a[i][i];
    }

    //-------- Mostrar polinomios --------
    printf("\nSpline cúbico por intervalos:\n");
    for (int k = 0; k < m; k++) {
        double ak = sol[4*k + 0];
        double bk = sol[4*k + 1];
        double ck = sol[4*k + 2];
        double dk = sol[4*k + 3];
        printf("[%g, %g]: S_%d(x) = %g x^3 + %g x^2 + %g x + %g\n",
               x[k], x[k+1], k, ak, bk, ck, dk);
    }

    char opcion;
    printf("\n¿Desea valuar el spline en un punto? (s/n): ");
    scanf(" %c", &opcion);

    while(opcion == 's' || opcion == 'S') {
        double xval;
        printf("Ingrese el valor de x a evaluar: ");
        scanf("%lf", &xval);

        //-------- Buscar intervalo donde cae xval --------
        int k = -1;
        for(int i=0; i<n-1; i++) {
            if(xval >= x[i] && xval <= x[i+1]) {
                k = i;
                break;
            }
        }

        if(k == -1) {
            printf("El valor %.4f está fuera del rango de los puntos.\n", xval);
        } else {
            double ak = sol[4*k + 0];
            double bk = sol[4*k + 1];
            double ck = sol[4*k + 2];
            double dk = sol[4*k + 3];
            double px = ak*pow(xval,3) + bk*pow(xval,2) + ck*xval + dk;
            printf("S_%d(%.4f) = %.6f\n", k, xval, px);
        }

        printf("\n¿Desea valuar otro punto? (s/n): ");
        scanf(" %c", &opcion);
    }
    return 0;
}