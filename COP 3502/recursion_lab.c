#include <stdio.h>
#include <stdlib.h>

int getTriNum(int x, int y)
{
	if (x == 1 && y == 1)
		return 1;
	if (x == 1)
		return 1 + getTriNum(y-1, x);
	return 1 + getTriNum(x-1, y+1);
}



int main(int argc, char *argv[])
{	
	
	printf("%d\n", getTriNum(atoi(argv[1]), atoi(argv[2])));
	return 0;
}
