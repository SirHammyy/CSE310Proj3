#ifndef CSE310PROJ3_GRAPH_H
#define CSE310PROJ3_GRAPH_H

struct edge {
    int src, dst, weight = 1;
    bool virt = false;
    edge* next = nullptr;
};

void printAdjacencyList(edge** graph, int numNodes);

int* findOddVertices(edge **graph, int numNodes, int &oddCount);

void printOddVertices(int* oddVertices, int oddCount);

int** FloydWarshall(edge **graph, int numNodes);

void printOddFloydWarshall(int **dist, int numNodes, const int *oddVertices, int oddCounter);

edge* sortEdgeArray(edge* o, int length);

edge* findMatching(edge* o, int length, int &lengthOfPath);

void printMatching(edge* m, int length);

void insertVirtualEdges(edge* m, edge** graph, int lengthOfPath, int numNodes);

#endif //CSE310PROJ3_GRAPH_H
