#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include <errno.h>
ssize_t getdelim(char **linep, size_t *n, int delim, FILE *fp){
    int ch;
    size_t i = 0;
    if(!linep || !n || !fp){
        errno = EINVAL;
        return -1;
    }
    if(*linep == NULL){
        if(NULL==(*linep = malloc(*n=128))){
            *n = 0;
            errno = ENOMEM;
            return -1;
        }
    }
    while((ch = fgetc(fp)) != EOF){
        if(i + 1 >= *n){
            char *temp = realloc(*linep, *n + 128);
            if(!temp){
                errno = ENOMEM;
                return -1;
            }
            *n += 128;
            *linep = temp;
        }
        (*linep)[i++] = ch;
        if(ch == delim)
            break;
    }
    (*linep)[i] = '\0';
    return !i && ch == EOF ? -1 : i;
}
ssize_t getline(char **linep, size_t *n, FILE *fp){
    return getdelim(linep, n, '\n', fp);
}


int zeroHeuristic(){
  return 0;
}

int blockHeuristic(Car carArray [], int goalX, int goalY){
  int heuristic = 1;
  int carsBlocking = 0;
  int i;
  
  //Get number of blocking cars
  for(i = 1; i < numberOfCars; i++){
    if(carArray[i].orientation == carArray[0].orientation){ // might never happen
      if(carArray[i].orientation == 'h'){
        if(goalX > carArray[i].coor.x) carsBlocking++;
      }
      else{
        if(goalY > carArray[i].coor.y) carsBlocking++;
      }
    }
    else{
      if(carArray[i].orientation == 'h'){ // vertical yung goal car
        if((carArray[0].coor.y + carArray[0].length - 1) < carArray[i].coor.x){ // kung nasa baba ng goal car yung ith car
          if(carArray[i].coor.x <= goalX && (carArray[i].coor.x + carArray[i].length - 1) >= goalX){
            carsBlocking++;
          }
        }
      }
      else{
        if((carArray[0].coor.x + carArray[0].length - 1) < carArray[i].coor.x){ // kung nasa kanan ng goal car yung ith car
          if(carArray[i].coor.y <= goalY && (carArray[i].coor.y + carArray[i].length - 1) >= goalY){
            carsBlocking++;
          }
        }
      }
    }
  }
  //End get number of blocking cars

  heuristic += carsBlocking;
  return heuristic;
}

int advanceHeuristic(){
  
}

/*Inputs: *mainCar - goalCar; the first car in carArray
          goalX, goalY - coordinates of exit point 
  Returns: True, if it has reached goal state
           else, false
*/
bool isGoalState(Car *mainCar, int goalX, int goalY){
  if((mainCar->orientation == 'v') && ((mainCar->coor.y + mainCar->length - 1) >= goalY)){
    if((mainCar->coor.y + mainCar->length - 1) > goalY) printf("Car exceeded goal point.");
    return true;
  }
  if((mainCar->orientation == 'h') && ((mainCar->coor.x + mainCar->length - 1) >= goalX)){
    if((mainCar->coor.x + mainCar->length - 1) > goalX) printf("Car exceeded goal point.");
    return true;
  }
  else return false;
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
  int i;

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
    numberOfCars = id_temp-1;
  free(line);

  if (feof(fp))
     printf("\n End of file reached.");
  else
     printf("\n Something went wrong.");

}

void createCarArray(Car* carList){
  int i;
  curr1 = head; 
  for(i=0;i<matrixSize;i+=1){
    carList[i] = *curr1;
    printf("Create Car Array fxn %d\n",carList[i].id);
    curr1 = curr1->next;
  }
}

int CoorComp(int x, int y, int coor1, int size1, int x2, int y2, int coor2, int size2){
  int i,j, copy_x=x,copy_y=y,copy_x2=x2,copy_y2=y2;
  for(i=0; i<size1; i++){
    if (coor1 == 104){
      y=copy_y;
      y=y+i;
    }
    else if(coor1==118){
      x=copy_x;
      x=x+i;
    }
    for(j=0; j<size2; j++){
      if (coor1 == 104){
        y2=copy_y2;
        y2=y2+j;
      }
      else if(coor1==118){
        x2=copy_x2;
        x2=x2+j;
      }
      if (x==x2 || y==y2)
        return 2;
    }
  }
  return 1;
}

bool CarCheck(int startx, int starty, Car carArray[], int car){
  int check = 1, i;
  int endx,endy, orientation=carArray[car].orientation,  size=carArray[car].length; 

//  printf("Start %d %d %d %d\n", startx, starty, orientation, size );
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

  printf("car %d\n", car );
  for(i=0; i<=numberOfCars; i++){
    if(car==i)
      i++;
    check=CoorComp(startx, starty, orientation, size, carArray[i].coor.x, carArray[i].coor.y, carArray[i].orientation, carArray[i].length);
  }


  printf("check: %d\n", check);
  if(check!=1)
    return false;
  return true; 
  
}

