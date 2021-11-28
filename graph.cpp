#include <iostream>
#include "graph.h"

#define INF 99999
using namespace std;

void printAdjacencyList(edge** graph, int numNodes) {
    for (int i = 1; i <= numNodes; i++) {
        edge* ptemp = graph[i];
        while (ptemp != nullptr) {
            cout << ptemp->src << " " << ptemp->dst << " " << ptemp->weight << " -> ";
            ptemp = ptemp->next;
        }
        cout << endl;
    }
}

int* findOddVertices(edge **graph, int numNodes, int &oddCount) {
    int oddVerticesCount = 0;
    for (int i = 1; i <= numNodes; i++) {
        int currentNumEdges = 0;
        for (int j = 1; j <= numNodes; j++) {
            edge *temp = graph[j];
            while (temp != nullptr) {
                if (temp->src == i)
                    currentNumEdges++;
                temp = temp->next;
            }
        }

        if (currentNumEdges % 2 != 0) {
            oddVerticesCount++;
        }
    }

    int* oddVertices = new int[oddVerticesCount], oddCounter = 0;
    for (int i = 1; i <= numNodes; i++) {
        int currentNumEdges = 0;
        for (int j = 1; j <= numNodes; j++) {
            edge *temp = graph[j];
            while (temp != nullptr) {
                if (temp->src == i)
                    currentNumEdges++;
                temp = temp->next;
            }
        }

        if (currentNumEdges % 2 != 0) {
            oddVertices[*&oddCounter] = i;
            oddCounter++;
        }
    }

    oddCount = oddCounter;
    return oddVertices;
}

void printOddVertices(int* oddVertices, int oddCount) {
    cout << "The odd-degree vertices in G: O = { ";
    for (int i = 0; i < oddCount; i++)
        cout << oddVertices[i] << " ";
    cout << "}" << endl << endl;
}

int** FloydWarshall(edge **graph, int numNodes) {
    int matrix[numNodes + 1][numNodes + 1];
    for (int i = 1; i <= numNodes; i++) {
        for (int j = 1; j <= numNodes; j++) {
            edge* temp = graph[i];
            while (temp->next != nullptr && temp->dst != j) {
                temp = temp->next;
            }
            if (temp->dst == j) {
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = INF;
            }
        }
    }

    int** dist;
    dist = new int*[numNodes + 1];
    for (int i = 1; i <= numNodes; i++) {
        dist[i] = new int[numNodes + 1];
        for (int j = 1; j <= numNodes; j++) {
            dist[i][j] = matrix[i][j];
            if (i == j) {
                dist[i][j] = 0;
            }
        }
    }

    for (int k = 1; k <= numNodes; k++) {
        for (int i = 1; i <= numNodes; i++) {
            for (int j = 1; j <= numNodes; j++) {
                if ((dist[i][k] + dist[k][j]) < dist[i][j] && (dist[k][j] != INF && dist[i][k] != INF)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= numNodes; i++) {
        for (int j = 1; j <= numNodes; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }
        }
    }
    return dist;
}

void printOddFloydWarshall(int **dist, int numNodes, const int *oddVertices, int oddCounter) {
    cout << "Results of Floyd-Warshall on O:" << endl;
    cout.width(4);
    cout << "    ";
    cout.width(4);
    cout << " |  ";
    for (int i = 1; i <= numNodes; i++) {
        for (int j = 0; j < oddCounter; j++) {
            if (oddVertices[j] == i) {
                cout.width(3);
                cout << right << i;
                cout << " ";
            }
        }
    }
    cout << endl;
    cout.width(4);
    cout << "--- ";
    cout.width(4);
    cout << "-+- ";
    for (int i = 1; i <= numNodes; i++) {
        for (int j = 0; j < oddCounter; j++) {
            if (oddVertices[j] == i) {
                cout.width(4);
                cout << left << "--- ";
            }
        }
    }
    cout << endl;
    for (int i = 1; i <= numNodes; i++) {
        for (int k = 0; k < oddCounter; k++) {
            if (oddVertices[k] == i) {
                cout.width(3);
                cout << right << i;
                cout.width(4);
                cout << right << " | ";
                cout << " ";
                for (int j = 1; j <= numNodes; j++) {
                    for (int u = 0; u < oddCounter; u++) {
                        if (oddVertices[u] == j) {
                            cout.width(3);
                            cout << right << dist[i][j];
                            cout << " ";
                        }
                    }
                }
                cout << endl;
            }
        }
    }
    cout << endl;
}

edge* sortEdgeArray(edge* o, int length) {
    int j;
    for (int i = 1; i < length; i++) {
        j = i;
        while (j >= 0 && o[j - 1].weight > o[j].weight) {
            swap(o[j - 1], o[j]);
            j = j - 1;
        }
    }

    return o;
}

edge* findMatching(edge* o, int length, int &lengthOfPath) {
    lengthOfPath = 0;
    bool flag = false;
    edge* m = new edge[length];
    m[0] = o[0];
    lengthOfPath++;

    for (int i = 1; i < length; i++) {
        for (int j = 0; j < lengthOfPath; j++) {
            if (o[i].src == m[j].src || o[i].src == m[j].dst ||
                o[i].dst == m[j].src || o[i].dst == m[j].dst) {
                    flag = true;
            }
        }

        if (!flag) {
            m[lengthOfPath] = o[i];
            lengthOfPath++;
        }

        flag = false;
    }

    return m;
}

void printMatching(edge* m, int length) {
    cout << "The greedy perfect matching in O: M = { ";
    for (int i = 0; i < length; i++) {
        cout << "(" << m[i].src << "," << m[i].dst << ") ";
    }
    cout << "}" << endl << endl;
}

void insertVirtualEdges(edge* m, edge** graph, int lengthOfPath, int numNodes) {
    for (int i = 0; i < lengthOfPath; i++) {
        edge* temp = new edge();
        *temp = m[i];
        temp->virt = true;
        temp->next = graph[m[i].src];
        graph[m[i].src] = temp;

        temp = new edge();
        *temp = m[i];
        temp->virt = true;
        temp->src = m[i].dst;
        temp->dst = m[i].src;
        temp->next = graph[m[i].dst];
        graph[m[i].dst] = temp;
    }
}
