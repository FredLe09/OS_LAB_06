#include "library_file.h"

void pause_program()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    getchar();
}

void input_referenced_sequence(int *page, int *numberPage, int iCritical)
{
    switch (iCritical)
    {
    case 1:
        *numberPage = 11;

        page = (int *)malloc(*numberPage * sizeof(int));
        page[0] = 2;
        page[1] = 1;
        page[2] = 5;
        page[3] = 2;
        page[4] = 0;
        page[5] = 8;
        page[6] = 5;
        page[7] = 0;
        page[8] = 0;
        page[9] = 0;
        page[10] = 7;

        printf("%d", page[0]);

        break;

    case 2:
        printf("-- Input your number of page: ");
        scanf("%d", numberPage);

        page = (int *)malloc(*numberPage * sizeof(int));
        for (int i = 0; i < *numberPage; i++)
        {
            printf("-- -- Input your page[%d]: ", i);
            scanf("%d", page[i]);
        }
        break;

    case 3:
        printf("-- Input your number of page: ");
        scanf("%d", numberPage);

        page = (int *)malloc(*numberPage * sizeof(int));
        int max_index_page = *numberPage * 2 + 1;
        for (int i = 0; i < *numberPage; i++)
            page[i] = rand() % max_index_page;

        break;
    }
}

void init_frames(int *frames, int numberFrame)
{
    frames = (int *)malloc(numberFrame * sizeof(int));

    for (int i = 0; i < numberFrame; i++)
        frames[i] = UNDEFINE;
}

void output_frames(int *frames, int numberFrame)
{
    for (int i = 0; i < numberFrame; i++)
        if (frames[i] == UNDEFINE)
            printf("  - ");
        else
            printf("%3d ", frames[i]);
}

int check_page_fault(int *frame, int numberFrame, int page)
{
    for (int i = 0; i < numberFrame; i++)
    {
        if (frame[i] == UNDEFINE)
            return 1;

        if (frame[i] == page)
            return 0;
    }
    return 1;
}