int CarUp(Car carArray[], int car){
  int copy = carArray[car].coor.x;
  copy--;
  if(carArray[car].orientation==104)
    return 0;

  if(CarCheck(copy, carArray[car].coor.y, carArray, car) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}

int CarDown(Car carArray[], int car){
  int copy = carArray[car].coor.x;
  copy++;
  if(carArray[car].orientation==104)
    return 0;

  if(CarCheck(copy, carArray[car].coor.y, carArray, car) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}

int CarLeft(Car carArray[], int car){
  int copy = carArray[car].coor.y;
  copy--;

  if(carArray[car].orientation==118)
    return 0;
  if(CarCheck(carArray[car].coor.x, copy, carArray, car) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}

int CarRight(Car carArray[], int car){
  int copy = carArray[car].coor.y;
  copy++;

  if(carArray[car].orientation==118)
    return 0;
  
  if(CarCheck(carArray[car].coor.x, copy, carArray, car) == true){
    printf("TRUE\n");
    return 1;
  }
  else{
    printf("FALSE\n");
    return 0;
  }
}



void CopyCar(Car array1[], Car array2[]){
//not sure if fucking right :))
  int i;
 // printf("%s\n", array1);
//  printf("%ld\n", sizeof(array1)/sizeof(int));
  for(i=0; i<=(sizeof(array1)/sizeof(array1[0])); i++){
    printf("%c\n", array1[i].id);
    //array2[i]=(Car*)malloc(sizeof(Car));
    array2[i]= array1[i];
  }
}

Node* initState(Node* state,int lvl, int heur, int cost, int id, int x, int y){
  state->parent = NULL;
  state->children = NULL;
  state->level = 0;
  state->currHeuristic = 0;
  state->currCost = 0;
  return state;
  //Node->carArray = (Node*)malloc
}

void push(Node *pointer){//, int data){
  // data was only used to check the content of the push
  if (Q_head==NULL){
      printf("Qhead is null\n");
      Q_head=(Queue*)malloc(sizeof(Queue));
      Q_head->ptr = pointer;
      Q_head->next= NULL;
      //Q_head->laman=data;
      Q_curr = Q_head;
  }
  else{
    printf("I CAN PUSH BITCH\n");
      Q_curr->next= (Queue*)malloc(sizeof(Queue));
      Q_curr= Q_curr->next;
      Q_curr->ptr = pointer;
      Q_curr->next= NULL; 
      //Q_curr->laman=data;    
  }

}

Node* pop(){//EDIT: this is copy pasted from internet
  Queue *pointer;
  
  // if (Q_head==NULL){
  //   printf("WALANG LAMAN BITCH\n");   
  // }
  // else{
  //   printf("++++ Q HEAD %d\n", Q_head->ptr->level);
  //   // pointer = Q_curr;
  //   // pointer = Q_curr->next;
  //   // // // printf("++++ Q HEAD %d\n", pointer->next->ptr->carArray[0].id);
  //   // // pointer=pointer->next;
  //   // // Q_head=Q_head->next;
  //   // //pointer = Q_head->next;
  
  pointer = Q_head;
  Q_head = Q_head->next;
  if(Q_head==NULL){
    //printf("++++ Q HEAD %d\n",Q_head->ptr->level);
    printf("WALANG LAMAN BITCH\n");
    Q_curr = NULL;
  }
  else{
    //  Q_curr = Q_head;
    pointer->next = NULL;
  }
  printf("++++ BEFORE RETURN POINTER->PTR->LEVEL IS %d\n",pointer->ptr->level);
  return pointer->ptr;
}

void printQ(){
  Queue *temp;
  temp = Q_head;
  while(temp!=NULL){
    printf("Level Of Queue%d\n", temp->laman);
    temp=temp->next;
  }
}

bool mainCarNotOnExit(Car mainCar){

}

Node* makeNewNode(Car carArray[], Node *parent){
  Node *node = (Node*)malloc(sizeof(Node));
  node->parent = parent;
  node->children = NULL;
  
  node->level = parent->level + 1;
  node->currHeuristic = 0;//get heuristic here
  node->currCost = 0;
  node->carArray = carArray;
  
}

void moveUp(Car carArray[], int index){//struct
  printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.x--;
  printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveDown(Car carArray[], int index){//struct
  printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.x++;
  printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveLeft(Car carArray[], int index){//struct
  printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.y--;
  printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveRight(Car carArray[], int index){//struct
  printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.y++;
  printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void BFS(Node *currNode){// make queue
  int i,j;
  Node *newNode;

/*  for(i=0;i<3;i++){
    push(NULL, i);
  }
  printQ();*/
  if(currNode!=NULL){
    for(i=0;i<numberOfCars;i++){//check all allowed moves per car (U/D,L/R)
      printf("Checking allowed moves\n");
      if(CarUp(currNode->carArray,i)==1){//if UP move valid
        carArray = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
        CopyCar(currNode->carArray, carArray);
        moveUp(carArray,i);
        newNode=makeNewNode(carArray, currNode);
        push(newNode);
      }
    }
  }
  else if(currNode==NULL)
    printf("+***+ Current node is NULL so no more node to BFS\n");
}

void aStar(Node *node){
  CarUp(node->carArray, 4);  
}

void makeRoot(Car carArray[]){
  int i;
  Node *rootNode = (Node*)malloc(sizeof(Node));
  rootNode->parent = NULL;
  rootNode->children = NULL;
  rootNode->level=0;
  rootNode->currHeuristic=0;//get heuristic here
  rootNode->currCost=0;
  rootNode->carArray = carArray;
  createCarArray(rootNode->carArray);

  printf("\n");
  for(i=0;i<matrixSize;i++){
    printf("CAR ARRAY ID #%d (%d,%d)\n", rootNode->carArray[i].id,rootNode->carArray[i].coor.x,rootNode->carArray[i].coor.y);
  }

  /*n_head = rootNode;
  n_curr = n_head;
*/push(rootNode);
  printf("mAKE ROOT PIECE OF SHIT");
}

