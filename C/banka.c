#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ()
{
    double u1, u2 = 0;
    int d,c = 0;
    printf("Zadejte kreditni urok [%%]:\n");
    if (scanf("%lf",&u1)!=1||u1<0 || u1>100) {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }
    printf("Zadejte debetni urok [%%]:\n");
    if (scanf("%lf",&u2)!=1||u2<0 || u2>100) {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }
    printf("Zadejte transakce:\n");
    double zustatek = 0;
    int dny = 0;
    while(scanf("%d,%d",&d,&c)==2) {
            
        if (d-dny<0) 
            break;
        if (d==0) {
            zustatek=c;
            continue;
        }
        if (c!=0) {
            for(int i=0;i<(d-dny);i++) {
                if (zustatek<0)
                    zustatek += ceil(zustatek*(100*u2*0.01))/100;
                else
                    zustatek += floor(zustatek*(100*u1*0.01))/100;
            }
        } else {
            for (int i=0;i<(d-dny);i++) {
                if (zustatek<0)
                    zustatek += ceil(zustatek*(100*u2*0.01))/100;
                else
                    zustatek += floor(zustatek*(100*u1*0.01))/100;
            } 
            printf("Zustatek: %.2lf\n", zustatek);
            return EXIT_SUCCESS;
        }
        
        dny = d;
        zustatek +=c;
    }
    printf("Nespravny vstup.\n");
    return EXIT_FAILURE;
}