#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    double funcion = 2*x + log(x) - sin(3*x) ;
    return  funcion;
}

int main(int argc, char const *argv[]){
    double x0 = 0, x1 = 0, error = 0, derivada = 0; 
    double tolerancia = 1e-6;
    int iter = 0;

    printf("Ingrese x0: ");
    scanf("%lf", &x0);
    printf("derivada: %8.f",(f(x0 + 0.001) - f(x0))/0.001);

    do {
        if(fabs((f(x0 + 0.01) - f(x0))/0.01) == 0){ //Verifico que el denominador no sea = 0
            printf("Derivada igual que cero\n");
            exit(1);
        }
        iter++;
        if(fabs((f(x0 + 0.001) - f(x0))/0.001) < 1e-10){ //Verifico que el denominador no sea demasiado pequeño
            printf("la derivada es muy chica\n");
            exit(1);
        }else{
            derivada = ((f(x0 + 0.001) - f(x0))/0.001);
            x1 = x0 - (f(x0) / derivada); //Marco la raiz de la recta tangente a la curva en xviejo
            error = fabs(x1 - x0);
            x0 = x1;
        }
    }while (error > tolerancia && iter < 10000);
    printf("\n\nLa raiz es: %.8f, con error de: %.8f\n",x0 ,error);
    printf("Cantidad de iteraciones para encontrarlo: %d\n",iter);
    printf("F(x1) es: %8.f\n", f(x1));
}   

