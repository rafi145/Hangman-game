#ifndef _head
#define _head

//includes and structs
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


//Function declares
void green();
void red();
void reset();
char** import_easy(int*);
char** import_medium(int*);
int isFull(int*, int);
void printboard(int);
void printprogress(char*,int*);
void error_msg(char* text,int amount);
int updatelocations(int*,char*,char);
void Startletters(int*, char*);
void hint(int*,int);

#endif 

