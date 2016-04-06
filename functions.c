#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
/* remove this block before passing; for windows only; copy pasted from the net */
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
/*END remove this block before passing; for windows only; copy pasted from the net END*/

void freeQueues(){
  Queue *q;
  Queue *nextQ;
  q = Q_head;

  while(q != NULL){
    nextQ = q->next;
    free(q);
    q = nextQ;
  }
}

void setGoalCoor(Car mainCar){
  if(mainCar.orientation == 'v'){
    goalX = mainCar.coor.x;
    goalY = matrixSize-1;
  }
  else{
    goalY = mainCar.coor.y;
    goalX = matrixSize-1;
  }
}

int zeroHeuristic(){
  return 0;
}

int blockHeuristic(Car carArray []){
  int heuristic = 1;
  int carsBlocking = 0;
  int i;
  
  //Get number of blocking cars
  for(i = 1; i < numberOfCars; i++){
    if(carArray[i].orientation == carArray[0].orientation){ // might never happen
      if(carArray[i].orientation == 'h'){
        if((goalX > carArray[i].coor.x) && (carArray[i].coor.y == goalY) && (carArray[i].coor.x > carArray[0].coor.x)){
          carsBlocking++;
        }
      }
      else{
        if(goalY > carArray[i].coor.y && carArray[i].coor.x == goalX && carArray[i].coor.y > carArray[0].coor.y){
          carsBlocking++;
        }
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

int advanceHeuristic(Car carArray[]){
  int i;
  int heuristic = 0;
  /*if(carArray[0].orientation == 'h'){
    heuristic = goalX - ( carArray[0].coor.x + carArray[0].length-1 );
  }
  if(carArray[0].orientation == 'v'){
    heuristic = goalY - ( carArray[0].coor.y + carArray[0].length-1 );
  }*/
  int blockHeur;
  blockHeur = blockHeuristic(carArray);

  /*if(carArray[0].orientation == 'v'){
    for(i=1;i<numberOfCars;i++){
      if(carArray[0].coor.y == carArray[i].coor.y){
        heuristic++;
      }
    } 
  }*/

  if(carArray[0].orientation == 'h'){
    
    if(carArray[0].coor.x == 0){
      for(i=1;i<numberOfCars;i++){
        if(carArray[0].coor.x == carArray[i].coor.x){
          heuristic++;
          heuristic = heuristic+blockHeur;
          printf("Heuristic:%d\n",heuristic);
          return heuristic;
        }
      }
    }
    else{
      for(i=1;i<numberOfCars;i++){
        if(carArray[0].coor.x == carArray[i].coor.x){
          heuristic++;
          //printf("Heuristic:%d\n",heuristic);
          i=numberOfCars;
        }
      }

      for(i=carArray[0].coor.x;i>0;i--){
        if(carArray[0].coor.x == carArray[i].coor.x){
          heuristic++;
          heuristic = heuristic+blockHeur;
          printf("Heuristic:%d\n",heuristic);
          return heuristic;
        }
      }
    }
  }

  if(carArray[0].orientation == 'v'){
    if(carArray[0].coor.y == 0){
      for(i=1;i<numberOfCars;i++){
        if(carArray[0].coor.y == carArray[i].coor.y){
          heuristic++;
          heuristic = heuristic+blockHeur;
          printf("Heuristic:%d\n",heuristic);
          return heuristic;
        }
      }
    }

    else{
      for(i=1;i<numberOfCars;i++){
        if(carArray[0].coor.y == carArray[i].coor.y){
          heuristic++;
          i=numberOfCars;
        }
      }

      for(i=carArray[0].coor.y;i>0;i--){
        if(carArray[0].coor.y == carArray[i].coor.y){
          heuristic++;
          heuristic = heuristic+blockHeur;
          printf("Heuristic:%d\n",heuristic);
          return heuristic;
        }
      }
    }

  }

  //heuristic = heuristic+blockHeur;

  return heuristic;
}

/*Inputs: *mainCar - goalCar; the first car in carArray
          goalX, goalY - coordinates of exit point 
  Returns: True, if it has reached goal state
           else, false
*/
bool isGoalState(Car mainCar){
  //printf("%c Y:%d GoalY:%d Length:%d\n",mainCar.orientation,mainCar.coor.y,mainCar.length-1);
  //printf("%c X:%d GoalX:%d Length:%d\n",mainCar.orientation,mainCar.coor.x,goalX,mainCar.length-1);
  if((mainCar.orientation == 'v') && ((mainCar.coor.y + mainCar.length - 1) >= goalY)){
    //printf("%c Y:%d GoalY:%d Length:%d\n",mainCar.orientation,mainCar.coor.y,goalY,mainCar.length-1);
    if((mainCar.coor.y + mainCar.length - 1) > goalY) printf("Car exceeded goal point.");
    return true;
  }
  if((mainCar.orientation == 'h') && ((mainCar.coor.x + mainCar.length - 1) >= goalX)){
    //printf("%c X:%d GoalX:%d Length:%d\n",mainCar.orientation,mainCar.coor.x,goalX,mainCar.length-1);
    if((mainCar.coor.x + mainCar.length - 1) > goalX) printf("Car exceeded goal point.");
    return true;
  }
  else return false;
}

void printOutput(int carMoved, char moveDir, Node *parent){
  Stack *temp;
  Stack *newS;
  Node *tempNode;

  int prevCarMoved = -1;
  char prevMoveDir = ' ';
  int moveCtr = 0;
  int i = 0;

  /*Create Stack*/
  temp = (Stack*)malloc(sizeof(Stack));
  temp->carMoved = carMoved;
  temp->moveDir = moveDir;
  temp->next = NULL;
  S_top = temp; 

  tempNode = parent;
  while(tempNode->parent != NULL){
    temp = (Stack*)malloc(sizeof(Stack));
    temp->carMoved = tempNode->carMoved;
    temp->moveDir = tempNode->moveDir;
    temp->next = S_top;
    S_top = temp;

    tempNode = tempNode->parent; 
    i++;
  }
  printf("\n\n\nFinished creating stack length %d. Printing stack.\n\n", i);

  /* Print Stack */
  while(S_top != NULL){
    if(prevCarMoved == S_top->carMoved && prevMoveDir == S_top->moveDir){
      moveCtr++;
    }
    else{
      if(moveCtr != 0){
        printf("%d %c %d\n", prevCarMoved, prevMoveDir, moveCtr);
        prevCarMoved = S_top->carMoved;
        prevMoveDir = S_top->moveDir;
        moveCtr = 1; 
      }
      else{
        prevCarMoved = S_top->carMoved;
        prevMoveDir = S_top->moveDir;
        moveCtr = 1; 
      }
    }

    temp = S_top;
    S_top = S_top->next;
    free(temp);
  }

  printf("%d %c %d", prevCarMoved, prevMoveDir, moveCtr);
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
    for(i = car->coor.x,ctr=0;ctr < car->length;i+=1,ctr+=1){
      arrayField[car->coor.y][i] = 'H';
    }
  }
  else if(car->orientation==118){
    for(i = car->coor.y,ctr=0;ctr<car->length;i+=1,ctr+=1){
      arrayField[i][car->coor.x] = 'V';
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

  TempCar = initCar(num,temp[0],temp[1],(char) temp[2],temp[3]);
  //insertToGrid(TempCar);
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
  //initGrid();
  //printGrid();  

  while ((read = getline(&line, &len, fp)) != -1) {
        MakeCar(line,id_temp);
        id_temp+=1;
        copy_idtemp = id_temp;
    }
    numberOfCars = id_temp-1;
    //printf("Number of cars: %d\n",numberOfCars);
  free(line);

  if (feof(fp))
     printf("\n End of file reached.\n");
  else
     printf("\n Something went wrong.\n");

}

void createCarArray(Car* carList){
  int i;
  curr1 = head; 
  for(i=0;i<numberOfCars;i+=1){
    carList[i] = *curr1;
    //printf("Create Car Array fxn %d\n",carList[i].id);
    curr1 = curr1->next;
  }
}

//compares coordinates of two cars
int CoorComp(int x, int y, int coor1, int size1, int x2, int y2, int coor2, int size2){
  int i,j, copy_x=x,copy_y=y,copy_x2=x2,copy_y2=y2;
  //CoorComp(startx, starty, orientation, size, carArray[i].coor.x, 
  //         carArray[i].coor.y, carArray[i].orientation, carArray[i].length);
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
      if (coor2 == 104){
        x2=copy_x2;
        x2=x2+j;
        
      }
      else if(coor2==118){
        y2=copy_y2;
        y2=y2+j;
      }
      if (x==x2 && y==y2)
        return 2;
    }
  }
  return 1;
}

bool CarCheck(int startx, int starty, Car carArray[], int car){
  int check = 1, i;
  int endx,endy, orientation=carArray[car].orientation,  size=carArray[car].length; 
  
  //checks if value of head belongs to range of matrix

  if(startx >= matrixSize || starty >= matrixSize || startx <  0 || starty <0){
    if(startx == goalX && starty == goalY);
    else{
      check = 2;
      return false;
    }
  }
  
  if (orientation==104){
    endx= startx + (size-1);
    if(endx >= matrixSize || endx < 0){
      if(startx == goalX && starty == goalY);
      else{
        check = 2;
        return false;
      }
    }
  }      
  else if (orientation==118){
    endy= starty + (size-1);
    if(endy>= matrixSize || endy < 0){
      if(startx == goalX && starty == goalY);
      else{
        check = 2;
        return false;
      }
    }
  }    

  //printf("Car %d\n", car+1 );
  for(i=0; i<numberOfCars; i++){//from i<=numberOfCars
    if(car==i)
      i++;
    if(i==numberOfCars) break;
    check=CoorComp(startx, starty, orientation, size, carArray[i].coor.x, carArray[i].coor.y, carArray[i].orientation, carArray[i].length);
    if(check==2) return false;
   }
   return true;
}

int CarUp(Car carArray[], int car){
  int copy = carArray[car].coor.y;
  copy--;
  if(carArray[car].orientation == 'h')
    return 0;

  if(CarCheck(carArray[car].coor.x, copy, carArray, car) == true){
    //printf("1 Move UP\n");
    return 1;
  }
  else{
    return 0;
  }
}

int CarDown(Car carArray[], int car){
  int copy = carArray[car].coor.y;
  copy++;
  if(carArray[car].orientation == 'h')
    return 0;

  if(CarCheck(carArray[car].coor.x, copy, carArray, car) == true){
    //printf("1 Move DOWN\n");
    return 1;
  }
  else{
    return 0;
  }
}

int CarLeft(Car carArray[], int car){
  int copy = carArray[car].coor.x;
  copy--;

  if(carArray[car].orientation=='v')
    return 0;

  if(CarCheck(copy, carArray[car].coor.y, carArray, car) == true){
    //printf("1 Move LEFT\n");
    return 1;
  }
  else{
    return 0;
  }
}

int CarRight(Car carArray[], int car){
  int copy = carArray[car].coor.x;
  copy++;

  if(carArray[car].orientation=='v')
    return 0;
  
  if(CarCheck(copy, carArray[car].coor.y, carArray, car) == true){
    //printf("1 Move RIGHT\n");
    return 1;
  }
  else{
    return 0;
  }
}



void CopyCar(Car array1[], Car array2[]){
  int i, j;
  for(i=0; i< numberOfCars; i++){
    //printf("i = %d\n", i);
    //printf("ID: %d\n", array1[i].id);
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
      //printf("Qhead is null\n");
      Q_head = (Queue*)malloc(sizeof(Queue));
      Q_orighead = Q_head;
      Q_head->ptr = pointer;
      Q_head->next= NULL;
      //Q_head->laman=data;
      Q_curr = Q_head;
  }
  else{
    //printf("I CAN PUSH\n");
      Q_curr->next = (Queue*)malloc(sizeof(Queue));
      Q_curr = Q_curr->next;
      Q_curr->ptr = pointer;
      Q_curr->next= NULL; 
      //Q_curr->laman=data;    
  }

}

Node* pop(void){//EDIT: this is copy pasted from internet
  Queue *pointer;
  popCtr++;
  pointer = Q_head;
  Q_head = Q_head->next;
  if(Q_head==NULL){
    // printf("WALANG LAMAN BITCH\n");
    Q_curr = NULL;
  }
  else{
  }
  printf("++++ BEFORE RETURN POINTER->PTR->LEVEL IS %d\n",pointer->ptr->level);
  //printf("Popped cost: %d\n",pointer->ptr->currCost);
  return pointer->ptr;
}

void printQ(){
  Queue *temp;
  temp = Q_head;
  while(temp!=NULL){
    //printf("Level Of Queue%d\n", temp->laman);
    temp=temp->next;
  }
}


Node* makeNewNode(Car carArray[], Node *parent, int carMoved, char moveDir, int type){
  Node *node = (Node*)malloc(sizeof(Node));
  node->parent = parent;
  node->children = NULL;
  
  node->level = parent->level + 1;

  //Get heuristic//
  //If type == 1, BFS; if type == 2, block heuristic; if type == 3, heuristic2
  if(type == 1) node->currHeuristic = 0;
  else if(type == 2) node->currHeuristic = blockHeuristic(carArray);
  else if(type == 3) node->currHeuristic = advanceHeuristic(carArray);

  node->currCost = parent->currCost + 1;
  //printf("Cost: %d\n",node->currCost);
  node->carArray = carArray;
  node->carMoved = carMoved;
  node->moveDir = moveDir;

  return node;
}


/* Input: carArray - array of cars of node to be checked
   Returns: true if configuration was already existing in previous nodes, else returns false
*/
bool configExists(Car carArray[]){
  Queue *current = Q_orighead;
  Car *currentCars; 
  int i;

  while(current != NULL){
    currentCars = current->ptr->carArray; 
    for(i = 0; i < numberOfCars; i++){
      if((currentCars[i].coor.x == carArray[i].coor.x) && (currentCars[i].coor.y == carArray[i].coor.y)){
        if(i == (numberOfCars - 1)) return true; // if last car na sya sa array, tapos equal pa rin yung coors, ibig sabihin pareho sila ng content sa carArray
      }
      else i = numberOfCars;
    }
    current = current->next;
  }
  return false;
}

// To be used for a*
// Inserts node into 'list' (using structure Queue)
void insert(Node *node){
  Queue *current = Q_head;
  Queue *prev = NULL;
  Node *tempNode;
  Queue *tempQ;

  if(current == NULL){
    //printf("Inserting into empty list\n");
    Q_head = (Queue*)malloc(sizeof(Queue));
    
    if(Q_orighead == NULL) Q_orighead = Q_head;
    else Q_orighead->next = Q_head;

    Q_head->ptr = node;
    Q_head->next= NULL;
    Q_curr = Q_head;
  }
  else{
    while(current != NULL){
      tempNode = current->ptr;
      if((tempNode->currHeuristic + tempNode->currCost) > (node->currHeuristic + node->currCost)){
        tempQ = (Queue*)malloc(sizeof(Queue));
        tempQ->ptr = node;

        if(prev == NULL){ //Kung mas maliit yung heuristic+cost ni new node kay head node
          tempQ->next = Q_head;
          Q_head = tempQ;
        }
        else{
          prev->next = tempQ;
          tempQ->next = current; 
        }
        return;
      }
      
      prev = current;
      current = current->next;
    }
    //Kung umabot na sa dulo, hindi pa naiinsert (meaning: mas malaki heuristic+cost ni new node sa lahat ng existing nodes)
    prev->next = (Queue*)malloc(sizeof(Queue));
    Q_curr = prev->next;
    Q_curr->ptr = node;
    Q_curr->next= NULL; 
  }
}

void moveUp(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.y--;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveDown(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.y++;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveLeft(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.x--;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveRight(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.x++;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

bool BFS(Node *currNode){// make queue
  int i,j;
  Node *newNode;
  if(currNode==NULL);
    //printf("+***+ Current node is NULL so no more node to BFS\n");
  else{
    for(i=0;i<numberOfCars;i++){//check allprintf allowed moves per car (U/D,L/R)
      //printf("+++++++++++++++++++++Checking allowed moves for Car %d+++++++++++++++++++++\n",currNode->carArray[i].id);
      if(currNode->carArray[i].orientation==118){
         
         if(CarUp(currNode->carArray,i)==1){//if UP move valid
          cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, cars);
          moveUp(cars,i);

          if(isGoalState(cars[0])){
            printf("Reached goal state\n");
            printOutput(i+1, 'U', currNode);
            return true;
          }
          if(configExists(cars)==false){
            newNode=makeNewNode(cars, currNode, i+1, 'U', 1);
            push(newNode);
          }
        }
        if(CarDown(currNode->carArray,i)==1){//if DOWN move valid
          cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, cars);
          moveDown(cars,i);

          if(isGoalState(cars[0])){
            printf("Reached goal state\n");
            printOutput(i+1, 'D', currNode);
            return true;
          }

          if(configExists(cars)==false){
            newNode=makeNewNode(cars, currNode, i+1, 'D', 1);
            push(newNode);
          }
        } 
      }
      else if(currNode->carArray[i].orientation==104){
        if(CarLeft(currNode->carArray,i)==1){//if UP move valid
          cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, cars);
          moveLeft(cars,i);

          if(isGoalState(cars[0])){
            printf("Reached goal state\n");
            printOutput(i+1, 'L', currNode);
            return true;
          }

          if(configExists(cars)==false){
            newNode=makeNewNode(cars, currNode, i+1, 'L', 1);
            push(newNode);
          }
        }

        if(CarRight(currNode->carArray,i)==1){//if UP move valid
          cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, cars);
          moveRight(cars,i);

          if(isGoalState(cars[0])){
            printf("Reached goal state\n");
            printOutput(i+1, 'R', currNode);
            return true;
          }

          if(configExists(cars)==false){
            newNode=makeNewNode(cars, currNode, i+1, 'R', 1);
            push(newNode);
          }
        }
      }
    }
  }

  return false;
}

//Make sure Queue* global vars are set to NULL before first call of aStar
bool aStar(Node *currNode,int type){
  int i, j;
  Node *newNode;

  if (currNode == NULL){
    //printf("+***+ Current node is NULL so no more node for A*\n");
  }  
  else{
    /*for(j = 0; j <numberOfCars; j++){
      printf("car %d at (%d, %d)\n", j, currNode->carArray[j].coor.x, currNode->carArray[j].coor.y);
    }*/
    for(i=0;i<numberOfCars;i++){//check allprintf allowed moves per car (U/D,L/R)
      /*printf("+++++++++++++++++++++Checking allowed moves for Car %d+++++++++++++++++++++\n",currNode->carArray[i].id);
      printf("FOR CAR %d:\n", i);

      printf("check up\n");*/

      if(CarUp(currNode->carArray,i)==1){//if UP move valid
        //printf("Car %d: up\n",i);
        cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
        CopyCar(currNode->carArray, cars);
        moveUp(cars,i);

        if(isGoalState(cars[0])){
          printf("Reached goal state\n");
          printOutput(i+1, 'U', currNode);
          return true;
        }
        if(configExists(cars));
        else{
          printf("Added a new node: Car %d, move up\n", i);
          newNode=makeNewNode(cars, currNode, i+1, 'U', type);
          insert(newNode);
        }
      }

      if(CarDown(currNode->carArray,i)==1){//if DOWN move valid
        //printf("Car %d: down\n",i);
        cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
        CopyCar(currNode->carArray, cars);
        moveDown(cars,i);

        if(isGoalState(cars[0])){
          printf("Reached goal state\n");
          printOutput(i+1, 'D', currNode);
          return true;
        }

        if(configExists(cars));
        else{

          printf("Added a new node: Car %d, move down\n", i);
          newNode=makeNewNode(cars, currNode, i+1, 'D', type);
          insert(newNode);
        }
      }

      if(CarLeft(currNode->carArray,i)==1){//if left move valid
        //printf("Car %d: left\n",i);
        cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
        CopyCar(currNode->carArray, cars);
        moveLeft(cars,i);
        
        if(isGoalState(cars[0])){
          printf("Reached goal state\n");
          printOutput(i+1, 'L', currNode);
          return true;
        }

        if(configExists(cars));
        else{

          printf("Added a new node: Car %d, move left\n", i);
          newNode=makeNewNode(cars, currNode, i+1, 'L', type);
          insert(newNode);
        }
      }

      if(CarRight(currNode->carArray,i)==1){//if right move valid
        //printf("Car %d: right\n",i);
        cars = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
        CopyCar(currNode->carArray, cars);
        moveRight(cars,i);
        
        if(isGoalState(cars[0])){
          printf("Reached goal state\n");
          printOutput(i+1, 'R', currNode);
          return true;
        }

        if(configExists(cars)); //printf("config exists\n");
        else{

          printf("Added a new node: Car %d, move right\n", i);
          newNode=makeNewNode(cars, currNode, i+1, 'R', type);

          insert(newNode);
        }
      }
    }
  }
  return false;
}

Node* makeRoot(Car carArray[]){
  int i;
  Node *rootNode = (Node*)malloc(sizeof(Node));
  rootNode->parent = NULL;
  rootNode->children = NULL;
  rootNode->level=0;
  rootNode->currHeuristic=0;//get heuristic here
  rootNode->currCost=0;
  rootNode->carArray = carArray;
  createCarArray(rootNode->carArray);

  /*for(i=0;i<numberOfCars;i++){
    printf("CAR ARRAY ID #%d (%d,%d)\n", rootNode->carArray[i].id,rootNode->carArray[i].coor.x,rootNode->carArray[i].coor.y);
  }*/

  // n_head = rootNode;
  // n_curr = n_head;
  return rootNode;
//   printf("mAKE ROOT PIECE OF SHIT");
}

void BFStree(Car carArray[]){
  /*int i;
  //BFS(pop());
  //printf("mainCar's coordinates (%d,%d)\n",head)

  Node *temp;
  temp = pop();
  BFS(temp);
  printf("MainCar (%d,%d)\n",temp->carArray[0].coor.x,temp->carArray[0].coor.y);
  // for(i=0;i<40;i++){
  //   temp = pop();
  //   BFS(temp);
  //   printf("(%d,%d) to (%d,%d) \n",temp->parent->carArray[0].coor.x,temp->parent->carArray[0].coor.y,carArray[0].coor.x,temp->carArray[0].coor.y); 
  // }
  while(isGoalState(temp->carArray[0])==false){
    temp = pop();
    BFS(temp);
    printf("MainCar (%d,%d)\n",temp->carArray[0].coor.x,temp->carArray[0].coor.y);
  }*/

  Node *node;
  bool goalReached;
  node = pop();
  while(node != NULL && goalReached == false){
    /*printf("Node explored @ level %d\n", node->level);
    printf("Heuristic: %d\n", node->currHeuristic);
    printf("Cost: %d\n", node->currCost);
    printf("Red car @ (%d, %d)\n", node->carArray[0].coor.x, node->carArray[0].coor.y);
    printf("\n");*/
    goalReached = BFS(node);
    //printf("\n\n\n");
    if(goalReached == false) node = pop();
  }
  if(goalReached == true){
    printf("Goal reached @ level %d\n", (node->level+1));
    return;
  }
  if(node == NULL) printf("No solution reached.\n");
  
}

void aStarTree(int type){
  Node *node;
  bool goalReached;
  node = pop();
  while(node != NULL && goalReached == false){
    /*printf("Node explored @ level %d\n", node->level);
    printf("Heuristic: %d\n", node->currHeuristic);
    printf("Cost: %d\n", node->currCost);
    printf("Red car @ (%d, %d)\n", node->carArray[0].coor.x, node->carArray[0].coor.y);
    printf("\n");*/
    goalReached = aStar(node,type);
    //printf("\n\n\n");
    if(goalReached == false) node = pop();
  }
  if(goalReached == true){
    printf("Goal reached @ level %d\n", (node->level+1));
    return;
  }
  if(node == NULL) printf("No solution reached.\n");
}
