// Tyler Morrill
// COP 3502, Spring 2019
// ty262581

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DupeyDupe.h"

double difficultyRating(void)
{
	return 3.0;
}

double hoursSpent(void)
{
	return 2.0;
}

int main(int argc, char **argv)
{
	int i, j, found_match = 0;
	int num_strings = argc - 1;
	
	for (i = num_strings; i > 0; i--)
	{
		if (found_match == 0)
		{
			for (j = 1; j < i; j++)
			{
				if (strcmp(argv[i], argv[j]) == 0)
				{
					printf("%s\n", argv[i]);
					found_match = 1;
					break;
				}
			}
		}
	}
	
	for (i = 1; i < num_strings; i++)
	{
		if (strcmp(argv[i], "dupe") == 0 && strcmp(argv[i + 1], "dupe") == 0)
		{
			printf("dupe dupe!\n");
			return 0;
		}
	}
	
	if (found_match == 0)
	{
		printf("no dupey dupe :(\n");
	}
	else 
	{
		return 0;
	}
}
