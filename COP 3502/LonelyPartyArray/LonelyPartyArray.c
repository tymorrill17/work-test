// Tyler Morrill
// COP 3502, Spring 2019
// 


#include <stdlib.h>
#include <stdio.h>
#include "LonelyPartyArray.h"

// Creates a Lonely Party Array to be used by other functions
LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	LonelyPartyArray *party = malloc(sizeof(LonelyPartyArray));
	
	if (party == NULL)
	{
		return NULL;
	}	
	
	if (num_fragments < 0 || fragment_length < 0)
		return NULL;
	
	party->num_fragments = num_fragments;
	party->fragment_length = fragment_length;
	party->num_active_fragments = 0;
	party->size = 0;

	// Dynamically allocates the fragments pointer array and sets each space to NULL
	party->fragments = malloc(sizeof(int *) * num_fragments);	
	if (party->fragments == NULL)
	{
		free(party);
		return NULL;
	}
	for (i = 0; i < num_fragments; i++)
	{
		party->fragments[i] = NULL;
	}
	
	// Dynamically allocates the fragment_sizes int array and sets each space to 0
	party->fragment_sizes = malloc(sizeof(int) * num_fragments);
	if (party->fragment_sizes == NULL)
	{
		free(party);
		free(party->fragments);
	}
	for (i = 0; i < num_fragments; i++)
	{
		party->fragment_sizes[i] = 0;
	}	
	
	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n",
		num_fragments * fragment_length, num_fragments);
	
	return party;
}

// Deallocates all memory associated with the LPA and sends it to the void where it came from
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;
	if (party == NULL)
		return NULL;
	if (party->fragments == NULL)
		return NULL;
		
	for (i = 0; i < party->num_fragments; i++)
		if (party->fragments[i] != NULL)
			free(party->fragments[i]);
	
	free(party->fragments);
	free(party->fragment_sizes);
	free(party);
	
	printf("-> The LonelyPartyArray has returned to the void.\n");
	
	return NULL;
}


// Checks if the passed index is valid
int isInvalidIndex(LonelyPartyArray *party, int index)
{
	if (index < 0)
		return 1;
	else if (index > party->num_fragments * party->fragment_length - 1)
		return 1;
	else
		return 0;
	
}


// Takes key and puts it into the index of the LPA, creates fragment if NULL
int set(LonelyPartyArray *party, int index, int key)
{	
	int fragment_num, fragment_index, i, lo, hi;
	
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}
	
	fragment_num = index / party->fragment_length;
	fragment_index = index % party->fragment_length;
	lo = fragment_num * party->fragment_length;
	hi = lo + party->fragment_length - 1;
	
	if (isInvalidIndex(party, index))
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", 
			index, fragment_num, fragment_index);
		return LPA_FAILURE;
	}
	
	// Allocates fragments not yet in use
	if (party->fragments[fragment_num] == NULL)
	{
		party->fragments[fragment_num] = malloc(sizeof(int) * party->fragment_length);
		
		if (party->fragments[fragment_num] == NULL)
		{
			return LPA_FAILURE;
		}
			
		for (i = 0; i < party->fragment_length; i++)
			party->fragments[fragment_num][i] = UNUSED;
			
		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", fragment_num, 
			party->fragment_length, lo, hi);	
		party->num_active_fragments++;
	}
	
	if (party->fragments[fragment_num][fragment_index] == UNUSED)
	{
		party->size++;
		party->fragment_sizes[fragment_num]++;
	}
		
	party->fragments[fragment_num][fragment_index] = key;
	
	return LPA_SUCCESS;
}

// Returns the value at the specified index if it is valid
int get(LonelyPartyArray *party, int index)
{
	int fragment_num, fragment_index;

	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}
	
	fragment_num = index / party->fragment_length;
	fragment_index = index % party->fragment_length;
	
	if (isInvalidIndex(party, index))
	{
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", 
			index, fragment_num, fragment_index);
		return LPA_FAILURE;
	}
	
	if (party->fragments[fragment_num] != NULL)
		return party->fragments[fragment_num][fragment_index];
	else
		return UNUSED;
}

// Removes the value at the specified index (sets it to UNUSED). If the index is the last value
// in the fragment, it deallocates the fragment and sets the LPA's attributes to the correct values
// (i.e. size, num_active_fragments)
int delete(LonelyPartyArray *party, int index)
{
	int fragment_num, fragment_index, i, lo, hi;
	
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}
	
	fragment_num = index / party->fragment_length;
	fragment_index = index % party->fragment_length;
	lo = fragment_num * party->fragment_length;
	hi = lo + party->fragment_length - 1;
	
	if (isInvalidIndex(party, index))
	{
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", 
			index, fragment_num, fragment_index);
		return LPA_FAILURE;
	}
	
	if (party->fragments[fragment_num] == NULL)
		return LPA_FAILURE;
	
	// Deletes set value
	if (party->fragments[fragment_num][fragment_index] != UNUSED)
	{
		party->fragments[fragment_num][fragment_index] = UNUSED;
		party->size--;
		party->fragment_sizes[fragment_num]--;
		
		// Deallocates fragment if it's empty
		if (party->fragment_sizes[fragment_num] == 0)
		{
			free(party->fragments[fragment_num]);
			party->fragments[fragment_num] = NULL;
			printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", fragment_num, 
				party->fragment_length, lo, hi);
			party->num_active_fragments--;
		}
		return LPA_SUCCESS;
	}
	return LPA_FAILURE;
}

