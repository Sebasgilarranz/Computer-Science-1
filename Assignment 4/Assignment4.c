// Sebastian Gilarranz
// COP 3502, Fall 2018
// se171788
// Program 2 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LonelyPartyArray.h"


LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int column;
	LonelyPartyArray *party;
	
	// Checking to see if parameters passed are ok
	if ((num_fragments > 0) && (fragment_length > 0))
		party = malloc(sizeof(LonelyPartyArray));

	// if paramaters were invalid.
	else 
		return NULL;

	// Checking if Malloc() failed.
	if (party != NULL)
	{
		party->num_fragments = num_fragments;
		party->fragment_length = fragment_length;
		party->num_active_fragments = 0;
		party->size = 0;

		// dynamically allocating space for fragments and sizes.
		party->fragments = malloc(sizeof(int*) * (party->num_fragments));
		party->fragment_sizes = malloc(sizeof(int) * (party->num_fragments));
		
		// checking if malloc() was succesfull. 
		if (party->fragment_sizes != NULL)
		{
			for (column=0; column < party->num_fragments; column++)
			{
				party->fragment_sizes[column] = 0;
			}
		}
	
		// if malloc() failed.
		else 
		{
			destroyLonelyPartyArray(party);
			return NULL;
		}
		
		// checking if malloc() was successfull. 
		if (party->fragments != NULL)
		{
			for (column=0; column < party->num_fragments; column++)
				party->fragments[column] = NULL;
		}
		
		// if malloc() failed.
		else 
		{
			destroyLonelyPartyArray(party);
			return NULL;
		}
	}
	
	// if malloc() failed.
	else 
		return NULL;
	
	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", (party->fragment_length * party->num_fragments), party->num_fragments);
	
	return party;
}


LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int column;


	if (party != NULL)
	{
		// freeing each column of fragments.
		for (column = 0; column < party->num_fragments; column++)
			free(party->fragments[column]);
		
		// now we can free everything else.
		free(party->fragments);
		free(party->fragment_sizes);
		free(party);
		
		printf("-> The LonelyPartyArray has returned to the void.\n");
	}

	return NULL;
}


int set(LonelyPartyArray *party, int index, int key)
{
	int column, row, s_row, count = 0, w_count = 0, w_frag = 0, w_offset = 0, neg_holder = 0, w_column = 0;
	
	// if party is empty.
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}
	
	// checking if index is valid.
	else if (index > ((party->num_fragments) * (party->fragment_length)-1) || index < 0)
	{
		// checking if negative so we can hold negative. 
		if (index < 0)
		{
			neg_holder = index;
			index = index * -1;
		}

		w_column = index / party->fragment_length;
		count = w_column * party->fragment_length;
	
		// we know what column so now we look for the row
		for (row = 0; row < party->fragment_length; row++)
		{
			if (index == count)
			{
				w_frag = w_column;
				w_offset = w_count;
				break;
			}
			
			count++;
			w_count++;
		}
	
	// print normally if index wasnt negative. 
	if (neg_holder == 0)
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, w_frag, w_offset);
	}
	
	// now we convert back to negative. 
	else 
	{
		index = index * -1;
		w_frag = w_frag * -1;
		w_offset = w_offset * -1;
		
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index , w_frag, w_offset);
	}

	return LPA_FAILURE;
	}	
	
	// if index is valid
	else 
	{
		// locating the column for index and setting count to the first cell in that column. 
		column = index / party->fragment_length;
		count = column * party->fragment_length;
		
		// going through each row.
		for (row = 0; row < party->fragment_length; row++)
		{
			// we got corresponding index.
			if (count == index)
			{
				if (party->fragments[column] == NULL)
				{
					
					party->fragments[column] = malloc(sizeof(int) * (party->fragment_length));
					
					// checking if malloc() worked.
					if (party->fragments[column] == NULL)
					{
						return LPA_FAILURE;
					}
					
					else 
					{
						// setting each cell to Unused in fragment.
						for (s_row = 0; s_row < party->fragment_length; s_row++)
						{
							party->fragments[column][s_row] = UNUSED;
						}
					
					// whole bunch of updates.
					party->num_active_fragments++;
					party->fragments[column][row] = key;
					party->size++;
					party->fragment_sizes[column]++;
					
					printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", column, party->fragment_length, (column * party->fragment_length), ((column * party->fragment_length) + (party->fragment_length) - 1));
					
					}
				}
				
				// if fragment was already allocatde but the cell is Unused.
				else if (party->fragments[column] != NULL && party->fragments[column][row] == UNUSED)
				{
					// whole bunch of updates. 
					party->fragments[column][row] = key;
					party->size++;
					party->fragment_sizes[column]++;
				}
					
				// if fragment was already allocated and the cell was already being used. 
				else if (party->fragments[column] != NULL && party->fragments[column][row] != UNUSED)
				{
					party->fragments[column][row] = key;
				}
			}
			
			count++;
			w_count++;
		}
	}

	return LPA_SUCCESS;
}


