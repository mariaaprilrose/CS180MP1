#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"



/*Main Functions*/
int main () {

    FILE *fp;
    int field[100][100];
    char buff[255];
    int i;
    Q_head = NULL;
    Q_curr = NULL;
    fp = fopen("a.txt", "r");
    getFile(fp);
    Car carArray[numberOfCars];

    makeRoot(carArray);
    
    // if(i==matrixSize){
    //   Car newCarArray = 
    // }
    printf("\nmatrix limit %d\n", matrixSize);
    printf("\n");
    printGrid();
    //aStar(n_curr);
    BFStree();
    fclose(fp);
    return 0;
}

