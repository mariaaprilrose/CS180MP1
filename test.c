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
//////////////ASTAR SEARCH
    // trial of CopyArray
/*    char array1[100], array2[100];
    array1[0]= 'a';
    array1[1]= 'b';
    array1[2]= 'c';
    array1[3]= 'g';
    array1[4]= 'f';
    array1[5]= 'h';
    array1[6]= 'i';
    array1[7]= 'l';*/
    //CopyArray(array1,array2);
    //printf("%s\n", array2);
    fclose(fp);
    return 0;
}

