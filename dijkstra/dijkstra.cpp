#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

class Planet {
    public:
        string name;
        int id;
        int x;
        int y;
        int z;
        int weight;
        int profit;
        Planet(int id, string name, int x, int y, int z, int weight, int profit);
};

Planet::Planet(int id, string name, int x, int y, int z, int weight, int profit) {
    this->id = id;
    this->name = name;
    this->x = x;
    this->y = y;
    this->z = z;
    this->weight = weight;
    this->profit = profit;
}

class Edge {
    public:
        Planet* start;
        Planet* end;
        int distance;
        Edge(Planet* start, Planet* end);
};

Edge::Edge(Planet* start, Planet* end) {
    this->start = start;
    this->end = end;
    //calculate distance between planets
    this->distance = sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2) + pow(end->z - start->z, 2));
}

vector<Planet> planets;
vector<Edge> edges;

void loadFromFile() {
    ifstream input;
    input.open("../A2planets.txt");

    string name;
    int x, y, z, weight, profit;

    int i = 0;
    //create planets
    while(input >> name >> x >> y >> z >> weight >> profit) {
        Planet planet(i++, name, x, y, z, weight, profit);
        planets.push_back(planet);
    }
   input.close();

    //assuming planet A is in the first index, B second and so on
    //create the edges based on the map
    input.open("../routes.txt");
    char startPlanet, endPlanet;
    int start, end;
    while(input >> startPlanet >> endPlanet) {
        //convert planet char to integer
        start = (int)startPlanet - 65;
        end = (int)endPlanet - 65;
        Edge edge(&planets[start], &planets[end]);
        edges.push_back(edge);
    }
    input.close();
}

//dijkstra starts from here
const int THEORETICAL_MAX = 1000000;
const int MAX_ENTRIES = 100;
int distanceMatrix[MAX_ENTRIES][MAX_ENTRIES];
int distances[MAX_ENTRIES];
bool nodesVisited[MAX_ENTRIES] = {0};
int numberOfNodes;
int passesThrough[MAX_ENTRIES];

void initializeMatrices() {
    for(int i = 0; i < edges.size(); i++) {
        distanceMatrix[edges[i].start->id][edges[i].end->id] = edges[i].distance;
    }

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
    return minimumNodeIndex;
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
                //there is a connection between the 2
                (distanceMatrix[nearestIndex][adjacent] != THEORETICAL_MAX)
                &&
                //if going through this vertice would help reach destination faster
                (distances[nearestIndex] + distanceMatrix[nearestIndex][adjacent] < distances[adjacent]) 
            ) {
                //this is now the new distance
                distances[adjacent] = distances[nearestIndex] + distanceMatrix[nearestIndex][adjacent];
                //to get to this node have to pass through this index
                //can trace path later
                passesThrough[adjacent] = nearestIndex;
            }
        }
    }
}

int main() {
    loadFromFile();
    initializeMatrices();
}