#include <iostream>
using namespace std;

const int THEORETICAL_MAX = 1000000;
const int MAX_ENTRIES = 100;
int distanceMatrix[MAX_ENTRIES][MAX_ENTRIES];
int distances[MAX_ENTRIES];
bool nodesVisited[MAX_ENTRIES] = {0};
int numberOfNodes;
int passesThrough[MAX_ENTRIES];

void initializeMatrices() {
    for(int i = 0; i < MAX_ENTRIES; i++) {
        distances[i] = THEORETICAL_MAX;
    }
    //planet A's distance is automatically 0
    distances[0] = 0;
    //planet A passes through no one
    passesThrough[0] = -1;
}

int getNearestAdjacent() {
    int minimum = THEORETICAL_MAX;
    int minimumNodeIndex = 0;
    for (int i = 0; i < numberOfNodes; i++) {
        if(!nodesVisited[i] && distances[i] < minimum) {
            minimum = distances[i];
            minimumNodeIndex = i;
        }
    }
}

void displayShortestDistances() {
    cout << "Planet" << "\t" << "Shortest Distance from A" << endl;
    for(int i = 0; i < numberOfNodes; i++) {
        cout << i << "\t" << distances[i] << endl;
    }
}

void dijkstra() {
    for(int i = 0; i < numberOfNodes; i++) {
        int nearestIndex = getNearestAdjacent();
        nodesVisited[nearestIndex] = true;
        for(int adjacent = 0; adjacent < numberOfNodes; adjacent++) {
            if(
                (distanceMatrix[nearestIndex][adjacent] != THEORETICAL_MAX)
                &&
                (distances[adjacent] > distances[nearestIndex] + distanceMatrix[nearestIndex][adjacent]) 
            ) {
                distances[adjacent] = distances[nearestIndex] + distanceMatrix[nearestIndex][adjacent];
                passesThrough[adjacent] = nearestIndex;
            }
        }
    }
    displayShortestDistances();
}

void loadFromFile() {

}

int main() {
    loadFromFile();
    cout << "at least runs" << endl;
}