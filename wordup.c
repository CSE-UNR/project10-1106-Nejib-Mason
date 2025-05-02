	//programmed by: Mason Nejib
	//Date: 05/0/2025
	//The purpose of this code is to collect a 5 letter word from mystery.txt then let the user guess 5 letter words to see if they can get the word with hints with only 6 guesses
	
	#include <stdio.h>
	
	//defines the max guess the user can have as well as the max amount of words allowed for the guess
	#define MAXGUESS 6
	#define CAP 5
	
	//prototypes for functions
	int checkLowAlph(char letter,char lowAlph[]);
	int checkAlph(char letter,char lowAlph[],char upAlph[]);
	int getLength(char string[]);
	void getGuess(char guessWord[], char lowAlph[], char upAlph[]);
	int checkMatch(char letter, int index1, char mletter, int index2, char lowAlph[], char upAlph[]);
	int updateGuesses(char guessWord[], char word[], char guessSaved[][CAP], char lowAlph[], char upAlph[], int num);
	
	int main()
	{
		//initializing variables and arrays, in particular num is used to jump spaces in the guessSaved array and the alphabet is used for comparasion and cap shinanigans
		int guesses = 1;
		int num = 1;
		char guessWord[CAP];
		char upAlph[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T' , 'U', 'V', 'W', 'X', 'Y', 'Z'};
		char lowAlph[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't' , 'u', 'v', 'w', 'x', 'y', 'z'};
		FILE* secretWord = fopen("mystery.txt", "r");
		char guessSaved[MAXGUESS*2][CAP];
		int win = 0;
		
		//tests if the file open correctly
		if(secretWord == NULL)
		{
			printf("Did not access file, goodbye\n");
			return 0;
		}
		
		//collects word from the text file
		char word[CAP];
		fscanf(secretWord, "%s", word);
		
		
		//while look for the amount of times the user can guess
		while(guesses <= 6)
		{
			if(guesses != 6)
			{
				printf("GUESS %d! Enter your guess: ", guesses);
			}
			else
			{
				printf("FINAL GUESS : ", guesses);
			}
			getGuess(guessWord, lowAlph, upAlph);
			printf("================================\n");
			//both updates the guess array and checks if the user won or not
			win = updateGuesses(guessWord, word, guessSaved, lowAlph, upAlph, num);
			if(win)
			{
				//converts the guess to all CAPS if the user got it correct
				for(int i = 0; i < CAP; i++)
				{
					guessWord[i] = upAlph[checkAlph(guessWord[i], lowAlph, upAlph)];	
				}
				printf("\t\t%s\n", guessWord);
				printf("\tYou won in %d guesses!\n", guesses);
				//prints diffrent word depending on how fast they guessed the word
				switch(guesses)
				{
					case 1:
						printf("\t\tGOATED!\n");
						break;
					case 2:
						printf("\t\tAmazing!\n");
						break;
					case 3:
						printf("\t\tAmazing!\n");
						break;
					case 4:
						printf("\t\tNice!\n");
						break;
					case 5:
						printf("\t\tNice!\n");
						break;
					case 6:
						break;
				}
				break;
			}
			//there is probably a more efficient way to do it them printing each letter but for whatever reason the code kept adding to the previous points though it wasn't told to
			for(int i = 0; i <= num; i++)
			{
				printf("%c", guessSaved[i][0]);
				printf("%c", guessSaved[i][1]);
				printf("%c", guessSaved[i][2]);
				printf("%c", guessSaved[i][3]);
				printf("%c", guessSaved[i][4]);
				printf("\n");
			}
			guesses++;
			num+=2;
		}
		printf("You lost, better luck next time!\n");
		fclose(secretWord);
	}
	
	//checks if the letter provided was a lower case letter, if it was it returns where in the array the letter is located
	int checkLowAlph(char letter,char lowAlph[])
	{
		for(int i = 0; i < 26 ; i++)
		{
			if(lowAlph[i] == letter)
			{
				return i;
			}
		}
		return -1;
	}
	
	//checks the letter if it is in the alphabet as a capital letter or lowercase, if it is it returns the index of the letter in the alphabet, if not it returns -1
	int checkAlph(char letter,char lowAlph[],char upAlph[])
	{
		if(checkLowAlph(letter, lowAlph) == -1)
		{
			for(int i = 0; i < 26 ; i++)
			{
				if(upAlph[i] == letter)
				{
					return i;
				}
			}
			return -1;
		}
		else
		{
			return checkLowAlph(letter, lowAlph);
		}
	}
	
	//gets length of a string
	int getLength(char string[])
	{
		int length = 0;
		for(int i = 0; string[i] != '\0'; i++)
		{
			length++;
		}
		return length;
	}
	
	//collects the guess of the uesr and determains if the guess was valid based on length and if it containts only letters
	void getGuess(char guessWord[], char lowAlph[], char upAlph[])
	{
		int length;
		int valid = 1;
		
		scanf("%s", guessWord);
		length = getLength(guessWord);
		for(int i = 0; guessWord[i] != '\0'; i++)
		{
			if(checkAlph(guessWord[i], lowAlph, upAlph) == -1)
			{
				valid = 0;
			}
		} 
		
		while(length != CAP || !valid)
		{
			if(length != CAP)
			{
				printf("Your guess must be %d letters long.", CAP);
			}
			if(!valid)
			{
				printf("Your guess must only contain letters.");
			}
			printf("\n");
			length = 0;
			valid = 1;
			scanf("%s", guessWord);
			length = getLength(guessWord);
			for(int i = 0; guessWord[i] != '\0'; i++)
			{
				if(checkAlph(guessWord[i], lowAlph, upAlph) == -1)
				{
					valid = 0;
				}
			}
			
		}
	}
	
	//if perfect match return 1, if match in word but wrong placement return 2, if not in word return 0
	int checkMatch(char letter, int index1, char mletter, int index2, char lowAlph[], char upAlph[])
	{
		if(checkAlph(letter, lowAlph, upAlph) == checkAlph(mletter, lowAlph, upAlph))
		{
			if(index1 == index2)
			{
				return 1;
			}
			return 2;
		}
		return 0;
	}
	
	//checks each letter in the guess to see if it is in the actual word, if it is but isn't in the right spot it puts a carrot underneath and if it is it makes it capital, also makes all letters lowercase if not correct spot and letter
	int updateGuesses(char guessWord[], char word[], char guessSaved[][CAP], char lowAlph[], char upAlph[], int num)
	{
		char used[CAP];
		int escape = 0;
		int check;
		int hits = 0;
		
		for(int i = 0; i < CAP; i++)
		{
			
			for(int j = 0; j < CAP; j++)
			{
				check = checkMatch(guessWord[i], i, word[j], j, lowAlph, upAlph);
				escape = 0;
				for(int k = 0; k < CAP; k++)
					if(guessWord[i] == used[k])
					{
						escape = 1;
						break;
					}
				if(escape)
				{
					guessSaved[num-1][i] = lowAlph[checkAlph(guessWord[i], lowAlph, upAlph)];
					guessSaved[num][i] = ' ';
					break;
				}
				if(check == 1)
				{
					guessSaved[num-1][i] = upAlph[checkAlph(guessWord[i], lowAlph, upAlph)];
					used[i] = guessWord[i];
					guessSaved[num][j] = ' ';
					hits++;
					break;
				}
				else if(check == 2)
				{
					guessSaved[num-1][i] = lowAlph[checkAlph(guessWord[i], lowAlph, upAlph)];
					guessSaved[num][i] = '^';
					used[i] = guessWord[i];
					break;
				}
				else
				{
					guessSaved[num-1][i] = lowAlph[checkAlph(guessWord[i], lowAlph, upAlph)];
					guessSaved[num][i] = ' ';
				}
			}
		}
		if(hits == CAP)
		{
			return 1;
		}
		return 0;
	}
	
	
	
	
