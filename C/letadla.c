//used header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//definition of accepted deviation of floating point
#define EPS 1e-12

//structure of a single plane in the format (x coordinate, y coordinate, name of the plane) where the name of the plane is not longer than 200 characters
typedef struct{
    double x;
    double y;
    char planeName[200];
} Plane;

typedef struct{
    double distance;
    Plane * Name1;
    Plane * Name2;
} distArray;

//structure where the data from the structure "Plane" are being saved into an array (function "addPlane")
typedef struct{
    Plane * data;
    size_t count;
    size_t size;
} planeArray;

//functionn used to free the array of distances, we are using this function at the end of function "calculateDistances"
void freedistArray (distArray * distances){
    free (distances);
}

//function used to calculate distances between all combinations of planes
void calculateDistances (planeArray * array, distArray * distances, Plane * p){
    size_t cnt = 0;
    double min = 0;
    size_t capacity = 100;
    for ( size_t j = 0 ; j<array->count - 1; j++ ){
        for ( size_t i = j + 1; i<array->count; i++ ){
            double dist_1 =((array->data[i].x - array->data[j].x) * (array->data[i].x - array->data[j].x));
            double dist_2 =((array->data[i].y - array->data[j].y) * (array->data[i].y - array->data[j].y));
            double dist = sqrt(dist_1 + dist_2);
            if (j == 0 && i == 1){
                min = dist;
            }
            if ((fabs(dist - min) <= EPS * fabs(dist + min))){
                distances[cnt].Name1 = &array->data[j];
                distances[cnt].Name2 = &array->data[i];
                cnt++;
            }
            else if (dist < min){
                cnt = 0;
                min = dist;
                distances[cnt].Name1 = &array->data[j];
                distances[cnt].Name2 = &array->data[i];
                cnt++;
            }
            if (cnt == capacity){
                capacity = capacity * 2;
                distances = (distArray*) realloc (distances, sizeof(distArray) * capacity);
            }
        }
    }
    printf("Vzdalenost nejblizsich letadel: %f\n", min);
    printf("Nalezenych dvojic: %ld\n", cnt);
    for (size_t i = 0; i<cnt; i++){
        printf("%s - %s\n", distances[i].Name1->planeName, distances[i].Name2->planeName);
    }
    free(distances);
}

//temporary function used to print the information about the planes
void printPlane (Plane * p){
    printf("%s, %f, %f\n", p->planeName, p->x, p->y);
}

//function used to free the memory from the array of planes
void freeArray (planeArray * array){
    free(array->data);
}

//function used to add planes into an array
void addPlane (Plane * p, planeArray * array){
    if(array->count == array->size){
        if(array->count == array->size){
            array->size += 100;
              
        array->data = (Plane*)realloc(array->data, sizeof(Plane)*array->size);
        }
    }
    array->data[array->count++] = *p;
}

int main (){
    Plane p;
    planeArray array = {};

//reading and checking input until feof (stdin)
    printf("Pozice letadel:\n");
    while (1){ 
        if(scanf("%lf,%lf: %199s", &p.x, &p.y, p.planeName) != 3){
            if (feof (stdin)){
                break;
            }
            printf("Nespravny vstup.\n");
            freeArray(&array);
            return 1;
        }
        addPlane(&p, &array);
    }
//if there are less than 2 planes on input the program prints out "Nespravny vstup." and ends, the return value is 1
    if (array.count < 2){
        printf("Nespravny vstup.\n");
        freeArray(&array);  
        return 1;
    }
    distArray * distances;
    distances = (distArray*)malloc(sizeof(distArray)*100);

    calculateDistances(&array, distances, &p);
//function used to free memory from the array of planes we got from input
//there is no need to free the array distances here, because we are already freeing the memory in function "calculateDistances"
    freeArray(&array);
    return EXIT_SUCCESS;
}