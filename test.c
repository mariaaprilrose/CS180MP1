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
    Car carList[numberOfCars];

    Node *rootNode = (Node*)malloc(sizeof(Node));
    rootNode->parent = NULL;
    rootNode->children = NULL;
    rootNode->level=0;
    rootNode->currHeuristic=0;//get heuristic here
    rootNode->currCost=0;
    rootNode->carArray = carList;
    createCarArray(rootNode->carArray);

    //add rootnode to queue
    insertToQueue(rootNode);
    
    printf("\n");
    for(i=0;i<matrixSize;i++){
      printf("CAR ARRAY ID #%d (%d,%d)\n", rootNode->carArray[i].id,rootNode->carArray[i].coor.x,headNode->carArray[i].coor.y);
    }
    
    // if(i==matrixSize){
    //   Car newCarArray = 
    // }
    printf("\nmatrix limit %d\n", matrixSize);
    printf("\n");
    printGrid();
//////////////ASTAR SEARCH

    n_head= headNode;
    n_curr= n_head;
    aStar(n_curr);


    // trial of CopyArray
    char array1[100], array2[100];
    array1[0]= 'a';
    array1[1]= 'b';
    array1[2]= 'c';
    array1[3]= 'g';
    array1[4]= 'f';
    array1[5]= 'h';
    array1[6]= 'i';
    array1[7]= 'l';
    //CopyArray(array1,array2);
    //printf("%s\n", array2);
    fclose(fp);
    return 0;
}

