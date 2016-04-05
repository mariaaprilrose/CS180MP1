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
      if(carArray[i].orientation == 'v'){ // vertical yung goal car
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
/*bool isGoalState(Car *mainCar, int goalX, int goalY){
  if((mainCar->orientation == 'h') && ((mainCar->coor.y + mainCar->length - 1) >= goalY)){//from v to h
    if((mainCar->coor.y + mainCar->length - 1) > goalY) printf("Car exceeded goal point.");
    return true;
  }
  if((mainCar->orientation == 'v') && ((mainCar->coor.x + mainCar->length - 1) >= goalX)){//from h to v
    if((mainCar->coor.x + mainCar->length - 1) > goalX){
      printf("Car exceeded goal point.");
    }
    return true;
  }
  else return false;
}*/

bool isGoalState(Car mainCar, int goalX, int goalY){
  if((mainCar.orientation == 'v') && ((mainCar.coor.y + mainCar.length - 1) >= goalY)){
    if((mainCar.coor.y + mainCar.length - 1) > goalY) printf("Car exceeded goal point.");
    return true;
  }
  if((mainCar.orientation == 'h') && ((mainCar.coor.x + mainCar.length - 1) >= goalX)){
    if((mainCar.coor.x + mainCar.length - 1) > goalX){
      printf("Car exceeded goal point.");
    }
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
    printf("Number of cars: %d\n",numberOfCars);
  free(line);

  if (feof(fp))
     printf("\n End of file reached.");
  else
     printf("\n Something went wrong.");

}

void createCarArray(Car* carList){
  int i;
  curr1 = head; 
  for(i=0;i<numberOfCars;i+=1){
    carList[i] = *curr1;
    printf("Create Car Array fxn %d\n",carList[i].id);
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
      y=copy_y;
      y=y+i;
    }
    else if(coor1==118){
      x=copy_x;
      x=x+i;
    }
    for(j=0; j<size2; j++){
      if (coor2 == 104){
        y2=copy_y2;
        y2=y2+j;
        
      }
      else if(coor2==118){
        x2=copy_x2;
        x2=x2+j;
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
    check = 2;
    return false;
  }
  
  if (orientation==118){
    endx= startx + (size-1);
    if(endx >= matrixSize || endx < 0){
      check = 2;
      return false;
    }
  }      
  else if (orientation==104){
    endy= starty + (size-1);
    if(endy>= matrixSize || endy < 0){
      check = 2;
      return false;
    }
  }    

  printf("Car %d\n", car+1 );
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
  int copy = carArray[car].coor.x;
  copy--;
  // if(carArray[car].orientation==104)
  //   return 0;

  if(CarCheck(copy, carArray[car].coor.y, carArray, car) == true){
    printf("1 Move UP\n");
    return 1;
  }
  else{
    return 0;
  }
}

int CarDown(Car carArray[], int car){
  int copy = carArray[car].coor.x;
  copy++;
  if(carArray[car].orientation==104)
    return 0;

  if(CarCheck(copy, carArray[car].coor.y, carArray, car) == true){
    printf("1 Move DOWN\n");
    return 1;
  }
  else{
    return 0;
  }
}

int CarLeft(Car carArray[], int car){
  int copy = carArray[car].coor.y;
  copy--;

  if(carArray[car].orientation==118)
    return 0;

  if(CarCheck(carArray[car].coor.x, copy, carArray, car) == true){
    printf("1 Move LEFT\n");
    return 1;
  }
  else{
    return 0;
  }
}

int CarRight(Car carArray[], int car){
  int copy = carArray[car].coor.y;
  copy++;

  if(carArray[car].orientation==118)
    return 0;
  
  if(CarCheck(carArray[car].coor.x, copy, carArray, car) == true){
    printf("1 Move RIGHT\n");
    return 1;
  }
  else{
    return 0;
  }
}



void CopyCar(Car array1[], Car array2[]){
  int i;
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
      Q_head = (Queue*)malloc(sizeof(Queue));
      Q_orighead = Q_head;
      Q_head->ptr = pointer;
      Q_head->next= NULL;
      //Q_head->laman=data;
      Q_curr = Q_head;
  }
  else{
    printf("I CAN PUSH\n");
      Q_curr->next = (Queue*)malloc(sizeof(Queue));
      Q_curr = Q_curr->next;
      Q_curr->ptr = pointer;
      Q_curr->next= NULL; 
      //Q_curr->laman=data;    
  }

}

Node* pop(){//EDIT: this is copy pasted from internet
  Queue *pointer;
  
  pointer = Q_head;
  Q_head = Q_head->next;
  if(Q_head==NULL){
    // printf("WALANG LAMAN BITCH\n");
    Q_curr = NULL;
  }
  else{
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


Node* makeNewNode(Car carArray[], Node *parent){
  Node *node = (Node*)malloc(sizeof(Node));
  node->parent = parent;
  node->children = NULL;
  
  node->level = parent->level + 1;
  node->currHeuristic = 0;//get heuristic here
  node->currCost = 0;
  node->carArray = carArray;
  
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
    printf("Inserting into empty list\n");
    Q_head = (Queue*)malloc(sizeof(Queue));
    Q_orighead = Q_head;
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
  carArray[index].coor.x--;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveDown(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.x++;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveLeft(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.y--;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void moveRight(Car carArray[], int index){//struct
  //printf("BE4 id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  carArray[index].coor.y++;
  //printf("AFTER id: %d, coordinate: %d\n", carArray[index].id, carArray[index].coor.x);
  
}

void BFS(Node *currNode){// make queue
  int i,j;
  Node *newNode;


  if(currNode!=NULL){
    for(i=0;i<numberOfCars;i++){//check allprintf allowed moves per car (U/D,L/R)
      printf("+++++++++++++++++++++Checking allowed moves for Car %d+++++++++++++++++++++\n",currNode->carArray[i].id);
      if(currNode->carArray[i].orientation==118){
        if(CarUp(currNode->carArray,i)==1){//if UP move valid
          carArray = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, carArray);
          moveUp(carArray,i);
          if(configExists(currNode->carArray)) break;
          newNode=makeNewNode(carArray, currNode);
          push(newNode);
        }
        if(CarDown(currNode->carArray,i)==1){//if DOWN move valid
          carArray = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, carArray);
          moveDown(carArray,i);
          if(configExists(currNode->carArray)) break;
          newNode=makeNewNode(carArray, currNode);
          push(newNode);
        }
      }
      else if(currNode->carArray[i].orientation==104){
        if(CarLeft(currNode->carArray,i)==1){//if UP move valid
          carArray = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, carArray);
          moveLeft(carArray,i);
          if(configExists(carArray)==false){
            newNode=makeNewNode(carArray, currNode);
            push(newNode);
          }
        }

        if(CarRight(currNode->carArray,i)==1){//if UP move valid
          carArray = malloc(numberOfCars*sizeof(Car));//make carArray holder/temp
          CopyCar(currNode->carArray, carArray);
          moveRight(carArray,i);
          if(configExists(carArray)==false){
            newNode=makeNewNode(carArray, currNode);
            push(newNode);
          }
        }
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

  for(i=0;i<numberOfCars;i++){
    printf("CAR ARRAY ID #%d (%d,%d)\n", rootNode->carArray[i].id,rootNode->carArray[i].coor.x,rootNode->carArray[i].coor.y);
  }

  // n_head = rootNode;
  // n_curr = n_head;
  push(rootNode);
//   printf("mAKE ROOT PIECE OF SHIT");
}

void BFStree(Car carArray[]){
  int i;
  //BFS(pop());
  //printf("mainCar's coordinates (%d,%d)\n",head)

  Node *temp;
  temp = pop();
  BFS(temp);
  printf("MainCar (%d,%d)\n",temp->carArray[0].coor.x,temp->carArray[0].coor.y);
  for(i=0;i<40;i++){
    temp = pop();
    BFS(temp);
    printf("(%d,%d) to (%d,%d) \n",temp->parent->carArray[0].coor.x,temp->parent->carArray[0].coor.y,carArray[0].coor.x,temp->carArray[0].coor.y); 
  }
  
}

