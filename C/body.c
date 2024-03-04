#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-12

int main ()
{
    double AB;
    double BC;
    double x1,x2,x3,y1,y2,y3;
    printf("Bod A:\n");
    if(scanf("%lf %lf", &x1, &y1)!=2) {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }
    printf("Bod B:\n");
    if(scanf("%lf %lf", &x2, &y2)!=2) {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }
    printf("Bod C:\n");
    if(scanf("%lf %lf", &x3, &y3)!=2) {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }
   
    AB=(y2-y1)/(x2-x1);
    BC=(y3-y2)/(x3-x2);
    
    if (x1==x2 && x2==x3 && x1==x3 && y1==y2 && y2==y3 && y1==y3) {
        printf("Nektere body splyvaji.\n");
        return EXIT_SUCCESS;
    }
    if ((x1==x2 && y1==y2) || (x1==x3 && y1==y3) || (x2==x3 && y2==y3)) {
        printf("Nektere body splyvaji.\n");
        return EXIT_SUCCESS;
    }
    if (((AB == BC) || (fabs(AB-BC) <= EPS * (fabs(AB)+fabs(BC)))) || ((x1==x2 && x2==x3 && x1==x3) && (y1!=y2 && y2!=y3 && y1!=y3))) {
        double max,mid,min,a,b,c;
        max=0;
        min=0;
        printf("Body lezi na jedne primce.\n");
        
        a = x1+y1;
        b = x2+y2;
        c = x3+y3;
        if(a>b && a>c) {
            max = a;
            if(b>c)
                min = c;
            else
                min = b;
        }
        if(b>a && b>c) {
            max = b;
            if(a>c)
                min = c;
            else
                min = a;
        }
        if(c>a && c>b) {
            max =c;
            if(a>b)
                min = b;
            else
                min = a;
        }
        mid = a + b + c - max - min ;
        if(fabs(mid-a)<=EPS*(fabs(mid)+fabs(a)))
            printf("Prostredni je bod A.\n");
        if(fabs(mid-b)<=EPS*(fabs(mid)+fabs(b)))
            printf("Prostredni je bod B.\n");
        if(fabs(mid-c)<=EPS*(fabs(mid)+fabs(c)))
            printf("Prostredni je bod C.\n");
        return EXIT_SUCCESS;
        
    } else {
        printf("Body nelezi na jedne primce.\n");
        return EXIT_FAILURE;
    }
}