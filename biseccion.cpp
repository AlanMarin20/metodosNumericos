#include <iostream> 
#include <stdio.h>
#include <math.h>

double f(double x){
    double funcion = ((9.81*x)/14)*(1-exp(-(14/x)*7))-35;
    return  funcion;
}

int main(int argc, char const *argv[]){
    double a = 0, b = 0; 
    double tolerancia = 1e-5;
    
    printf("Ingrese a: ");
    scanf("%lf", &a);
    printf("Ingrese b: ");
    scanf("%lf", &b);

    //Verifico si la raiz esta entre x0 y x1
    if (f(a) * f(b) > 0) { //NO esta la raiz en el intervalo
        printf("El intervalo [%.2f, %.2f] no tiene raiz\n", a, b);
        exit(1); 
    }    

    double c = 0, error = 0, cviejo = 0;
    int iter = 0;

    do {
        iter++;
        c = (a + b) / 2; //Divido el intervalo en dos
        if (f(a) * f(c) > 0){ 
            a = c; //Si la raiz esta a la derecha
        }else if (f(a) * f(c) < 0){
            b = c; //Si la raiz esta a la izquierda
        }
        else{
            printf("c= %.10f es la raiz\n", c); 
        }
        error = fabs(c - cviejo); //Calculo el error
        cviejo = c;
    }while (error > tolerancia);
    printf("La raiz es: %.12f, con error de: %.14f\n",c ,error);
    printf("Cantidad de iteraciones para encontrarlo: %d\n",iter);
}   

