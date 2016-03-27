#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int zeroHeuristic(){
  return 0;
}

int blockHeuristic(){
  int carsBlocking = 1;
  carsBlocking+=1;
  return carsBlocking;
}

int advanceHeuristic(){
  
}

int cost(){
  
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
  int i,j, copy_x=x,copy_y=y,copy_x2=x2,copy_y2=y2;
  for(i=0; i<size1; i++){
    if (coor1 == 104){
      x=copy_x;
      x=x+i;
    }
    else if(coor1==118){
      y=copy_y;
      y=y+i;
    }
    for(j=0; j<size2; j++){
      if (coor1 == 104){
        x2=copy_x2;
        x2=x2+j;
      }
      else if(coor1==118){
        y2=copy_y2;
        y2=y2+j;
      }
      if (x==x2 || y==y2)
        return 2;
    }
  }
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
    endx= startx + (size-1);
    if(endx >= matrixSize || endx < 0)
      check = 2;
      
  }      
  

  //checks end of car orientation for vertical
  if (orientation=118){
    endy= starty + (size-1);
    if(endy>= matrixSize || endy < 0)
      check = 2;
  }    

  //checks if new movement will collide with other bodies
  curr2 = head;
  while(curr2!= NULL){
    //so it doesn't check with itself
    if (curr1 == curr2)
      curr2=curr2->next;
    if (curr2 ==NULL)
      break;
    //check = CoorComp(x,y, orientation, size, curr2->coor.x, curr2->coor.y, curr2->orientation, curr2->size)
    check=CoorComp(0,3,104, 2, 3,1,118,3);
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

  if(CarCheck(car->coor.x, copy, car->orientation, car->length) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}

int CarDown(Car *car){
  int copy = car->coor.y;
  copy--;

  if(CarCheck(car->coor.x, copy, car->orientation, car->length) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}
int CarLeft(Car *car){
  int copy = car->coor.x;
  copy--;

  if(CarCheck(copy, car->coor.y, car->orientation, car->length) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}
int CarRight(Car *car){
  int copy = car->coor.x;
  copy++;
  if(CarCheck(copy, car->coor.y, car->orientation, car->length) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}

void aStar(){
  curr1 = head;
  int ifmove;
  //returns 1 to ifmove if move is possible; no storing of new values yet
  ifmove= CarUp(curr1);


  //while(curr1!=NULL){
  //  if (CarCheck(2,3,104,2) == true)
    //  printf("TRUE\n");
  //  else
    //  printf("False\n");
  //  curr1 = curr1->next;
  //}
}