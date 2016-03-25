#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>

/*All Structures*/
typedef struct{
  int x;
  int y;
} Coordinates;

typedef struct gridstate GridState;
struct gridstate{
  //char **state;
  //GridState *state;
  GridState *next;
  GridState *prev;
  int height;
  int currentHeuristic;
  int currentCost;
};
GridState *state_head;

typedef struct car Car;
struct car{
  int id;
  char orientation;
  int length;
  Coordinates coor;
  Car *next;
};

typedef struct node Node;
struct node{
  int currentHeuristic;
  int currentCost;
  Car *cars;
  Node **children;
};

/*Global Vasiables*/
int matrixSize;
char arrayField[10][10];
int copy_idtemp;
Car *TempCar;
Car *head;
Car *curr1;
Car *curr2;

/*Functions*/
void initGrid();
void printGrid();
void insertToGrid(Car *car);
void MakeCar(char *carData, int num);
void getFile(FILE *fp);
int CoorComp(int x, int y, int coor1, int size1, int x2, int y2, int coor2, int size2);
bool CarCheck(int startx, int starty, int orientation, int size);
int CarUp(Car *car);
int CarDown(Car *car);
int CarLeft(Car *car);
int CarRight(Car *car);
void aStar();

/*Main Functions*/
int main () {

    FILE *fp;
    int field[100][100];
    char buff[255];
    
    fp = fopen("a.txt", "r");
    getFile(fp);
    printf("\nmatrix limit %d\n", matrixSize);
    printf("\n");
    printGrid();
    aStar();

    fclose(fp);
    return 0;
}

void initGrid(){
  int i,j;
  for(i=0;i<matrixSize;i+=1){
    for(j=0;j<matrixSize;j+=1){
      arrayField[i][j] = '*';
    }
  }
}

void printGrid(){
  int i,j;
  printf("\n");
  for(i=0;i<matrixSize;i+=1){
    for(j=0;j<matrixSize;j+=1){
      printf("%c",arrayField[i][j]);
    }
    printf("\n");
  }
}

void insertToGrid(Car *car){
  //store Cars first
  int i,ctr;
  
  if(car->orientation==104){ //h
    for(i = car->coor.y,ctr=0;ctr<car->length;i+=1,ctr+=1){
      arrayField[car->coor.x][i] = 'H';
    }
  }
  else if(car->orientation==118){
    for(i = car->coor.x,ctr=0;ctr<car->length;i+=1,ctr+=1){
      arrayField[i][car->coor.y] = 'V';
    }
  }

}

Car* initCar(int id, int x, int y, char c, int len){
  Car* alpha = (Car*)malloc(sizeof(Car));
  alpha->id = id;
  alpha->coor.x = x;
  alpha->coor.y = y;
  alpha->orientation = c;
  alpha->length = len;
}

void MakeCar(char *carData, int num){
  
  int i,j;
  j=0;
  int temp[4];

  for(i = 0; i < 12; i++){
    if(carData[i]!=32 && carData[i]>0 && carData[i]!=10){
      carData[i] = carData[i] - 48;
      // printf("Cardata %d\n", carData[i]);
      temp[j] = carData[i];
      //printf("Temp %d\n", temp[j]);
      j+=1;
    }   
  }
  temp[2] = temp[2] + 48;

  TempCar = initCar(num,temp[1],temp[0],(char) temp[2],temp[3]);
  insertToGrid(TempCar);
  if(num==1){
    head = TempCar;
    head->next = NULL;
    curr1 = head;
  }
  else{
    curr1->next = TempCar;
    curr1 = TempCar;
    curr1->next = NULL;
  }
  
}

void getFile(FILE *fp){

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int id_temp = 1;

  if (fp == NULL)
        exit(EXIT_FAILURE);
  getline(&line, &len, fp);
  matrixSize = line[0]-48;
  initGrid();
  printGrid();  

  while ((read = getline(&line, &len, fp)) != -1) {
        MakeCar(line,id_temp);
        id_temp+=1;
        copy_idtemp = id_temp;
    }

  free(line);

  if (feof(fp))
     printf("\n End of file reached.");
  else
     printf("\n Something went wrong.");
}

int CoorComp(int x, int y, int coor1, int size1, int x2, int y2, int coor2, int size2){
  if (x==x2 || y==y2)
    return 2;
  return 1;
}

bool CarCheck(int startx, int starty, int orientation, int size){
  int check = 1;
  int endx,endy;

  //checks if value of head belongs to range of matrix
  if(startx >= matrixSize || starty >=matrixSize || startx <  0 || starty <0)
    check = 2;

  //checks end of car orientation for horizontal
  if (orientation==104){
    endx= startx + size;
    if(endx >= matrixSize || endx < 0)
      check = 2;
      
  }      
  

  //checks end of car orientation for vertical
  if (orientation=118){
    endy= starty + size;
    if(endy>= matrixSize || endy < 0)
      check = 2;
  }    

  //checks if new movement will collide with other bodies
  curr2 = head;
  while(curr2->next->next!= NULL){
    //so it doesn't check with itself
    if (curr1 == curr2)
      curr2=curr2->next;
    //check = CoorComp(x,y, orientation, size, curr2->coor.x, curr2->coor.y, curr2->orientation, curr2->size)
    check=CoorComp(2,3,104, 2, 2,1,118,3);
    printf("curr1%d, curr2%d\n",curr1->id, curr2->id );
    curr2=curr2->next;
  }
  printf("check: %d\n", check);
  if(check!=1)
    return false;
  return true; 
  
}

int CarUp(Car *car){
  int copy = car->coor.y;
  copy++;
  return 1;
}
int CarDown(Car *car){
  int copy = car->coor.y;
  copy++;
  return 1;
}
int CarLeft(Car *car){
  int copy = car->coor.x;
  copy++;
  return 1;
}
int CarRight(Car *car){
  int copy = car->coor.x;
  copy++;
  return 1;
}

void aStar(){
  curr1 = head;
  while(curr1!=NULL){
    if (CarCheck(2,3,104,2) == true)
      printf("TRUE\n");
    else
      printf("False\n");
    curr1 = curr1->next;
  }
}
