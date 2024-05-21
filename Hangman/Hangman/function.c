#include "header.h"

//Color changes
void green(){
  printf("\033[0;32m");
}
void red(){
  printf("\033[0;31m");
}
void reset() {
	printf("\033[0m");
}

//import from file easy list
char** import_easy(int* size) {
	FILE* in = fopen("animal_easy.txt", "rt");
	int i = 0;
	char** list_easy;
	if (in == NULL)
	{
		printf("ERROR open animal_easy.txt file.");
		exit(1);
	}
	list_easy = (char**)malloc(sizeof(char*));
	if (list_easy == NULL)
		error_msg(list_easy, "Error in allocation memory!", i);
	list_easy[i] = (char*)malloc(15 * sizeof(char));
	if (list_easy[i] == NULL)
		error_msg(list_easy, "Error in allocation memory!", i);
	while (fscanf(in, "%s", list_easy[i]) != EOF)
	{
		i++;
		list_easy = (char**)realloc(list_easy, (i + 1) * sizeof(char*));
		if (list_easy == NULL)
			error_msg(list_easy, "Error in allocation memory!", i - 1);
		list_easy[i] = (char*)malloc(15 * sizeof(char));
		if (list_easy[i] == NULL)
			error_msg(list_easy, "Error in allocation memory!", i);
	}
	fclose(in);
	*size = i;
	return list_easy;
}

//import from file medium list
char** import_medium(int* size) {
	FILE* in = fopen("animal_medium.txt", "rt");
	int i = 0;
	char** list_medium;
	if (in == NULL)
	{
		printf("ERROR open animal_easy.txt file.");
		exit(1);
	}
	list_medium = (char**)malloc(sizeof(char*));
	if (list_medium == NULL)
		error_msg(list_medium, "Error in allocation memory!", i);
	list_medium[i] = (char*)malloc(15 * sizeof(char));
	if (list_medium[i] == NULL)
		error_msg(list_medium, "Error in allocation memory!", i);
	while (fscanf(in, "%s", list_medium[i]) != EOF)
	{
		i++;
		list_medium = (char**)realloc(list_medium, (i + 1) * sizeof(char*));
		if (list_medium == NULL)
			error_msg(list_medium, "Error in allocation memory!", i - 1);
		list_medium[i] = (char*)malloc(15 * sizeof(char));
		if (list_medium[i] == NULL)
			error_msg(list_medium, "Error in allocation memory!", i);
	}
	fclose(in);
	*size = i;
	return list_medium;
}

//print the grapic hangman
void printboard(int c)
{
	char h = 'O', b[4] = "/|\\", d[4]="/ \\";
	if (c == 2)
		strcpy(d,"   ");
	else if (c == 1)
	{
		strcpy(d, "   ");
		strcpy(b, "   ");
	}
	else if (c < 1)
	{
		h = ' ';
		strcpy(d, "   ");
		strcpy(b, "   ");

	}
	printf("\n____________________________\n");
	printf("|                          |\n");
	printf("|      *********           |\n");
	printf("|      *       *           |\n");
	printf("|      *       %c           |\n",h);
	printf("|      *      %s          |\n",b);
	printf("|      *      %s          |\n",d);
	printf("|      *                   |\n");
	printf("|      *                   |\n");
	printf("|**************************|\n");
}

//print the progres
void printprogress(char* g,int* l)
{
	printf("\nThe progress->");
	for (int i = 0; i < strlen(g); i++)
	{
		if (l[i] ==1)
			printf(" %c",g[i]);
		else 
			printf(" _");
	}
	printf("\n");
}

//Upate the location for right answer
int updatelocations(int* l, char* word, char g)
{
	int i,flag=0;
	for (i = 0; i < strlen(word); i++)
	{
		if (word[i] == g || word[i] == (g - 32))
			if (l[i] != 1)
			{
				l[i] = 1;
				flag = 1;
			}
	}
	return flag;
}

void Startletters(int* l, char* word)
{
	int size = 2,random;
	if (strlen(word) <= 3)
		size = 1;
	else if (strlen(word) > 5)
		size = 3;
	for (int i = 0; i < size; i++)
	{
		srand(i);
		random = rand() % strlen(word);
		l[random] = 1;
	}
}

int isFull(int* l,int size)
{
	for (int i = 0; i < size; i++)
	{
		if (l[i] == 0)
			return 0;
	}
	return 1;
}

void hint(int* l,int s)
{
	int random,isgive=0;
	while (!isgive)
	{
		srand(time(NULL));
		random = rand() % s;
		if (l[random] != 1)
		{
			l[random] = 1;
			isgive = 1;
		}
	}
}

//error msg and exit code 1
void error_msg(char** array,char* text,int amount)
{
	if (amount != 0)
	{
		for (int i = 0; i < amount; i++)
		{
			free(array[i]);
		}
		free(array);
	}
	printf("%s", text);
	exit(1);
}