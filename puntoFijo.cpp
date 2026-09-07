#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    double funcion = (pow(x+1,1./3));
    return  funcion;
}
double Derivada(double x){
    double derivada = (1/(3*(pow(x+1,2./3))));
    return  derivada;
    // fabs((f(x0 + 0.01) - f(x0))/0.01) aproximacion
}

int main(int argc, char const *argv[]){
    double x0 = 0, x1 = 0, error = 0; 
    double tolerancia = 1e-10;
    int iter = 0; 

    printf("Ingrese x0: ");
    scanf("%lf", &x0);
    printf("derivada: %8.f\n",Derivada(x0));
    do {
        iter++;
        if(fabs(Derivada(x0)) >= 1){ //Si val absoluto de la derivada es mayor que 1, la funcion no converge.
            printf("El metodo no converge.\nEl valor absoluto de la derivada es: %.5f\n", fabs((f(x0 + 0.01) - f(x0))/0.01));
            exit(1);
        }else{
            x1 = f(x0); //Acerco la raiz al f(xviejo)
            error = fabs(x1 - x0);
            x0 = x1;
        }
    }while (error > tolerancia);
    printf("La raiz es: %.14f, con error de: %.14f\n",x0 ,error);
    printf("Cantidad de iteraciones para encontrarlo: %d\n",iter);
}   

