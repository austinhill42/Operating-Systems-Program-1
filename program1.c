/********************************* program1.c *********************************
* Programmer: Austin Hill
* 
* Course: CSCI 4354.01
* 
* Date: February 16, 2018
* 
* Assignment: Program 1
* 
* Environment: Arch Linux using GCC
* 
* Files Included: program1.c
* 
* Purpose: To read memory requests from user input and assign them to fixed 
*          sized partitions
* 
* Input: Up to 100 memory assignments
* 
* Preconditions: Only integers are accepted, and the last character entered
*                cannot be a whitespace character
* 
* Output: The memory assignments, total fragmentation, requests in the waitlist
*         
* Algorithm:
*   Read input from user
*   Initialize the memory and partitions structs
*   For each memory request
*       Reject the request if it's too big
*       For each partition
*           If the request will fit in the partition
*               if the partition is free
*                   add the request to the partition
*       if the request went unassigned
*           add it to the waitlist
*   For each request in a partition
*       print the request and partition information
*   For each unassigned request
*       print the memory requested
*
*******************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* struct for each partition */
typedef struct partition
{
    int size;
    int startloc;
    int endloc;
    int firstused;
    int lastused;
    int infrag;
    bool free;   
} part;

/* struct for a linked list */
typedef struct list
{
    struct list* next;
    int value;
} list;

void add(struct list* l, int val);
void del(struct list* l);
int length(list* l);

void main(void)
{
    /* initialize variables */
    int i = 0, j = 0, reqlen = 0, exfrag = 0, infrag = 0;
    /* temp buffer to store the requests of unknown reqlen */
    int* read = (int*)malloc(sizeof(int) * 100);
    /* while loop control */
    char nl;
    /* wait list for memory requests */
    list* waitlist = (list*) malloc(sizeof(list));
    /* unassigned partitions */
    list* unassigned = (list*) malloc(sizeof(list));
    /* list control */
    list* current;

    printf("Enter memory requests (up to 100): ");
  
    /* read requests into array */
    while (scanf("%d", &read[reqlen++]))   
        if ((nl = getchar()) == '\n')
            break;
    
    /* struct for overall memory */
    struct memory
    {
        int partsize;
        int numparts;
        int memreq[reqlen];
    } mem;
    
    /* initialize memory */
    mem.partsize = 512;
    mem.numparts = 10;
    for (i = 0; i < reqlen; mem.memreq[i++] = read[i]);

    free(read);

    /* initialize the partitions */
    part parts[mem.numparts];
    parts[0].size = mem.partsize;
    parts[0].startloc = 0;
    parts[0].endloc = parts[0].size - 1;
    parts[0].firstused = -1;
    parts[0].lastused = -1;
    parts[0].infrag = parts[0].size;
    parts[0].free = true;

    for (i = 1; i < mem.numparts; i++)
    {
        parts[i].size = mem.partsize;
        parts[i].startloc = parts[i-1].endloc + 1;
        parts[i].endloc = parts[i].startloc + parts[i].size - 1;
        parts[i].firstused = -1;
        parts[i].lastused = -1;
        parts[i].infrag = parts[i].size;
        parts[i].free = true;
    }

    /* assign memory requests */
    for (i = 0, current = waitlist; i < reqlen; i++)
    {
        bool assigned = false;
        bool rejected = false;

        if (mem.memreq[i] > mem.partsize)
        {
            printf("\nThe job requesting %d bytes of memory is too large "
                    "and has been rejected.", mem.memreq[i]);

            rejected = true;
        }
        else 
        {
            for (j = 0; j < mem.numparts; j++)
            {
                if (mem.memreq[i] <= parts[j].size)
                {
                    if (parts[j].free)
                    {   
                        parts[j].firstused = 0;
                        parts[j].lastused = mem.memreq[i] - 1;
                        parts[j].infrag = parts[j].size - parts[j].lastused;
                        parts[j].free = false;
                        assigned = true;
                        break;
                    }
                }
            }
        }

        if (!assigned && !rejected)
        {
            if (current== NULL)
            {
                current = (list*) malloc(sizeof(list));
                current->next = NULL;
                current->value = mem.memreq[i];
            }
            else
                add(current, mem.memreq[i]);
        }
    }

    /* print memory assignments */
    printf("\n\nMemory Assignments:\n");
    for (i = 0, current = unassigned; i < mem.numparts; i++)
    {
        if (!parts[i].free)
        {
            printf("Memory request %d assigned to partition %d\n\t" 
                    "First address: %d\n\tLast address: %d\n\t" 
                    "Internal fragmentation: %d\n", parts[i].lastused + 1, i,
                    parts[i].firstused, parts[i].lastused, parts[i].infrag);
            
            infrag += parts[i].infrag;
        }
        else
        {
            exfrag += parts[i].size;

            if (current == NULL)
            {
                current = (list*) malloc(sizeof(list));
                current->next = (list*) malloc(sizeof(list));
                current->value = parts[i].startloc;
            }
            else
            {
                add(current, parts[i].startloc);
            }
        }
    }

    /* print unassigned partitions */
    if (unassigned == NULL)
        printf("\nThere are no unassigned partitions.\n");
    else
    {
        current = unassigned;
        printf("\n%d unassigned partition(s) at location(s):", length(unassigned));
        
        for (i = 0; i < length(unassigned); i++) 
            printf("\n\t%d", (current = current->next)->value);
    }

    /* print additional information */
    printf("\n\nTotal internal fragmentation: %d\nTotal external fragmentation: %d\n"
           "Total fragmentation: %d\n", infrag, exfrag, infrag + exfrag);
    if (waitlist == NULL)
        printf("\nThere are no requests in the waitlist\n");
    else
    {
        current = waitlist;
        printf("\n%d requests in the waitlist: ", length(waitlist));

        for (i = 0; i < length(waitlist); i++)
            printf("\n\t%d", (current = current->next)->value);
    }
}

void add(struct list* l, int val)
{
    list* new = (list*) malloc(sizeof(list));

    new->next = l->next;
    new->value = val;
    l->next = new;
    l = l->next;
}

int length(struct list* l)
{
    list* current = l;
    
    if (current == NULL || (current =current->next) == NULL)
        return 0;
    
    int i = 1;

    while (current != NULL)
    {
        current = current->next;
        i++;
    }

    return i - 1;
}
