#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants
#define UNDEFINE -1
#define EXIT 0
#define DEFAULT 1
#define MANUAL 2
#define RANDOM 3

// Default referenced sequence
int DEFAULT_PAGE[] = {2, 1, 5, 2, 0, 8, 5, 0, 0, 0, 7};

// index of first page is swap in frames
int first_index = 0;

// number of page fault
int page_fault = 0;

// function to pause program
void pause_program();

// init array of frames
void init_frames(int **, int *);

// run fifo algorithm to return index of frame
// to be swapped out
int fifo_paging(int, int *, int);

// add page into frames
void add_page(int **, int, int);

// display_frames
void display_frames(int *, int);

int main()
{
  // random seed
  srand(time(NULL));

  // init variables
  int number_page;
  int number_frame;

  int *arr_pages = NULL;

  // choose the method for input referenced sequence
  int choose = 0;
  do
  {
    printf("--- Page Replacement Algorithm ---\n");
    printf(" 1. Default referenced sequence\n");
    printf(" 2. Manual input sequence\n");
    printf(" 3. Random input sequence\n");
    printf(" 0. Exit\n");

    printf("-- Choose your option: ");
    scanf("%d", &choose);

    if (choose == EXIT)
    {
      printf("Exitting...\n");
      return 0;
    }

    switch (choose)
    {
    case DEFAULT:
      arr_pages = (int *)DEFAULT_PAGE;
      number_page = sizeof(DEFAULT_PAGE) / sizeof(int);
      break;

    case MANUAL:
      printf("-- Input your number of pages: ");
      scanf("%d", &number_page);
      arr_pages = (int *)malloc(number_page * sizeof(int));

      printf("-- Input your referenced sequence: ");
      for (int i = 0; i < number_page; i++)
        scanf("%d", &(arr_pages[i]));
      break;

    case RANDOM:
      printf("-- Input your number of pages: ");
      scanf("%d", &number_page);
      arr_pages = (int *)malloc(number_page * sizeof(int));
      for (int i = 0; i < number_page; i++)
        arr_pages[i] = rand() % (int)(number_page * 0.7);
      break;

    default:
      printf("Invalid option. ",
             "Please try again and ",
             "press <Enter> to continue!\n");
      pause_program();
      system("clear");
      break;
    }
  } while (choose < 0 || choose > 3);

  int *arr_frames = NULL;
  init_frames(&arr_frames, &number_frame);

  // display information of test case
  system("clear");

  printf("--- FIFO - Page Replacement Algorithm ---\n");
  printf("  - Number of pages: %d\n", number_page);
  printf("  - Number of frames: %d\n", number_frame);
  printf("  - Referenced sequence:\n\t");
  for (int i = 0; i < number_page; i++)
    printf("%d ", arr_pages[i]);
  printf("\n");

  // run fifo algorithm and display step by step
  printf("\nSTT Page\tFrames\n");
  for (int i = 0; i < number_page; ++i)
  {
    printf("%2d   %3d\t", i, arr_pages[i]);
    int pos = fifo_paging(number_frame, arr_frames,
                          arr_pages[i]);
    if (pos != UNDEFINE)
      add_page(&arr_frames, pos, arr_pages[i]);
    display_frames(arr_frames, number_frame);

    if (pos != UNDEFINE)
    {
      page_fault++;
      printf("  *");
    }

    printf("\n");
  }

  printf("\nNumber of page fault: %d\n", page_fault);

  // free memory
  if (arr_pages != DEFAULT_PAGE)
    free(arr_pages);
  free(arr_frames);

  return 0;
}

void pause_program()
{
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }

  getchar();
}

void init_frames(int **arr_frames, int *number_frame)
{
  printf("-- Input your number of frames: ");
  scanf("%d", number_frame);

  *arr_frames = (int *)malloc(*number_frame * sizeof(int));

  for (int i = 0; i < *number_frame; i++)
    (*arr_frames)[i] = UNDEFINE;
}

int fifo_paging(int number_frame, int *arr_frames,
                int page)
{
  for (int i = 0; i < number_frame; i++)
  {
    if (arr_frames[i] == page)
      return UNDEFINE;

    if (arr_frames[i] == UNDEFINE)
      return i;
  }

  int pos = first_index;
  first_index++;
  first_index %= number_frame;
  return pos;
}

void add_page(int **arr_frames, int pos, int page)
{
  (*arr_frames)[pos] = page;
}

void display_frames(int *arr_frames, int number_frames)
{
  for (int i = 0; i < number_frames; i++)
    if (arr_frames[i] == UNDEFINE)
      printf("  _ ");
    else
      printf("%3d ", arr_frames[i]);
}
