
typedef struct{
  int x;
  int y;
} Coordinates;

typedef struct gridstate GridState;
struct gridstate{
  //char **state;
  //GridState *state;
  GridState *parent;
  GridState **children;
  int height;
  int currentHeuristic;
  int currentCost;
};
//GridState *head;

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
bool CarCheck(int startx, int starty, int orientation, int size);
int CarUp(Car *car);
int CarDown(Car *car);
int CarLeft(Car *car);
int CarRight(Car *car);
void aStar();
