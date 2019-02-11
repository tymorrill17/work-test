// Sean Szumlanski
// COP 3502, Spring 2019 - Week #2 Lab Activity
//
// =============================================================================
// EXERCISES
// =============================================================================
//
// PART 1: Tracing with Pointers and Dynamic Memory Allocation
//
// 1. BEFORE RUNNING THIS PROGRAM, read through it to determine what it's doing.
//    Draw diagrams that show exactly what memory looks like. I.e., draw boxes
//    for each variable in main(), give them each their own fake memory
//    addresses, and any time there's a pointer stored in memory, make sure that
//    its value reflects the appropriate made-up memory address that it should
//    contain.
//
//    You might want to start in main() and trace through it line by line,
//    reading any functions you're unfamiliar with whenever they get called.
//
//    The worksheet for this lab will help you keep track of your diagrams.
//
// 2. Based on your diagrams, predict what the output of main() will be. Then
//    compile and run this program to see if the output is what you expected. If
//    not, trace through carefully to figure out why your hypothesis about the
//    output was incorrect.
//
//    NOTE: When you run the program, it will crash. Don't worry about that just
//          yet. Tracking down the cause of that crash is the next exercise.
//
// =============================================================================
//
// PART 2: Tracking Down a Crash
//
// 1. Before even reading through the code, track down exactly which line is
//    causing this program to crash.
//
//    -> Try compiling this code with and without the -g flag, and see how those
//       different options affect the output of gdb.
//
// 2. After identifying the line that causes this to crash, trace through the
//    code to see if you can identify and explain why the code was crashing on
//    that particular line.
//
// 3. Next, modify the code to eliminate all crashes, but be careful not to
//    introduce any memory leaks as you do so, and do not change the code's core
//    functionality! Note that there are at least two decent ways to resolve the
//    crash.
//
// =============================================================================


#include <stdio.h>
#include <stdlib.h>

typedef struct bauble
{
	int x;

	struct bauble *before;
	struct bauble *after;
} bauble;


bauble *make_new_bauble(int x)
{
	bauble *baub = malloc(sizeof(bauble));

	baub->x = x;
	baub->before = NULL;
	baub->after = NULL;

	return baub;
}

void fuse_baubles_together(bauble *baub1, bauble *baub2)
{
	baub1->after = baub2;
	baub2->before = baub1;
}

void print_baubles(bauble *baub)
{
	bauble *temp;

	temp = baub;

	while (temp != NULL)
	{
		printf("%d ", temp->x);
		temp = temp->before;
	}
	printf("\n");
}

void free_bauble(bauble *baub)
{
	free(baub->after);
	free(baub->before);
	free(baub);
}

int main(void)
{
	bauble *a, *b, *c;

	// What does memory look like after all three of these function calls have
	// been executed?
	a = make_new_bauble(55);
	b = make_new_bauble(11);
	c = make_new_bauble(22);

	// What does memory look like after calling the following function? Draw a
	// separate diagram showing the results of each function call.
	fuse_baubles_together(c, b);
	fuse_baubles_together(a, c);

	// QUESTION: Does calling the print_baubles() function change a, b, or c in
	// any way whatsoever, or do they remain the same?

	// What is the output of the following function calls?
	print_baubles(a);
	print_baubles(b);

	// What does memory look like after calling the following function?
	fuse_baubles_together(a, b);

	// What is the output of the following function calls?
	print_baubles(a);
	print_baubles(b);

	// If you're working on Exercise #1 (drawing memory diagrams and predicting
	// the output of this program), you only need to draw a diagram for what
	// happens after the first call to free_bauble(). However, you will want to
	// trace through and understand what's happening with all three calls as you
	// work on Exercise #2.
	free_bauble(a);
	free_bauble(b);
	free_bauble(c);

	return 0;
}
