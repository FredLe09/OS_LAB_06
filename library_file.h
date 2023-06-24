#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define UNDEFINE -1

#define EXIT 0
#define DEFAULT 1
#define MANUAL 2
#define RANDOM 3

// Pause program
// Wait for user press <Enter> to continue
void pause_program();

// Input referenced sequence
void input_referenced_sequence(int *, int *, int);

// Init frames
void init_frames(int *, int);

// Output frames
void output_frames(int *, int);

// Check page fault
// return 1 if page fault
// return 0 if not page fault
int check_page_fault(int *, int, int);