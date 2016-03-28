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
Node *node_head;

// typedef struct node Node;
// struct node{
//   int currentHeuristic;
//   int currentCost;
//   Car *cars;
//   Node **children;
// };

/*Global Vasiables*/
int matrixSize;
char arrayField[10][10];
int copy_idtemp;
int numberOfCars;
Car *TempCar;
Car *head;
Car *curr1;
Car *curr2;
Node *tempNode;

/*Functions*/
void initGrid();
void printGrid();
void insertToGrid(Car *car);
void MakeCar(char *carData, int num);
void getFile(FILE *fp);
void createCarArray(Car* carList);
int CoorComp(int x, int y, int coor1, int size1, int x2, int y2, int coor2, int size2);
bool CarCheck(int startx, int starty, int orientation, int size);
int CarUp(Car *car);
int CarDown(Car *car);
int CarLeft(Car *car);
int CarRight(Car *car);
int CopyArray(char array1[], char array2[]);
void aStar();
void BFS();