int get(LonelyPartyArray *party, int index)
{
	int column, row, count = 0, w_count = 0, w_frag = 0, w_offset = 0, neg_holder = 0, w_column = 0;
	
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}
	
	// checking if index is valid or neg.
	else if (index > ((party->num_fragments) * (party->fragment_length)-1) || index < 0)
	{
		// if index is negative. 
		if (index < 0)
		{
			neg_holder = index;
			index = index * -1;
		}

		w_column = index / party->fragment_length;
		count = w_column * party->fragment_length;
		
		// going through the column of fragment. 
		for (column = 0; column < party->fragment_length; column++)
		{
			// we got a hit. 
			if (index == count)
			{
				w_frag = w_column;
				w_offset = w_count;
				break;
			}
			
			count++;
			w_count++;
		}
	
		// if index was negative. 
		if (neg_holder == 0)
		{
			printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index , w_frag, w_offset);
		}
		
		// convert everything back to negative. 
		else 
		{
			index = index * -1;
			w_frag = w_frag * -1;
			w_offset = w_offset * -1;
			printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index , w_frag, w_offset);
		}
	
		return LPA_FAILURE;
	}	
	
	// now if index was valid.
	else 
	{
		// find what column we need.
		column = index / party->fragment_length;
		count = column * party->fragment_length;
		
		// go through each cell. 
		for (row = 0; row < party->fragment_length; row++)
		{
			// check if index is a match and if fragment is or isnt null
			if (count == index && party->fragments[column] != NULL)
				return party->fragments[column][row];
			
			else if (count == index && party->fragments[column] == NULL)
				return UNUSED;
			
			count++;
		}
	}
	
	return LPA_FAILURE;
}


