/* ENGGEN131 C Project 2022 - Boulder Break */
#define _CRT_SECURE_NO_WARNINGS
#define CAVE_SIZE 13
#include <stdio.h>
#include <string.h>

void InitialiseStory(char* paragraph)
{
	char story[2000] = "Once upon a time, two races ruled over Earth: Humans and\n\
The Gorons. One day, war broke out between the two races.\n\
After a long battle, the humans were victorious.They\n\
sealed the Gorons underground with a magic spell.\n\
\n\
The fear of Gorons was based mainly on the fear\n\
that the Gorons would eventually turn on humans\n\
and start a revolution...\n\
\n\
Trapped underground, the monsters explored their new\n\
environment and slowly set up a society there.\n\
\n\
One day, a child named Steve fell into one of the spell's\n\
cracks, ending up in the land of the Gorons.\n\
\n\
In order to reach the surface, Steve must battle the\n\
resenting Gorons, pushing them in holes in order to...\n\
\n\
                  BOOM...Escape!\n";

	strcat(paragraph, story);


}
void PrintCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int i, j;
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 1) {
				printf("%c", '#');
			}
			else if (cave[i][j] == 0) {
				printf(" ");
			}
			else if (cave[i][j] == 69) {
				printf(" ");
			}
			else if (cave[i][j] == 88) {
				printf("X");
			}
			else if (cave[i][j] == 42) {
				printf("*");
			}
			else if (cave[i][j] == 43) {
				printf("+");
			}
			else if (cave[i][j] == 79) {
				printf("O");
			}
		}
		printf("\n");
	}
}
void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char* layout)
{
	// initialise variables.
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (layout[k] == '1') {
				cave[i][j] = 1;
			}
			else if (layout[k] == '0') {
				cave[i][j] = 0;
			}
			else if (layout[k] == 'E') {
				cave[i][j] = 69;
			}
			k++;
		}
	}
}
int IsBorderComplete(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int i, j;
	int end = CAVE_SIZE - 1;

	// Loop through the border to check conditions.
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			// If there are any 0s' in the border, return 0.
			if (cave[0][j] == 0 || cave[end][j] == 0 || cave[i][0] == 0 || cave[i][end] == 0) {
				return 0;
			}
		}
	}
	return 1;
}
int IsExitUnique(int cave[CAVE_SIZE][CAVE_SIZE])
{
	// Initialise variables
	int i, j;
	int E = 0;
	// Determine if there only 1 E in the array.
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 69) {
				E++;
			}
		}
	}
	if (E != 1) {
		return 0;
	}
	return 1;
}
int IsExitAccessible(int cave[CAVE_SIZE][CAVE_SIZE])
{
	//initialise variables.
	int end = CAVE_SIZE - 1;
	int i, j;
	int E = 0;
	// Determine if there only 1 E in the array.
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 69) {
				E++;
			}
		}
	}
	if (E != 1) {
		return 0;

	}
	// Check if exit is in the corner
	if (cave[0][0] == 69 || cave[end][end] == 69 || cave[0][end] == 69 || cave[end][0] == 69) {
		return 0;
	}
	else {
		//Check if exit is inside the cave
		for (i = 1; i < CAVE_SIZE - 1; i++) {
			for (j = 1; j < CAVE_SIZE - 1; j++) {
				if (cave[i][j] == 69)
					return 0;
			}
		}
	}
	if (E == 1) {
		return 1;
	}
	return 0;
}
void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char element[])
{
	int i, j;
	char player[100] = "player";
	char boulder[100] = "boulder";
	char hole[100] = "hole";
	char treasure[100] = "treasure";
	int playercount = 0;

	// if trying to add out of bounds, return.
	if (row >= CAVE_SIZE || row < 0 || col >= CAVE_SIZE || col < 0) {
		return;
	}

	// Determine if preexisting player is in the game.

	if (strcmp(element, player) == 0) {
		for (i = 0; i < CAVE_SIZE; i++) {
			for (j = 0; j < CAVE_SIZE; j++) {
				if (cave[i][j] == 'X') {
					playercount++;
				}
			}
		}
	}

	// Add player
	if ((strcmp(element, player) == 0) && playercount == 0 && cave[row][col] == 0) {
		cave[row][col] = 'X';
	}
	//Add boulder
	if ((strcmp(element, boulder) == 0) && cave[row][col] == 0) {
		cave[row][col] = 'O';
	}
	//Add hole
	if ((strcmp(element, hole) == 0) && cave[row][col] == 0) {
		cave[row][col] = '*';
	}
	//Add treasure
	if ((strcmp(element, treasure) == 0) && cave[row][col] == 0) {
		cave[row][col] = '+';
	}
}
void RotateCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	// Initialise variables.
	int i, j;
	int transpose[CAVE_SIZE][CAVE_SIZE];
	int temp[CAVE_SIZE][CAVE_SIZE];

	// Transpose the cave into temperary array.
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			transpose[j][i] = cave[i][j];
		}
	}
	// Reverse each row of temperary array.
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			temp[i][j] = transpose[i][j];
		}
	}
	// set the cave as the new rotated cave.
	for (i = 0; i < CAVE_SIZE; i++) {
		int l = CAVE_SIZE - 1;
		for (j = 0; j < CAVE_SIZE; j++) {
			cave[i][j] = temp[i][l];
			l--;
		}
	}
}
int MakeMove(int cave[CAVE_SIZE][CAVE_SIZE], char move)
{
	int i, j, row = 0, col = 0;

	int turnboard;
	// Determine how many times to rotate the cave.
	if (move == 'w') {
		turnboard = 0;
	}
	else if (move == 'a') {
		turnboard = 1;
	}
	else if (move == 's') {
		turnboard = 2;
	}
	else if (move == 'd') {
		turnboard = 3;
	}
	// Rotate the cave.
	for (i = 0; i < turnboard; i++) {
		RotateCave(cave);
	}

	// Determine where the player is
	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 'X') {
				row = i;
				col = j;
				break;
			}
		}
	}

	// Moving the character when there is no obstacle.
	if (cave[row - 1][col] == 0 || cave[row - 1][col] == '+') {
		cave[row - 1][col] = cave[row][col];
		cave[row][col] = 0;
		// Player didn't fall into hole or exit. (standard return condition)
		for (i = 0; i < 4 - turnboard; i++) {
			RotateCave(cave);
		}
		return 0;
	}

	// If next to a wall, standard return.
	if (cave[row - 1][col] == 1) {
		for (i = 0; i < 4 - turnboard; i++) {
			RotateCave(cave);
		}
		return 0;
	}

	// If next to a boulder, push the boulder until it hits a wall.
	int k = row - 1;
	if (cave[k][col] == 'O') {
		while (cave[k][col] != 1 || cave[k][col] != 'O') {
			if (cave[k - 1][col] == '*') {
				cave[k - 1][col] = 0;
				cave[k][col] = 0;
				break;
			}
			if (cave[k - 1][col] == '+') {
				break;
			}
			if (cave[k - 1][col] == 1 || cave[k - 1][col] == 'O') {
				break;
			}
			if (k == 0) {
				cave[k][col] = 0;
				break;
			}
			if (cave[k - 1][col] != 1 && cave[k - 1][col] != 'O') {
				cave[k - 1][col] = cave[k][col];
				cave[k][col] = 0;
			}
			k--;
		}

		// player didn't fall into hole or exit. (standard return condition)
		for (i = 0; i < 4 - turnboard; i++) {
			RotateCave(cave);
		}
		return 0;
	}

	// If the player reaches the exit, 
	if (cave[row - 1][col] == 'E') {
		cave[row - 1][col] = 'X';
		cave[row][col] = 0;
		// Rotate the board back to original position and return.
		for (i = 0; i < 4 - turnboard; i++) {
			RotateCave(cave);
		}
		return 2;
	}
	// If the player falls into a hole.
	if (cave[row - 1][col] == '*') {
		cave[row][col] = 0;
		//Rotate the board back to original position and return.
		for (i = 0; i < 4 - turnboard; i++) {
			RotateCave(cave);
		}
		return 1;
	}
	return 0;
}

