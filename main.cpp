#include <iostream>

using namespace std;

struct edge {
    int src, dst;
    edge* next;
};

int main() {
    string input;
    getline(cin, input);
    int numNodes = stoi(input.substr(0, input.find(' ')));
    int numEdges = stoi(input.substr(input.find(' '), input.length()));
    edge* graph[numNodes];
    for (int i = 0; i < numNodes; i++)
        graph[i] = nullptr;
    graph[0] = new edge();
    graph[0]->src = numNodes;
    graph[0]->dst = numEdges;
    while(getline(cin, input)) {
        int src = stoi(input.substr(0, input.find(' ')));
        int dst = stoi(input.substr(input.find(' '), input.length()));
        edge* temp = new edge();
        temp->src = src;
        temp->dst = dst;
        temp->next = nullptr;

        if (graph[src] == nullptr) {
            graph[src] = temp;
        }
        else {
            temp->next = graph[src];
            graph[src] = temp;
        }
    }

    for (int i = 0; i < numNodes; i++) {
        edge* temp = graph[i];
        while (temp != nullptr) {
            temp = temp->next;
        }
    }

    //Find odd-degree vertices
    int oddVerticesCount = 0;
    for (int i = 1; i <= numNodes; i++) {
        int currentNumEdges = 0;
        for (int j = 1; j < numNodes; j++) {
            edge *temp = graph[j];
            while (temp != nullptr) {
                if (temp->src == i || temp->dst == i)
                    currentNumEdges++;
                temp = temp->next;
            }
        }

        if (currentNumEdges % 2 != 0) {
            oddVerticesCount++;
        }
    }

    int oddVertices[oddVerticesCount], counter = 0;
    for (int i = 1; i <= numNodes; i++) {
        int currentNumEdges = 0;
        for (int j = 1; j < numNodes; j++) {
            edge *temp = graph[j];
            while (temp != nullptr) {
                if (temp->src == i || temp->dst == i)
                    currentNumEdges++;
                temp = temp->next;
            }
        }

        if (currentNumEdges % 2 != 0) {
            oddVertices[counter] = i;
            counter++;
        }
    }

    cout << "The odd-degree vertices in G: O = { ";
     for (int i = 0; i < counter; i++)
        cout << oddVertices[i] << " ";
    cout << "}" << endl;
}