int delete(LonelyPartyArray *party, int index)
{
	int count = 0,row, w_count = 0, w_frag, w_offset, neg_holder = 0, w_column = 0, column;
	
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}
	
	// checking if index is valid or neg.
	else if (index > ((party->num_fragments) * (party->fragment_length) - 1) || index < 0)
	{
		// if index is negative. 
		if (index < 0)
		{
			neg_holder = index;
			index = index * -1;
		}

		w_column = index / party->fragment_length;
		count = w_column * party->fragment_length;
		
		// going through the column of fragment. 
		for (column = 0; column < party->fragment_length; column++)
		{
			// we got a hit. 
			if (index == count)
			{
				w_frag = w_column;
				w_offset = w_count;
				break;
			}
			
			count++;
			w_count++;
		}
	
		// if index was negative. 
		if (neg_holder == 0)
		{
			printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, w_frag, w_offset);
		}
		
		// convert everything back to negative. 
		else 
		{
			index = index * -1;
			w_frag = w_frag * -1;
			w_offset = w_offset * -1;
			printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, w_frag, w_offset);
		}
	
		return LPA_FAILURE;
	}		
	
	// if index is ok.
	else 
	{
		// find what column we need.
		column = index / party->fragment_length;
		count = column * party->fragment_length;			
		
		// going through each cell to get a match
		for (row = 0; row < party->fragment_length; row++)
		{
			
			// if count and if column isnt null
			if (count == index && party->fragments[column] != NULL)
			{
				// if cell isnt used. 
				if (party->fragments[column][row] == UNUSED)
					return LPA_FAILURE;
				
				// if cell is beinng used
				else 
				{
					// delete fragment. and subtract from some things. 
					party->fragments[column][row] = UNUSED;
					party->size--;
					party->fragment_sizes[column]--;

					// when column reaches 0.
					if (party->fragment_sizes[column] == 0)
					{	
						// free the fragments, set to NULL, subtract active frags,
						free(party->fragments[column]);
						party->fragments[column] = NULL;
						party->num_active_fragments--;
						
						printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n",column, party->fragment_length, (column * party->fragment_length), ((column * party->fragment_length) + (party->fragment_length) - 1));
					}
				}
			}
			
			// if index is correct and fragment column is NULL
			else if (count == index && party->fragments[column] == NULL)
				return LPA_FAILURE;

			count++;
		}
	}
	
	return LPA_SUCCESS;
}


int containsKey(LonelyPartyArray *party, int key)
{
	int column, row, s_row;
	
	if (party == NULL)
		return 0;
	
	// looping through fragments to find key
	for (column = 0; column < party->num_fragments; column++)
	{
			// checking if fragment column is null
			if (party->fragments[column] != NULL)
			{
				// going through the row to see if theres a match.
				for (s_row = 0; s_row < party->fragment_length; s_row++)
				{
					if (party->fragments[column][s_row] == key)
						return 1;
				}
			}
		}
	
	return 0;
}


int isSet(LonelyPartyArray *party, int index)
{
	int count = 0, column, row;
	
	if (party == NULL)
		return 0;

	// checking if index is invalid.
	else if (index > ((party->num_fragments)*(party->fragment_length) - 1) || index < 0)
		return 0;
	
	// if index is valid.
	else 
	{
		// finding the column
		column = index / party->fragment_length;
		count = column * party->fragment_length;		
		
		// looping through the rows
		for (row = 0; row < party->fragment_length; row++)
		{
			// if correct index and party is not null.
			if (count == index && party->fragments[column] != NULL)
			{
				// if call is being used.
				if (party->fragments[column][row] != UNUSED)
					return 1;
				
				else 
					return 0;
			}
			
			// if fragment column is not being used. 
			else if (count == index && party->fragments[column] == NULL)
				return 0;

			count++;
		}
	}
	
	return 0;
}


int printIfValid(LonelyPartyArray *party, int index)
{
	int count = 0, column, row;
	
	// checking is index is corresponding to a used cell.
	if (isSet(party,index) == 0)
		return LPA_FAILURE;
	
	// if cell is being used.
	else 
	{
		// finding correct column for index.
		column = index / party->fragment_length;
		count = column * party->fragment_length;		
		
		// looping through row. 
		for (row = 0; row < party->fragment_length; row++)
		{
			// if index is a match.
			if (count == index)
				printf("%d\n",party->fragments[column][row]);

			count++;
		}
	}
	
	return LPA_SUCCESS;
}


LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int count = 0, column, row;
	
	if (party == NULL)
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().");
	
	// looping through entire fragments array.
	for (column = 0; column < party->num_fragments; column ++)
	{
		for (row = 0; row < party->fragment_length; row++)
		{
			// if collumn isnt null
			if (party->fragments[column] != NULL)
			{
				// reset fragment. and other calculations.
				party->fragments[column][row] = UNUSED;
				party->size--;
				party->fragment_sizes[column]--;

				// if fragment has no cells left. 
				if (party->fragment_sizes[column] == 0)
				{	
					// free memory.
					free(party->fragments[column]);
					party->fragments[column] = NULL;
					party->num_active_fragments--;
				}
			}
		}
		count++;
	}
	
	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", (party->fragment_length*party->num_fragments), party->num_fragments);
	
	return party;
}


