#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void main(void)
{
    /* initialize variables */
    int i = 0;
    int length = 0;
    /* temp buffer to store the requests of unknown length */
    int* read = (int*)malloc(sizeof(int) * 100);
    /* while loop control */
    char nl;

    printf("Enter Memory Requests (up to 100): ");
  
    /* read requests into array */
    while(scanf("%d", &read[length++]))   
        if((nl = getchar()) == '\n')
            break;
    
    /* struct for each mempoy request */
    typedef struct memassign
    {
        int size;
        int startloc;
        bool inmem;   
    } memassign;
    
    /* struct for overall memory */
    struct memory
    {
        int partsize;
        int numparts;
        memassign memreq[length];
    } mem;
    
    mem.partsize = 512;
    mem.numparts = 10;
    
    /* initialize struct values */
    for(i = 0; i < length; i++)
    {
        mem.memreq[i].size = read[i];
        mem.memreq[i].startloc = (mem.partsize * i);
        mem.memreq[i].inmem = false;
    }

    free(read);
}
