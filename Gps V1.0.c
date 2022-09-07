/******************************************************/
/******************************************************/
/***********Author: Braa Adel,Ali Abu Sami*************/
/*****************File: DIO_private.h******************/
/******************Date: 18th Aug 2022*****************/
/*********************Version: V1**********************/
/*******Desc:Searching process throw paths to get a spe-
cific destination by getting known of every possible av-
ailable or blocked path********************************/
/******************************************************/
/******************************************************/


#include <stdio.h>
#include "STD_TYPES.h"
#include "stdlib.h"
#define up 0
#define right 1
#define down 2
#define left 3
#define zero 5
#define firstX 2
#define firstY 0
#define LastX 1
#define LastY 1

//STRUCTS
typedef struct bit {u8 o:2;}bit;
typedef struct{
	u8 x,y;             //Dimentions
	struct {
		u8 z:2;          //Arrows 0,1,2,4
	}no_back;
	struct node * nxt;
	struct node * prev;
	struct node * anotherStack;  //next For Another Ways
	u8 path;
}node;

bit i,j;
#define i i.o
#define j j.o

//VARIABLES
u8 opp,  //Opposite dir
moving,  //move steps
anotherway,  //Number of other pathes
anoswitchTURN; //there is another path
u8 count_second=1;    //second path steps
u8 count_First=1;   //first path steps

 u8 arr[4][4]={{1, 1,   zero, 1},     //The map
			 {1, zero, zero,zero},
			 {1,  1,     1, zero},
			 {1,  1,     1, zero}};
			 
//NODES			 
node * head = NULL;
node * tail = NULL;	
node * pointer = NULL; //head of another path stack


//FUNCTIONS
void push(u8,u8,u8);  //adding to stack
void print_stack();   //Print first stack content
void print_stack_ano();  //Print second stack content
void move();             //search for away on
u8 No_Back(u8);          //Not going Back 


void main()
{
	i=firstY; j=firstX;	
	do{move();}while(moving!=0 && moving<10);
	if(i==LastY && j==LastX)
	{if(moving>9)print_stack();else printf("Infinity Loop");}
	
	i=pointer->y;
	j=pointer->x;
	opp=pointer->path;
	pointer->path=No_Back(opp);

	if(anoswitchTURN==1)moving=1;
	
	do{move();}while(moving!=0 && moving<10);
	if(moving>9)print_stack_ano();else printf("Infinity Loop");	
}

void move()
{
moving++;
anotherway=0;
if(1){
	if(arr[i][j+1]==zero && right !=opp){ //Right
		anotherway++;
		push(right,j,i);
		j++;
		opp=No_Back(right);
	}
	if(arr[i][j-1]==zero && left !=opp){ //Left
		anotherway++;
		push(left,j,i);
		j--;
		opp=No_Back(left);
	}
	if(arr[i+1][j]==zero && down !=opp){ //Down
		anotherway++;
		push(down,j,i);
		i++;
		opp=No_Back(down);
	}
	if(arr[i-1][j]==zero  && up !=opp ){ //Up
		anotherway++;
		push(up,j,i);
		i--;
		opp=No_Back(up);
	}
}else{
		moving= 0;
}}


void push(u8 val,u8 x1, u8 y1){
	if(head == NULL)              //Start stack
	{
		head = (node*)malloc(sizeof(node));
		head-> path = val;
		head-> nxt = NULL;
		head-> x = x1;
		head-> y = y1;
		head-> prev = NULL;//added
		tail = head;
	}
	else{                           //Add to Stack
		node * temp =(node*)malloc(sizeof(node));
		temp->path = val;
		temp-> x = x1;
		temp-> y = y1;
		
		if(anoswitchTURN!=1){
		temp->nxt = NULL;
		temp-> prev =(node*) tail;//added
		tail->nxt = temp;
		tail = temp;
		}
		else{
			temp->anotherStack = NULL;
			temp-> prev =(node*) tail;//added
			tail->anotherStack = temp;
			tail = temp;
		}}
	
	if(anotherway==2){        //Get a head for the Another Path
		pointer =(node*)malloc(sizeof(node));
		pointer=tail->prev;
		anotherway++;
	}
	No_Back(val);
}


void print_stack(){
	node* ptr =head;
	while(ptr->nxt != NULL){  //Print The First Path
		printf("%d  (%d,%d)\n",ptr->path,ptr->x,ptr->y);
		ptr=(node*)ptr->nxt;count_First++;
	}
	printf("%d  (%d,%d)\n",ptr->path,ptr->x,ptr->y);
	printf("Counter.= %d\n",count_First);
	
}
void print_stack_ano(){     //Print The another Path
	node* ptr =pointer;
	printf("%d  (%d,%d)\n",head->path,head->x,head->y);
	while(ptr->anotherStack != NULL){
		printf("%d  (%d,%d)\n",ptr->path,ptr->x,ptr->y);
		ptr=(node*)ptr->anotherStack;count_second++;
		printf("Counter..= %d\n",count_second);
	}
	printf("Counter..= %d\n",count_second);
}


u8 No_Back(u8 value){   //Getting the opposite Dir
	node * temp =(node*)malloc(sizeof(node));
	temp->no_back.z=value;
	temp->no_back.z+=2;
	return temp->no_back.z;
	
}








