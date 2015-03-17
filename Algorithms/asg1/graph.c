//File:graph.c
//Author: Steven Pan
//Date: 4/15/2012
//Class: CMPS 101
//Assignment: 1  

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

int loadEdges(FILE* inbuf, IntList adjVertices[])
{
    int	num;
    Cstring line;
    num = 0;
    char currs[1024];
    IntList curr;
    while (fgets(currs, 1024, inbuf) != NULL)
    {
        Edge e = parseEdge(currs);
        curr = intCons(e.to, adjVertices[e.from]);
        adjVertices[e.from] = curr;
        num++;
    }

    return num;
}

void printGraph(IntList curr){
    printf("[%d] ", intFirst(curr));
    if(intRest(curr))
    printGraph(intRest(curr));
    return;
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
    printf("Input: %s\n", infile);
    char line[1024];
    fgets(line, 1024, inbuf);
    sscanf(line, "%d", &n);
    printf("n = %d\n", n);
    IntList* adjVertices = calloc(n+1, sizeof(IntList));
    initEdges(n, adjVertices);
    m = loadEdges(inbuf, adjVertices);
    fclose(inbuf);
    printf("m = %d\n", m);

    for (i = 1; i <= n; i++)
    {
        printf("%d   ",i);
        if(adjVertices[i])
        printGraph(adjVertices[i]);
        printf("\n");
    }
    return 0;
}
