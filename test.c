#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"



/*Main Functions*/
int main () {

    FILE *fp;
    Node *rootNode;
    int field[100][100];
    char buff[255];
    int i;

    Q_head = NULL;
    Q_curr = NULL;
    Q_orighead = NULL;
    fp = fopen("a.txt", "r");
    getFile(fp);
    
    Car carArray[numberOfCars];

    rootNode = makeRoot(carArray);
    setGoalCoor(carArray[0]);

    // if(i==matrixSize){
    //   Car newCarArray = 
    // }
    printf("\nmatrix limit %d\n", matrixSize);
    printf("\n");
    printGrid();
    //push(rootNode); // for bfs
    //BFStree(carArray);
    printf("NUMBER OF CARS: %d\n", numberOfCars);
    freeQueues();
    Q_head = NULL;
    Q_curr = NULL;
    Q_orighead = NULL;
    insert(rootNode); // for astar
    //aStarTree();
    BFStree(carArray);
    fclose(fp);
    return 0;
}

