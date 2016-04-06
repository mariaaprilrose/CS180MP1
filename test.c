#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include <time.h>


/*Main Functions*/
int main () {
    clock_t begin, end;
    double time_spent;
    FILE *fp;
    Node *rootNode;
    int field[100][100];
    char buff[255];
    int i;

    fp = fopen("a.txt", "r");
    getFile(fp);
    
    Car carArray[numberOfCars];

    rootNode = makeRoot(carArray);
    setGoalCoor(carArray[0]);

    /*Q_head = NULL;
    Q_curr = NULL;
    Q_orighead = NULL;
    printf("1) BFS\n");
    popCtr = 0;
    push(rootNode); // for bfs
    begin = clock();
    BFStree(carArray);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Expanded %d nodes\n",popCtr);
    printf("Time spent: %f seconds\n",time_spent);
    freeQueues(); */

    
    /*printf("2) A* with blocking heuristic\n");
    Q_head = NULL;
    Q_curr = NULL;
    Q_orighead = NULL;
    popCtr = 0;
    insert(rootNode); // for astar
    begin = clock();
    aStarTree(2);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Expanded %d nodes\n",popCtr);
    printf("Time spent: %f seconds\n",time_spent);
    freeQueues(); */

    printf("3) A* with advance heuristic\n");   
    Q_head = NULL;
    Q_curr = NULL;
    Q_orighead = NULL;
    popCtr = 0;
    insert(rootNode);
    begin = clock();
    aStarTree(3);
    freeQueues();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Expanded %d nodes\n",popCtr);
    printf("Time spent: %f seconds\n",time_spent);

    fclose(fp);
    return 0;
}

