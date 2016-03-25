#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 250

typedef struct node Node;

struct node{
	char data;
	int tag;
	int visit;
	Node *LSON;
	Node *RSON;
	Node *FTR;
};

Node *head;
Node *curr;
Node *temp;
Node *prev;

//FUNCTIONS
int valid1(char[], int);
int valid2(char[], int);
int printPost(Node *, FILE *,int);
int printChoice();
Node* getNode(char );
Node* Tree(char[], char[], int);
Node* Tree2(char[], char[], int);
void printLevel(Node *, int, FILE *);
void printTable(Node *, FILE *);
void *getInput(char *);

FILE *input, *output;

int main(){
	int i, j;  //for loops
	int choice; //option
	int height; //height of tree
	int size; //size of array
	int done = 0; //if user's done using the program, initialized as false
	int validation;

	output = fopen("2014.out","w"); //open output file

	while(done != 1){
		choice = printChoice();
		if(choice == 1){
			char data[MAX_SIZE];
			char tag[MAX_SIZE];

			//GET DATA
			printf("DATA: ");
			scanf("%[^\n]",data);
			getchar();

			//PRINT DATA ARRAY
			fprintf(output,"DATA: " );
			for(i=0;i<strlen(data);i++){
				fprintf(output,"%c", data[i]);
			}
			fprintf(output,"\n" );

			//GET TAGS
			printf("TAG: ");
			scanf("%[^\n]",tag);
			getchar();

			//PRINT TAG ARRAY
			fprintf(output,"TAG: " );
			for(i=0;i<strlen(tag);i++){
				fprintf(output,"%c", tag[i]);
			}
			fprintf(output,"\n" );

			if (strlen(data) != strlen(tag)){ //not equal input
				fprintf(output,"Input is invalid.\n\n");
			}

			else{
				getInput(data);
				getInput(tag);

				size = strlen(data);

				if(size==1 && tag[0] == '0'){ //tree with only one node
					fprintf(output,"Postorder: %c\n",data[0]);
					fprintf(output,"Levelorder: %c\n",data[0]);
					fprintf(output,"\nTable: \nLSON NODE RSON\n--------------\n");
					fprintf(output,"      %c\n\n",data[0]);
				}

				else if(size==1 && tag[0] == '1'){ //one node with children is invalid
					fprintf(output,"Input is invalid.\n\n");
				}

				else{
					if(tag[0] == '0'){
						fprintf(output,"Input is invalid.\n\n");
					}

					else{
						validation = valid1(tag,size);
						if(validation == -1){
							Node *root = Tree(data,tag,size);
							fprintf(output,"Postorder: ");
							height = printPost(root,output,0);
							fprintf(output,"\nLevel Order: ");
							for(i=0;i<height;i++){
									printLevel(root, i, output);
							}
							fprintf(output,"\nTable: \nLSON NODE RSON\n--------------\n");
							printTable(root,output);
							fprintf(output,"\n\n");
						}
						else{
							fprintf(output,"Input is invalid.\n\n");
						}
					}
				}
			}
		}

		else if(choice == 2){
			char filename[MAX_SIZE];
			char data_array[MAX_SIZE];
			char tag_array[MAX_SIZE];
			char data = ' ';
			int index = 0;

			printf("Filename: ");
			scanf("%s",filename);

			input = fopen(filename,"r");

			while(!feof(input)){
				index = 0;
				while(index < MAX_SIZE){
					data_array[index] = ' ';
					tag_array[index] = -1;
					index++;
				}
				index = 0;
				while(data!=':' && !feof(input)){
					data = fgetc(input);
				}
				fgetc(input);
				while(data!='\n' && !feof(input)){
					data = fgetc(input);
					if(data!=' '){
						data_array[index] = data;
						index++;
					}
				}
				int index = 0;
				while(data!=':' && !feof(input)){
					data = fgetc(input);
				}
				fgetc(input);
				data = fgetc(input);
				while(data!='\n' && !feof(input)){
					if(data!=' '){
						tag_array[index] = atoi(&data);
						index++;
					}
					data = fgetc(input);
				}

				fprintf(output,"DATA: " );
				int i;
				for(i=0;i<index;i++){
					if(i==index-1){
						fprintf(output,"%c", data_array[i]);
					}
					else{
					fprintf(output,"%c", data_array[i]);
					}
				}
				fprintf(output,"\n"); 

				fprintf(output,"TAG: " );
				for(i=0;i<index;i++){
					fprintf(output,"%d", tag_array[i]);
				}
				fprintf(output,"\n");

				int size = strlen(data_array);

				if(index==1 && tag_array[0] == 0){
					fprintf(output,"Postorder: %c\n",data_array[0]);
					fprintf(output,"Levelorder: %c\n",data_array[0]);
					fprintf(output,"\nTable: \nLSON NODE RSON\n--------------\n");
					fprintf(output,"      %c\n\n",data_array[0]);
				}
				else if(index==1 && tag_array[0] != 1){
					fprintf(output,"Input is invalid.\n\n");
				}
				else{
					//print(tag_array,size1);
					if(tag_array[0] == 0){
						fprintf(output,"Input is invalid.\n\n");
					}
					else{
						int validation = valid2(tag_array,index);
						if(validation == -1){
							Node *head_node = Tree2(data_array,tag_array,index);
							fprintf(output,"Postorder: ");
							height = printPost(head_node, output,0);
							fprintf(output,"\nLevelorder: ");
							int i = 0;
							for(i=0;i<height;i++){
								printLevel(head_node, i, output);
							}
							fprintf(output,"\nTable: \nLSON NODE RSON\n--------------\n");
							printTable(head_node,output);
							fprintf(output,"\n\n");
							}
						else{
							fprintf(output,"Input is invalid.\n\n");
						}
					}
				}
			}
			fclose(input);
		}

		else if(choice==3){
			printf("Exits.\n");
			done = 1;
		}

		else{
			printf("Wrong input.\n");
		}
	}
	fclose(output);
}

