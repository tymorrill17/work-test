#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Dynamic Memory Allocation

int main(void)
{
	int *dynamicInteger;
	dynamicInteger = malloc(sizeof(int)); // allocates memory to fit an int variable
	
	free(dynamicInteger); // releases the allocation
	
	printf("%f\n", sqrt(25));
}
	
	
	// stack space vs. heap space
