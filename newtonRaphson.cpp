#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    double funcion = (pow(x,3)-x -1);
    return  funcion;
}
double Derivada(double x){
    double derivada = (3*pow(x,2)-1);
    return  derivada;
    // fabs((f(x0 + 0.01) - f(x0))/0.01) aproximacion
}

int main(int argc, char const *argv[]){
    double x0 = 0, x1 = 0, error = 0, derivada = 0; 
    double tolerancia = 0.001;
    int iter = 0;

    printf("Ingrese x0: ");
    scanf("%lf", &x0);

    do {
        if(fabs(Derivada(x0)) == 0){ //Verifico que el denominador no sea = 0
            printf("Derivada igual que cero\n");
            exit(1);
        }
        iter++;
        if(fabs(Derivada(x0)) < 1e-10){ //Verifico que el denominador no sea demasiado pequeño
            printf("la derivada es muy chica\n");
            exit(1);
        }else{
            derivada = Derivada(x0);
            x1 = x0 - (f(x0) / derivada); //Marco la raiz de la recta tangente a la curva en xviejo
            error = (fabs(x1 - x0));
            x0 = x1;
        }
    }while (error > tolerancia && iter < 4);
    printf("\n\nLa raiz es: %.10f, con error de: %.10f\n",x0 ,error);
    printf("Cantidad de iteraciones para encontrarlo: %d\n",iter);
    //printf("F(x1) es: %8.f\n", f(x1));
}   

