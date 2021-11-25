#ifndef CSE310PROJ3_DEFNS_H
#define CSE310PROJ3_DEFNS_H

struct edge {
    int src, dst;
    edge* next;
};

int* findOddVertices(edge **graph, int numNodes, int &oddCount);

void printOddVertices(int* oddVertices, int oddCount);

int** FloydWarshall(edge **graph, int numNodes);

void printOddFloydWarshall(int **dist, int numNodes, const int *oddVertices, int oddCounter);

#endif //CSE310PROJ3_DEFNS_H
