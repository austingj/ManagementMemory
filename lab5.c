/**
README
Name: Austin Jeffery
How to Compile: Copy this lab5.c file into a directory along with a text file saved as input.txt
Then open the terminal where these two files are located in and run the command
"gcc -g lab5.c -o run" after it has compiled you should be able to run it by 
using the command ./run
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
char processes[100];
char useOrFree[100];
int memlength[100];
int totalmem[10] = {0,0,0,0,0,0,0,0,0,0}; //this is used to represent the size 0s represent holes
char procmem[10] = {'0','0','0','0','0','0','0','0','0','0'}; //0s represent holes 
int max;
int holesize = 0;
int maxstart = 0;
int maxfin = 0;
int getlengthmem(void);
#include <stdio.h>
#include <stdlib.h>

//read file store processes char in processes array
//store U or F char in useOrFree array
//store size in memlength array
void readfile(){
	FILE *inputfile = fopen("input.txt", "r");
	int number;
	int nop;
	int i =0;
	char proc[100];
	char use[100];
	if( !inputfile){
	printf("File cannot be read\n");
	exit(-1);
	}
	printf("~~~~~~~INPUT FILE TEXT ~~~~~~~~~\n");
	char buf[100];
	while(fscanf(inputfile,"%1[^ ,] , %1[^ ,] ,%d\n", proc,use, &number)==3){
		printf("%s", proc);
		printf(", ");
		printf("%s", use);
			printf(", ");
		printf("%d", number);
		printf(" ");
		printf("\n");	
		processes[i] = *proc;
		useOrFree[i] = *use;
		memlength[i] = number;
		i++;
	}max = i;
	printf("~~~~~~~END OF INPUT TXT~~~~~~~~~\n");
}
void print(){
	printf("\nPRINT FUNC\n");
	for(int i =0;i<max;i++){
		printf("%c",processes[i]);
		printf("%c",useOrFree[i]);
		printf("%d",memlength[i]);
		printf("\n");
	}
}
void output(){
	printf("\n");
	for(int i = 0; i < 10; i++){
	printf("[ %c ]", procmem[i]);
	}
	printf("\n");
	for(int i = 0; i < 10; i++){
	printf("[ %d ]", totalmem[i]);
	}
printf("\n");
}

//gethole will find the biggest hole in the totalmem array, it will also set the start
//and finish values. Total mem array will either be 0s or 1s (0s = holes, 1s = spot is being used
void gethole(){
	int length = 0;
	int finish[10];
	int start[10];
	int hole[10] = {0,0,0,0,0,0,0,0,0,0};
	int currentmax = 0;
	int j =0;
	int cmaxhole = 0;
	//printf("MAX : %d", max);
	for(int i = 0; i< 10 ; i++){
		if(totalmem[i] == 0){
		start[j] = i;
		hole[j]++;
		cmaxhole = hole[j];
		//printf("\n maxhole %d " , cmaxhole);
		}
		else{	
		for(int k = 0; k < 10; k++){
		if(cmaxhole < hole[k]){
			cmaxhole = hole[k];
			//printf("cmaxhole < hole[k");
			start[j] = start[j] - cmaxhole;
			finish[j] = start[j] + cmaxhole;
			}
		}
		j++;
		}
		if(currentmax < cmaxhole){
			currentmax = cmaxhole;
			start[j] = start[j] - cmaxhole;
			maxstart = start[j] +1 ;
			maxfin = start[j] + cmaxhole + 1;
			holesize = currentmax;
			}
	}
/*	printf("\n maxstart: %d",maxstart);	to show values as it goes through
	printf("\n");
	printf(" maxfin: %d",maxfin);
	printf("\n");
*/
}
//allocatemem will go through the input file, max = number of lines
//it calls gethole() method to calculate biggest hole
void allocatemem(){
	int j = 0;
	int s = 0;
	int f = 0;
	int i = 0;
	int m = 0;
	int count = 0;
	int length = 0;
	while(max!=i){
		if(useOrFree[i] == 'U'){	
			gethole();
			printf("Holesize: %d", holesize);
			if(memlength[i] > holesize){
			printf("Cannot allocate memory, hole too small");
			}
			else{	//allocate mem, change totalmem 000 to 111 etc
				length = memlength[i];
				printf(" allocating %c : %d", processes[j], length);
				for(int i = maxstart ; i<length+maxstart; i++){
					procmem[i] = processes[j];
					totalmem[i] = 1;
				}
			}
		}
		if(useOrFree[i] == 'F'){
			length = memlength[i];
			printf("Removing Process: %c  length: %d ",processes[j], length);
			for(int i =0;i<10;i++){
					//printf("if procmen I [ %c ]", procmem[i]);
					//printf(" == processes J [ %c ]", processes[j]);
					//printf("\n");
				if(procmem[i] == processes[j]){
					s = i;	
					count++;		
				}
			}
			//printf("count = %d", count);
			s  = s-count + 1;
			f = s + length;
			for(int i = s; i < f; i ++){
					totalmem[i] = 0;
					procmem[i] = '0';
					m++;
			}
		}
		count = 0;
		j++;
		i++;
		output();
	}
}

int main()
{
	//step 1 read file and store input
	//step 2 implement algorithm
	readfile();
	print();
	printf("\n");
	allocatemem();
	
printf("\nEND\n");
	return 0;
}