int getSize(LonelyPartyArray *party)
{
	// return size of party if party isnt null
	if (party == NULL)
		return -1;

	return party->size;
}


int getCapacity(LonelyPartyArray *party)
{
	// if party isnt null return num_fragments times fragment_length.
	if (party == NULL)
		return -1;
	
	return (party->num_fragments * party->fragment_length);
}


int getAllocatedCellCount(LonelyPartyArray *party)
{
	// if party isnt null return (num_active_fragments * fragment_length.)
	if (party == NULL)
		return -1;

	return (party->num_active_fragments * party->fragment_length);
}


long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	// if party isnt NULL return total array sizes.
	if (party == NULL)
		return 0;

	return ((long long unsigned int)(party->num_fragments * party->fragment_length)*sizeof(int));
}


long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	// if party isnt NULL return whole size of struct 
	if (party == NULL)
		return 0;

	return ((long long unsigned int)(sizeof(LPA*) + sizeof(LPA) + (sizeof(party->fragments)*(party->num_fragments)) + (sizeof(int)*(party->num_fragments)) + (sizeof(int)*party->num_active_fragments*party->fragment_length)));
}


double difficultyRating(void)
{
	return 4.5;
}


double hoursSpent(void)
{
	return 30;
}


LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
	int column, row, count = 0;
	LonelyPartyArray *newParty;
	
	if (party == NULL){
		return NULL;
	}

	newParty = malloc(sizeof(LonelyPartyArray));
	
	// checking if malloc was successfull
	if (newParty == NULL)
	{
		return NULL;
	}
	
	// if it was
	else 
	{
		// copy all integers from party to newParty.
		newParty->num_fragments = party->num_fragments;
		newParty->fragment_length = party->fragment_length;
		newParty->num_active_fragments = party->num_active_fragments;
		newParty->size = party->size;

		// allocate fragments and fragment sizes.
		newParty->fragments = malloc(sizeof(int*) * (newParty->num_fragments));
		newParty->fragment_sizes = malloc(sizeof(int) * (newParty->num_fragments));
		
		// if malloc() was successfull.
		if (newParty->fragment_sizes != NULL)
		{
			for (column=0; column < newParty->num_fragments; column++)
			{
				newParty->fragment_sizes[column] = 0;
			}
		}
		
		// if malloc() failed.
		else 
		{
			destroyLonelyPartyArray(newParty);
			return NULL;
		}
	
		// if malloc() was successfull.
		if (newParty->fragments != NULL)
		{
			for (column=0; column < newParty->num_fragments; column++)
				newParty->fragments[column] = NULL;
		}
		
		// if malloc () failed
		else 
		{
			destroyLonelyPartyArray(newParty);
			return NULL;
		}

		// loop through fragments
		for (column = 0; column < newParty->num_fragments; column++)
		{
			// if current fragment is not null
			if (party->fragments[column] != NULL)
			{
				// allocate frament
				newParty->fragments[column] = malloc(sizeof(int) * newParty->fragment_length);
				
				// checking if malloc failed.
				if (newParty->fragments[column] == NULL)
				{
					destroyLonelyPartyArray(newParty);
					return NULL;
				}
			}
				// check each cell (if not null)
				for (row = 0; row < newParty->fragment_length; row++)
				{
					// if fragment isnt null 
					if (newParty->fragments[column] != NULL)
					{
						newParty->fragments[column][row] = party->fragments[column][row];
					}
					
				}
		}
	}
	
	printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n", (newParty->num_fragments * newParty->fragment_length), newParty->num_fragments);
	
	return newParty;
}
