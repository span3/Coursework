// File:dfsTrace.c
// Author: Steven Pan (span3@ucsc.edu)
// Date: 5/31/12
// Class: CMPS 101
// Assignment: 3

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

int dfs(IntList* adjVertices, int* color, int v,int time, int* start,int* finish,int* parent,int* mark)
{
    mark[v] = 1;
    int w;
    IntList remAdj;
    color[v] = 1;
    time++;
    start[v] = time; 
    remAdj = adjVertices[v];
    while (remAdj != NULL)  
    {
        w = intFirst(remAdj);
        if (color[w] == 0)
        {
            mark[w] = 1;
            parent[w] = v;
            time = dfs(adjVertices, color, w,time,start,finish,parent,mark);
        }
        remAdj = intRest(remAdj);
    }
    time++;
    finish[v] = time;
    color[v] = 2;
    return time;
}

void dfsSweep(IntList* adjVertices, int n,int* start,int* finish,int time,int* parent)
{
    int* mark = calloc(n+1, sizeof(int));
    time = 0;
    int* color = calloc(n+1, sizeof(int));
    int i, j;
    for (i = 1; i <= n; i++)
    {
        color[i] = 0;
    }
    for (i = 1; i <= n; i++)
    {
        if (color[i] == 0)
        {
            parent[i] = -1;
            time = dfs(adjVertices, color, i,time,start,finish,parent,mark);
        }
        j = i;
        if (mark[j] == 1)
            printf("%d:\n", i);
        for (j = 1; j <=n; j++)
        {
            if(mark[j] == 1)
            printf("Vertex:%d, Start:%d, Finish:%d, Parent:%d \n",j,start[j],finish[j], parent[j]);
        }
        for (j = 1; j <=n; j++)
            mark[j] = 0;
    }
}

int main(int argc, char* argv[]) {
    int m, n, i, time;
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

    int* start = calloc(n+1, sizeof(int));
    int* finish = calloc(n+1, sizeof(int));
    int* parent = calloc(n+1, sizeof(int));
    dfsSweep(adjVertices,n,start,finish,time,parent);
    return 0;
}
     
