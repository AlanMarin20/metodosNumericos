#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Ingrese el tamaño de la matriz (ej: 100): ");
    scanf("%d", &n);

    FILE *fp = fopen("matriz.txt", "w");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        // recorro columnas
        for (int j = 0; j < n; j++) {
            if (j == i) {
                fprintf(fp, "2 ");
            } else if (j == i-1 || j == i+1) {
                fprintf(fp, "1 ");
            } else {
                fprintf(fp, "0 ");
            }
        }

        // ahora el resultado (última columna)
        if (i == 0) {
            fprintf(fp, "4.5");
        } else if (i < n-1) {
            fprintf(fp, "6");
        } else {
            fprintf(fp, "4.5");
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("La matriz se guardó en matriz.txt\n");
    return 0;
}