// Returns true if the LPA contains the specified key
int containsKey(LonelyPartyArray *party, int key)
{
	int i;
	if (party == NULL)
		return 0;
		
	for (i = 0; i < party->fragment_length * party->num_fragments; i++)
		if (get(party, i) == key)
			return 1;
	
	return 0;
}

// Returns true if the cell at the index has been set
int isSet(LonelyPartyArray *party, int index)
{
	if (party == NULL)
		return 0;
	if (isInvalidIndex(party, index))
		return 0;
	
	if (get(party, index) == UNUSED || get(party, index) == LPA_FAILURE)
		return 0;
	
	return 1;
}

// Checks if the index is valid and prints the value there if it has been set
int printIfValid(LonelyPartyArray *party, int index)
{
	if (party == NULL)
		return LPA_FAILURE;
	if (isInvalidIndex(party, index))
		return LPA_FAILURE;
		
	if(isSet(party, index))
	{
		printf("%d\n", get(party, index));
		return LPA_SUCCESS;
	}
	else
	{
		return LPA_FAILURE;
	}	
}

// Resets the LonelyPartyArray to its initialized state
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int i;
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return party;
	}
	
	// Frees each of the allocated fragments
	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			free(party->fragments[i]);
			party->fragments[i] = NULL;
		}
		party->fragment_sizes[i] = 0;
	}
	
	party->size = 0;
	party->num_active_fragments = 0;
	printf("-> The LonelyPartyArray has returned to its nascent state. ");
	printf("(capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, 
		party->num_fragments);
	
	return party;
}

// Returns the size member of the LPA struct
int getSize(LonelyPartyArray *party)
{
	if (party == NULL)
		return LPA_FAILURE;
	
	return party->size;
}

// Returns the capacity of the whole LPA
int getCapacity(LonelyPartyArray *party)
{
	if (party == NULL)
		return LPA_FAILURE;
		
	return party->fragment_length * party->num_fragments;
}

// Returns how many cells are in the current number of allocated fragments
int getAllocatedCellCount(LonelyPartyArray *party)
{
	if (party == NULL)
		return LPA_FAILURE;
		
	return party->num_active_fragments * party->fragment_length;
}

// Returns the total memory a normal array would take up instead of a LPA
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	if (party == NULL)
		return LPA_FAILURE;
	int x = getCapacity(party);
	return (long long unsigned int)(x * sizeof(int));
}

// Returns the total memory the LonelyPartyArray occupies
long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	int array_size, LPA_pointer, LPA_size, fragments_size, fragment_sizes_size, active_size;
	long long unsigned int total;
	if (party == NULL)
		return LPA_FAILURE;
	
	array_size = party->num_active_fragments * party->fragment_length * sizeof(int);
	LPA_pointer = sizeof(LonelyPartyArray *);
	LPA_size = sizeof(LonelyPartyArray);
	fragments_size = sizeof(int *) * party->num_fragments;
	fragment_sizes_size = sizeof(int) * party->num_fragments;
	total = array_size + LPA_pointer + LPA_size + fragments_size + fragment_sizes_size;
	
	return total;
}

LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
	int i, j;
	if (party == NULL)
		return NULL;
	if (party->fragments == NULL)
		return NULL;
	if (party->fragment_sizes == NULL)
		return NULL;
		
	LonelyPartyArray *LPA = malloc(sizeof(LonelyPartyArray));
	if (LPA == NULL)
	{
		return NULL;
	}	
	
	// Transfers mother array party's values to new array LPA
	LPA->num_fragments = party->num_fragments;
	LPA->fragment_length = party->fragment_length;
	LPA->num_active_fragments = party->num_active_fragments;
	LPA->size = party->size;

	LPA->fragments = malloc(sizeof(int *) * LPA->num_fragments);	
	if (LPA->fragments == NULL)
	{
		free(LPA);
		return NULL;
	}
	for (i = 0; i < LPA->num_fragments; i++)
	{
		if (party->fragments[i] == NULL)
			LPA->fragments[i] = NULL;
		else
			LPA->fragments[i] = malloc(sizeof(int) * LPA->fragment_length);
	}
	
	// Dynamically allocates the fragment_sizes int array and sets each space to the corresponding
	// value in the mother LPA
	LPA->fragment_sizes = malloc(sizeof(int) * LPA->num_fragments);
	if (LPA->fragment_sizes == NULL)
	{
		free(LPA);
		
		for (i = 0; i < party->num_fragments; i++)
			if (party->fragments[i] != NULL)
				free(party->fragments[i]);
				
		free(LPA->fragments);
	}
	
	// Sets the values of the occupied cells in party to the corresponding cells in LPA
	for (i = 0; i < LPA->num_fragments; i++)
	{
		LPA->fragment_sizes[i] = party->fragment_sizes[i];
	}	
	
	for (i = 0; i < LPA->num_fragments; i++)
	{
		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < LPA->fragment_length; j++)
			{
				LPA->fragments[i][j] = party->fragments[i][j];
			}
		}
	}
	
	printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n",
		getCapacity(LPA), LPA->num_fragments);
	
	return LPA;
}

double difficultyRating(void)
{
	return 4.0;
}


double hoursSpent(void)
{
	return 12.0;
}