int valid1(char x[], int s){
	int sum = 0;
	int i;
	for(i=0;i<s;i++){
		if(x[i]=='1'){
			sum++;
			}
		else if(x[i]=='0'){
			sum--;
			if(sum<0 && i<s-1){
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	return sum;
}

int valid2(char x[], int s){
	int sum = 0;
	int i;
	for(i=0;i<s;i++){
		if(x[i]==1){
			sum++;
			}
		else if(x[i]==0){
			sum--;
			if(sum<0 && i<s-1){
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	return sum;
}

int printPost(Node *current, FILE *output, int height){
	height = height+1;
	int height_left = 0;
	int height_right = 0;
	int new_height = 0;
	if(current->LSON!=NULL){
		height_left = printPost(current->LSON,output,height);
		height_right = printPost(current->RSON,output,height);
		if(height_left > height_right) new_height = height_left;
		else new_height = height_right;
	}
	else new_height = height;
	fprintf(output,"%c", current->data);
	return (new_height);
}

int printChoice(){
	int num;
	printf("CHOOSE: \n1: INPUT FROM USER\n2: INPUT FROM EXTERNAL FILE\n3. EXIT\nEnter number: ");
	scanf("%d", &num);
	getchar();
	return num;
}


Node* getNode(char data){
	Node* alpha = (Node *) malloc(sizeof(Node));
	alpha->data= data;
	alpha->RSON = NULL;
	alpha->LSON = NULL;
	return (alpha);
}

Node* Tree(char data[], char tag[], int s){
	int size = s;
	int i = 0;
	for(i = 0; i < size; i++) {
		if(i == 0){
			head = getNode(data[i]);
			head->FTR=NULL;
			curr = head;
		}
		else{
			temp = getNode(data[i]);
			if(tag[i-1]=='1'){
				temp->FTR = curr;
				curr->LSON = temp;
				curr = temp;
			}
			else if(tag[i-1]=='0'){
				while(1){
					if(curr->FTR == NULL){
						break;
					}
					else if(curr->FTR->RSON!=NULL){
						prev = curr;
						curr = curr->FTR;
					}
					else{
						temp->FTR = curr->FTR;
						curr->FTR->RSON = temp;
						curr = curr->FTR->RSON;
						break;
					}
				}
			}
		}
	}
	return head;
}

Node* Tree2(char data[], char tag[], int s){
	int size = s;
	int i = 0;
	for(i = 0; i < size; i++) {
		if(i == 0){
			head = getNode(data[i]);
			head->FTR=NULL;
			curr = head;
		}
		else{
			temp = getNode(data[i]);
			if(tag[i-1]==1){
				temp->FTR = curr;
				curr->LSON = temp;
				curr = temp;
			}
			else if(tag[i-1]==0){
				while(1){
					if(curr->FTR == NULL){
						break;
					}
					else if(curr->FTR->RSON!=NULL){
						prev = curr;
						curr = curr->FTR;
					}
					else{
						temp->FTR = curr->FTR;
						curr->FTR->RSON = temp;
						curr = curr->FTR->RSON;
						break;
					}
				}
			}
		}
	}
	return head;
}

void printLevel(Node *current, int level, FILE *output){
	if(current == NULL) return;
	if(level == 0){
		fprintf(output,"%c",current->data);
	}
	else if(level>0){
		printLevel(current->LSON, level-1, output);
		printLevel(current->RSON, level-1, output);
	}
}

void printTable(Node *current, FILE *output){
	if(current->LSON!=NULL){
		fprintf(output,"%c     ", current->LSON->data);
	}
	else{
		fprintf(output,"      ");
	}
	fprintf(output,"%c     ", current->data);
	if(current->RSON!=NULL){
		fprintf(output,"%c\n", current->RSON->data);
	}
	else{
		fprintf(output," \n");
	}
	if(current->LSON!=NULL){
		printTable(current->LSON,output);
		printTable(current->RSON,output);
	}
}

void *getInput(char* str){
	int i;
	int j;
	for(i=0; i<strlen(str); i++){
		if(str[i] == ' '){
			for(j=i; j<strlen(str); j++){
				str[j] = str[j+1];
			}
		}else if(str[i] == '\n'){
			str[i] = '\0';
		}
	}
}