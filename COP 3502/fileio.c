#include <stdio.h>



void foo(void)
{
	int *pointer = NULL;
	*pointer = 4;
}

int main(void)
{
	FILE *ifp = fopen("text.txt", "r");
	foo();
	char c;
	fscanf(ifp, "%c", &c);
	
	printf("%c\n", c);
}
