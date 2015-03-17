// File:graph02.c
// Author: Steven Pan (span3@ucsc.edu)
// Date: 5/13/12
// Class: CMPS 101
// Assignment: 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intList.h"

typedef char* Cstring;

typedef struct
{
    int from;
    int to;
    double weight;
} Edge;


void initEdges(int n, IntList* adjVertices)
{
    int i;
    for (i = 1; i <= n; i ++)
    {
        adjVertices[i] = NULL;
    }
    return;
}

Edge parseEdge(char line[])
{
    Edge newE;
    int numFields;
    numFields = sscanf(line, "%d %d", &newE.from, &newE.to);
    if (numFields < 2 || numFields > 3)
    {
        printf("Bad edge: %s", line);
        exit(1);
    }

    if (numFields == 2)
    newE.weight = 0.0;
    return newE;
}

int loadEdges(FILE* inbuf, IntList adjVertices[], int n)
{
    int	num;
    Cstring line;
    num = 0;
    char currs[1024];
    IntList curr;
    while (fgets(currs, 1024, inbuf) != NULL)
    {
        Edge e = parseEdge(currs);
        if (e.to > n || e.to < 1)
        {
            printf("Bad edge: %d \n", e.to);
        }
        else
        {
            curr = intCons(e.to, adjVertices[e.from]);
            adjVertices[e.from] = curr;
            num++;
        }
    }

    return num;
}

void printGraph(IntList curr)
{
    printf("[%d] ", intFirst(curr));
    if(intRest(curr))
    printGraph(intRest(curr));
    return;
}

IntList* transposeGraph (IntList* origGraph, int n)
{
    IntList* newGraph;
    int i;
    for (i = 1; i <= n; i++)
    {
        IntList curr = calloc(2, sizeof(IntList));
        curr = origGraph[i];
        printf("%d", intFirst(origGraph[i]));
        while (intRest(curr) != NULL)
        {
            newGraph[intFirst(curr)] = intCons(i,newGraph[intFirst(curr)]);
        }
    }
    return newGraph;
}

int hasCycle(IntList *origGraph, int n)
{
    int* checkEdges = calloc(n+1, sizeof(int));
    int i;
    for (i = 1; i <=n; i++)
    {
        checkEdges[i] = 0;
    }
    for (i = 1; i <=n; i++)
    {
        for (;;)
        {
            int currNum;
            currNum = intFirst(origGraph[i]);
            if (checkEdges[currNum] = 0)
            checkEdges[currNum] = 1;
            if (intRest(origGraph[i]))
            origGraph[i] = intRest(origGraph[i]);
            else
            break;
        }
    }
    for (i = 1; i <=n; i++)
    {
        if (checkEdges[i] = 0)
        return 0;
    }
    return 1;
}
int main(int argc, char* argv[]) {
    int m, n, i;
    FILE* inbuf;
    if (argc == 0)
    {
        printf("Usage: java graph input.data /n");
        return 1;
    }

    if (argv[1] == NULL)
    {
        printf("argv1 is null \n");
        return 123;
    }

    Cstring infile = argv[1];
    inbuf = fopen(argv[1], "r");
    printf("Opened %s for input.\n", infile);
    char line[1024];
    fgets(line, 1024, inbuf);
    sscanf(line, "%d", &n);
    printf("n = %d\n", n);
    IntList* adjVertices = calloc(n+1, sizeof(IntList));
    initEdges(n, adjVertices);
    m = loadEdges(inbuf, adjVertices, n);
    fclose(inbuf);
    printf("m = %d\n", m);
    IntList* copy = calloc(n+1, sizeof(IntList));
    copy = adjVertices;
    for (i = 1; i <= n; i++)
    {
        printf("%d \t",i);
        if(copy[i])
        printGraph(copy[i]);
        printf("\n");
    }
    int cycle = hasCycle(adjVertices, n);
    if (cycle = 1)
    printf("This graph is a cycle. \n Example: %d, %i", adjVertices[1], intFirst(adjVertices[1]));
    else
    printf("This graph is not a cycle. \n");
    IntList* transGraph = calloc(n+1, sizeof(IntList));
    transGraph = transposeGraph(adjVertices, n);
    for (i = 1; i <=n; i++)
    {
        printf("%d \t",i);
        if(transGraph[i])
        printGraph(transGraph[i]);
        printf("\n");
    }
    return 0;
}
     
