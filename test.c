#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>

int matrixSize;
char arrayField[10][10];
int copy_idtemp;

typedef struct{
  int x;
  int y;
} Coordinates;

typedef struct car Car;
struct car{
  int data[4];
  // char id[1];
  int id;
  char orientation;
  // char orientation[1];
  int length;
  Coordinates coor;
  Car *next;
};

Car mainCar;

typedef struct{
  char **grid;
} GridState;

typedef struct node Node;
struct node{
  int currentHeuristic;
  int currentCost;
  GridState *grid;
  Car *cars;
  Node **children;
};


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

void insertToGrid(Car car){
  //store Cars first
  int i,ctr;
  
  if(car.orientation==104){ //h
    for(i = car.coor.y,ctr=0;ctr<car.length;i+=1,ctr+=1){
      arrayField[car.coor.x][i] = 'H';
    }
    //improvement: design of printing car
  }
  else if(car.orientation==118){
    for(i = car.coor.x,ctr=0;ctr<car.length;i+=1,ctr+=1){
      arrayField[i][car.coor.y] = 'V';
    }
  }

}

void MakeCar(char *carData, int num){
  Car TempCar;
  int i,j;
  j=0;
  
  for(i = 0; i < 12; i++){
    if(carData[i]!=32 && carData[i]>0){
      carData[i] = carData[i] - 48;
      printf("Cardata %d\n", carData[i]);
      mainCar.data[j] = carData[i];
      j+=1;
    }   
  }


  mainCar.id = num;
  mainCar.coor.x = mainCar.data[1];
  mainCar.coor.y = mainCar.data[0];
  mainCar.data[2] = mainCar.data[2] + 48;
  // printf("\n Orientation %c \n",(char)mainCar.data[2]);
  mainCar.orientation = (char) mainCar.data[2];
  mainCar.length = mainCar.data[3];
  printf("\n ID:%d X:%d Y:%d Orie:%c Len:%d",mainCar.id,mainCar.coor.x,mainCar.coor.y,mainCar.orientation,mainCar.length);
  
  insertToGrid(mainCar);
  TempCar=mainCar;


}

/*bool CarCheck(Car car){
  int x = 1;
  if(car.coor.x >= matrixSize || car.coor.y >=matrixSize)
    x = 2;

  if(x==1)
    return true;
  else
    return false; 
}*/

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
  //make Goal car
  // getdelim(&line, &len,'\n',fp);
  // MakeCar(line,id_temp);

  while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        MakeCar(line,id_temp);
        //printf("%s", line);
        id_temp+=1;
        copy_idtemp = id_temp;
    }

  free(line);
   
  if (feof(fp))
     printf("\n End of file reached.");
  else
     printf("\n Something went wrong.");
}

void aStar(){
/*  for(i=0; i<copy_idtemp; i++){
    if (i==mainCar.id)
      CarCheck()
  }*/
  
}

int main () {

    FILE *fp;
    int field[100][100];
    char buff[255];
    
    fp = fopen("a.txt", "r");
    getFile(fp);
    printf("\nmatrix limit %d\n", matrixSize);
    printf("\n");
    printGrid();
    //void aStar()

    // Initialize Grid // 

    fclose(fp);
    return 0;
}
