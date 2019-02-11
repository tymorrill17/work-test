// Sean Szumlanski
// COP 3502, Spring 2019

// =======================
// DupeyDupe: UnitTest01.c
// =======================
// This test case verifies that your difficultyRating() function returns a value
// within the expected range (as defined in the assignment PDF).
//
// For instructions on compiling your program with this source code, please see
// the assignment PDF.


#include <stdio.h>
#include "DupeyDupe.h"

// This acts as the main() function for this test case.
int unit_test(int argc, char **argv)
{
	int success = 1;

	// difficultyRating() must return a double on the range [1.0, 5.0].
	if (difficultyRating() < 1.0 || difficultyRating() > 5.0)
		success = 0;

	printf("%s\n", success ? "Success!" : "Fail whale!");
	return 0;
}
