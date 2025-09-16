#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *fp = fopen("puntos.txt","r");
    if(!fp){ 
        printf("No se pudo abrir puntos.txt\n"); 
        return 1; 
    }

    int n, p;
    fscanf(fp,"%d",&n); // Leo cantidad de puntos

    printf("Ingrese el grado del polinomio p: ");
    scanf("%d", &p);

    if(n < p+1){
        printf("Datos insuficientes para el grado del polinomio.\n");
        fclose(fp);
        return 1;
    }

    double x[n], y[n];
    for(int i=0;i<n;i++){
        fscanf(fp,"%lf %lf",&x[i],&y[i]);
    }
    fclose(fp);

    //-------- Construir matriz A y vector b --------
    double A[p+1][p+1], b[p+1];
    for(int l=0;l<=p;l++){
        b[l]=0.0;
        for(int i=0;i<n;i++){
            b[l]+=pow(x[i],l)*y[i];
        }
        for(int m=0;m<=p;m++){
            double sum=0.0;
            for(int i=0;i<n;i++){
                sum+=pow(x[i],l+m);
            }
            A[l][m]=sum;
        }
    }

    //-------- Gauss con pivoteo --------
    for(int k=0;k<=p;k++){
        int maxRow=k;
        for(int i=k+1;i<=p;i++){
            if(fabs(A[i][k])>fabs(A[maxRow][k])) maxRow=i;
        }
        if(maxRow!=k){
            for(int j=0;j<=p;j++){
                double tmp=A[k][j]; A[k][j]=A[maxRow][j]; A[maxRow][j]=tmp;
            }
            double tmpb=b[k]; b[k]=b[maxRow]; b[maxRow]=tmpb;
        }

        for(int i=k+1;i<=p;i++){
            double factor = A[i][k]/A[k][k];
            for(int j=k;j<=p;j++){
                A[i][j]-=factor*A[k][j];
            }
            b[i]-=factor*b[k];
        }
    }

    //-------- Retrosustitución --------
    double coef[p+1];
    for(int i=p;i>=0;i--){
        double sum=b[i];
        for(int j=i+1;j<=p;j++){
            sum-=A[i][j]*coef[j];
        }
        coef[i]=sum/A[i][i];
    }

    //-------- Mostrar polinomio --------
    printf("Polinomio de regresion:\nP(x) = ");
    for(int i=0;i<=p;i++){
        if(i==0) printf("%.6f",coef[i]);
        else printf(" + %.6f*x^%d",coef[i],i);
    }
    printf("\n");

    //-------- Calculo coeficiente de correlación r --------
    double ST=0.0, SR=0.0, yprom=0.0;
    for(int i=0;i<n;i++){
        yprom+=y[i];
    }
    yprom/=n;

    for(int i=0;i<n;i++){
        double yi_pred=0.0;
        for(int j=0;j<=p;j++) yi_pred+=coef[j]*pow(x[i],j);
        SR+=(y[i]-yi_pred)*(y[i]-yi_pred);
        ST+=(y[i]-yprom)*(y[i]-yprom);
    }

    double r=sqrt((ST-SR)/ST);
    printf("Coeficiente de correlacion r = %.4f\n",r);

    return 0;
}