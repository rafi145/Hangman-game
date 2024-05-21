#include "header.h"

int main()
{
	char** difficult=NULL,op,*word,guess;
	int size,random,strikes=0,ishintallow=0;
	int* psize=&size,flag=0,iswin=0,*locations;
	printf("      Welcome to Hangman Game!\n\n");
	printf("Choose Difficulty (e-easy , m-medium):");
	op = _getche();
	while (!flag)
	{
		switch (op)
		{
		case 'm':
			difficult = import_medium(psize);
			flag = 1;
			break;
		case 'e':
			difficult = import_easy(psize);
			green();
			printf("\n\nYou have 1 hint, Press '*' to claim.\n");
			reset();
			ishintallow = 1;
			flag = 1;
			break;
		default:
			printf("\nError in key type try again...\n");
			printf("Choose Difficulty (e-easy , m-medium):");
			op = _getche();
			break;
		}
	}
	printf("\nYou have 3 strikes to guess the right animal!\n");
	printboard(strikes);
	srand(time(NULL));
	random = rand() % size;
	word = difficult[random];
	locations = (int*)calloc(strlen(word),sizeof(int));
	if (locations == NULL)
	{
		error_msg("Error in memory allocation", 0);
	}
	Startletters(locations, word);
	printprogress(word, locations);
	while (strikes != 3 && !iswin)
	{
		printf("Enter your guess: ");
		rewind(stdin);
		scanf("%c", &guess);
		if (ishintallow && guess == '*')
		{
			hint(locations, strlen(word));
			ishintallow = 0;
			printboard(strikes);
			printprogress(word, locations);
		}
		else if (guess == '*')
		{
			printf("\nYou ran out of hints/not allowed.\n");
		}
		else if (strchr(word, guess) != NULL|| strchr(word, guess-32) != NULL)
		{
			
			if (updatelocations(locations, word, guess))
			{
				green();
				printf("Well done!\n");
				reset();
				printboard(strikes);
				printprogress(word, locations);
			}
			else
			{
				strikes++;
				printboard(strikes);
				printprogress(word, locations);
				printf("Try Again you have ");
				red();
				printf("%d ", 3 - strikes);
				reset();
				printf("strikes left.\n");
			}
			
			
		}
		else
		{
			strikes++;
			printboard(strikes);
			printprogress(word, locations);
			printf("Try Again you have ");
			red();
			printf("%d ", 3 - strikes);
			reset();
			printf("strikes left.\n");
		}
		if (isFull(locations, strlen(word)))
			iswin = 1;
	}
	if (iswin)
	{
		green();
		printf("\nIt's a win, Good Job!!\n");
		reset();
	}
	else
	{
		red();
		printf("\nLoser :(\n");
		reset();
		printf("The word is %s.\n",word);
	}
	
	return 0;
}