#include <stdio.h>
#include <string.h>

typedef struct{
  int x;
  int y;
} Coordinates;

typedef struct{
  char id[1];
  char orientation[1];
  Coordinates *coor;
} Car;

typedef struct{
  char **grid;
} GridState;

typedef struct Node{
  int currentHeuristic = 0;
  int currentCost = 0;
  GridState *grid;
  Car *cars;
  Node **children;
} Node;

void getFile(FILE *fp, int *matrix){

  int ch = getc(fp);
  char c;
  ch = ch - 48;
  *matrix = ch;
  do {
    ch = getc(fp);
    
    /// for new lines
    if (ch == 10){
        ch = getc(fp);
        printf("\n");
    }

    /// for spaces == 32, for EOF <-1
    if (ch != 32 && ch > 0){ 
        ch = ch - 48;
        printf(" %d  ", ch );
    }    
  } while (ch != EOF); 
   
  if (feof(fp))
     printf("\n End of file reached.");
  else
     printf("\n Something went wrong.");    
}

int main () {

    FILE *fp;
    int field[100][100];
    char buff[255];
    int matrix;

    fp = fopen("a.txt", "r");
    /*getFile(fp, &matrix);
    printf("\nmatrix limit %d\n", matrix);*/

    // Initialize Grid // 

    fclose(fp);
    return 0;
}
