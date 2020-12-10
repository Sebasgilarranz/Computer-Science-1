// Sebastian Gilarranz
// COP 3502, Fall 2018
// se171788
// Program 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SneakyRooks.h"

int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
	// Dynamically allocating memory to track the Column and row of rook, as well as 
	// the coordinate struct.
	int *trackCol = calloc(boardSize, sizeof(int*)), *trackRow = calloc(boardSize, sizeof(int*)), retValue = 1;
	Coordinate *holder = malloc(sizeof(Coordinate));
	
	// Loop through rookStrings, to get coordinates.
	for (int i = 0; i < numRooks; i++)
	{
		parseCoordinateString(rookStrings[i], holder);

		// Keep track how many of eachcolumn and row of each rook.
		trackCol[holder->col]++;
		trackRow[holder->row]++;

		// If theres more than two in a row or column then they can attack eachother.
		if (trackCol[holder->col] == 2 || trackRow[holder->row] == 2)
			retValue = 0;
	}	

	// Cleaning up our mess.
	free(holder);
	free(trackCol);
	free(trackRow);

	return retValue;
}

void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
 	// Just alittle bit of initialization, no dynamic allocation woooohoooo!
 	int lenStr = strlen(rookString), actCol = 0, row = 0, spot = 0;

 	// Loop through each character in rookString
 	for (int i = 0; i < lenStr; i++)
 	{
 		// If the character is alpha then we do some arithmetic to calculate 
 		// the numeric value of alpha.
 		if (isalpha(rookString[i]))
 		{
 			actCol *= 26;
 			actCol += rookString[i] - ('a' - 1);
 			spot++;
 		}
 		
 		// break early to not waste time.
 		else 
 			break;
 	}

 	// Use atoi to extract the row.
 	row += atoi(&rookString[spot]);

 	// Assign the col and row values in the struct to these local values.
 	rookCoordinate->col = actCol;
 	rookCoordinate->row = row;
 }

double difficultyRating(void)
{
	return 1.6969;
}

double hoursSpent(void)
{
	return 3.6969;
}