//Follow code was provided by the lecturer.
/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
		scanf("%c", &move);
	}
	return move;
}

/* The Boulder Break simulation */
int main(void)
{
	char story[2000];
	int gameOver = 0;

	// Game here -------------------------------------------------------------------------//
	char layout[200] = "11111111111111000001110001100000110000110000010000011000000000001100000000000111110000000011110000000001100000000000110000000111111000000000001E0000000000011111111111111";

	int cave[CAVE_SIZE][CAVE_SIZE];
	InitialiseCave(cave, layout);
	AddItem(cave, 3, 6, "player");
	AddItem(cave, 2, 8, "player");
	AddItem(cave, 8, 4, "boulder");
	AddItem(cave, 6, 3, "boulder");
	AddItem(cave, 5, 9, "boulder");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 11, 1, "hole");
	AddItem(cave, 9, 9, "treasure");
	AddItem(cave, 8, 9, "treasure");
	//------------------------------------------------------------------------------------//

	printf("ENGGEN131 - C Project 2022\n");
	printf("                          ... presents ...\n");
	printf("______   _____  _     _        ______  _______  ______\n");
	printf("|_____] |     | |     | |      |     \\ |______ |_____/\n");
	printf("|_____] |_____| |_____| |_____ |_____/ |______ |    \\_\n");
	printf("______   ______ _______ _______ _     _\n");
	printf("|_____] |_____/ |______ |_____| |____/ \n");
	printf("|_____] |    \\_ |______ |     | |    \\_\n");
	printf("\n");
	printf("%s\n", story);
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	PrintCave(cave);
	while (!gameOver) {
		gameOver = MakeMove(cave, GetMove());
		PrintCave(cave);
		if (gameOver == 1) {
			printf("\n\nGAME OVER!! \nYou died!\n\n");
		}
		else if (gameOver == 2) {
			printf("\n\nCONGRATULATIONS!! \nYou escaped!\n\n");
		}
	}

	return 0;
}