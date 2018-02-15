#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWLEN 11
#define COLLEN 2

typedef struct Mem
{
    int partsize;
    int numparts;
    int memreqs[ROWLEN][COLLEN];

} Mem;

int** expandArray(int** arr, int row, int col, int newrow, int newcol);

void main(void)
{
    /* initialize variables */
    int i = 0;
    int length = 0;
    int read = 0;
    char nl;
    Mem mem = {512, 10, {{0}}}; // initialize the struct

    mem.memreqs[0][0] = ROWLEN; // first row elment stores the number of rows
    mem.memreqs[0][1] = COLLEN; // first col element stores the number of columns
    
    printf("Memory Requests: ");
  
    /* read requests into array */
    i = 1;
    while(scanf("%d", &mem.memreqs[i++][0]))   
    {
        length++;

        /* if number of requests exceeds array size, expand the array */
        if(length == mem.memreqs[0][0] - 1)
        {   
            mem.memreqs = expandArray(mem.memreqs, 
                                      mem.memreqs[0][0], 
                                      mem.memreqs[0][1], 
                                      mem.memreqs[0][0] + 1, 
                                      mem.memreqs[0][1]);
        }
        //printf("\nYou Entered: %d", mem.memreqs[i-1][0]);
        //printf("\n%d %d %d\n", mem.memreqs[0][0], mem.memreqs[0][1], length);
        if((nl = getchar()) == '\n')
            break;

    }
    
    printf("\nYou entered: ");
    for(i = 1; i < mem.memreqs[0][0]; printf("*%d* ", mem.memreqs[i++][0]));
    printf("\n");
    
}

/* function to expand an array */
int** expandArray(int** arr, int row, int col, int newrow, int newcol)
{
    printf("\nEXPANDING ARRAY: %d %d %d %d\n", row, col, newrow, newcol);
    int i = 0;
    int j = 0;
    int temp[newrow][newcol];

    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
            temp[i][j] = arr[i][j];

    /* update the array size */
    temp[0][0] = newrow;
    temp[0][1] = newcol;
    printf("\n**%d %d**\n", sizeof(temp)/sizeof(temp[0]), sizeof(temp[0]) / sizeof(temp[0][0]));

    return temp;
}
