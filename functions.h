/*All Structures, Global Variables, Function Decalarations*/

typedef struct{
  int x;
  int y;
} Coordinates;

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
  //char **state;
  //GridState *state;
  Node *parent;
  Node **children;
  int level;
  int currHeuristic;
  int currCost;
  Car *carArray;
  //access array of coordinates
};

typedef struct queue Queue;
struct queue{
  Queue *next;
  int laman;
  Node *ptr;
};

Node *node_head;

/*Global Vasiables*/
int matrixSize;
char arrayField[10][10];
int copy_idtemp;
int numberOfCars;
int goalX;
int goalY;
Car *TempCar;
Car *head;
Car *curr1;
Car *curr2;
Car *cars;
Node *tempNode;

Node *n_head;
Node *n_curr;
Node *tempNode;

Queue *Q_head;
Queue *Q_curr;
Queue *Q_orighead; // For config tracking

/*Functions*/
void setGoalCoor(Car mainCar);
int blockHeuristic(Car carArray []);
int advanceHeuristic(Car carArray[]);
bool isGoalState(Car mainCar);
void initGrid();
void printGrid();
void insertToGrid(Car *car);
void MakeCar(char *carData, int num);
void getFile(FILE *fp);
void createCarArray(Car* carList);
int CoorComp(int x, int y, int coor1, int size1, int x2, int y2, int coor2, int size2);
bool CarCheck(int startx, int starty, Car carArray[], int car);
int CarUp(Car carArray[], int car);
int CarDown(Car carArray[], int car);
int CarLeft(Car carArray[], int car);
int CarRight(Car carArray[], int car);
void CopyCar(Car array1[], Car array2[]);
bool aStar(Node *node);
Node* initState(Node* state,int lvl, int heur, int cost, int id, int x, int y);
void push(Node *pointer);//, int data);
Node* pop();
void printQ();
Node* makeNewNode(Car carArray[], Node *parent, int type);
bool configExists(Car carArray[]);
void insert(Node *node);
void BFS();
void makeRoot(Car carArray[]);
void BFStree(Car carArray[]);