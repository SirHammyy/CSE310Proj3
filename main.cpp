#include <iostream>
#include "defns.h"

#define INF 99999
using namespace std;


int main() {
    string input;
    getline(cin, input);
    int numNodes = stoi(input.substr(0, input.find(' ')));
    int numEdges = stoi(input.substr(input.find(' '), input.length()));
    edge *graph[numNodes + 1];
    for (int i = 0; i < numNodes; i++)
        graph[i] = nullptr;
    graph[0] = new edge();
    graph[0]->src = numNodes;
    graph[0]->dst = numEdges;
    while (getline(cin, input)) {
        int src = stoi(input.substr(0, input.find(' ')));
        int dst = stoi(input.substr(input.find(' '), input.length()));
        edge *temp = new edge();
        temp->src = src;
        temp->dst = dst;
        temp->next = nullptr;

        if (graph[src] == nullptr) {
            graph[src] = temp;
        } else {
            temp->next = graph[src];
            graph[src] = temp;
        }

        temp = new edge();
        temp->src = dst;
        temp->dst = src;
        temp->next = nullptr;
        if (graph[dst] == nullptr) {
            graph[dst] = temp;
        } else {
            temp->next = graph[dst];
            graph[dst] = temp;
        }
    }

    edge *last = graph[numNodes];
    while (last->next != nullptr && last->next->src < 10000 && last->next->dst < 10000) {
        last = last->next;
    }
    last->next = nullptr;

    //Find odd-degree vertices
    int oddCount;
    int *oddVertices = findOddVertices(graph, numNodes, oddCount);
    printOddVertices(oddVertices, oddCount);

    //Floyd Warshall Algorithm
    int** dist = FloydWarshall(graph, numNodes);
    printOddFloydWarshall(dist, numNodes, oddVertices, oddCount);

    //Greedy Algorithm
    
}
