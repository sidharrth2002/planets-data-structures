#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <map> 

// #include "../Planet.h"
// #include "../Edge.h"
using namespace std;
//REUSE FOR OTHER ALGOS
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
};

//REUSE FOR OTHER ALGOS
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
    // cout << start->name << " " << this->distance << " " << end->name << endl;
};

//REUSE FOR OTHER ALGOS
vector<Planet> planets;
vector<Edge> edges;

//REUSE FOR OTHER ALGOS
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

Edge findEdge(int start, int end) {
    for(int i = 0; i < edges.size(); i++) {
        Edge edge = edges[i];
        if((edge.start->id == start && edge.end->id == end) 
        ||
        (edge.start->id == end && edge.end->id == start)) {
            return edge;
        }
    }
}

//dijkstra starts from here
//basically infinity lah
const int THEORETICAL_MAX = 1000000;
const int MAX_ENTRIES = 10;
int distanceMatrix[MAX_ENTRIES][MAX_ENTRIES];
int distances[MAX_ENTRIES];
bool nodesVisited[MAX_ENTRIES] = {0};
int numberOfNodes;
int passesThrough[MAX_ENTRIES];
vector<Edge> usedEdges;
char m[7][7];

//PART OF IT CAN REUSE FOR OTHER ALGOS
void initializeMatrices() {    
    //==============================
    //CAN REUSE FOR OTHER ALGORITHMS FROM HERE
    
    //initialize with max values
    for(int i = 0; i < MAX_ENTRIES; i++) {
        for(int j = 0; j < MAX_ENTRIES; j++) {
            distanceMatrix[i][j] = THEORETICAL_MAX;
        }
    }

    //set edges that are actually connected
    for(int i = 0; i < edges.size(); i++) {
        distanceMatrix[edges[i].start->id][edges[i].end->id] = edges[i].distance;
    }

    //to print the adjacency matrix (can make it look better)
    //use setw()
    for(int k = 0; k < MAX_ENTRIES; k++) {
        cout << (char)(k+65) << " ";
    }
    cout << endl;

    for(int i = 0; i < MAX_ENTRIES; i++) {
        cout << (char)(i + 65) << " ";
        for(int j = 0; j < MAX_ENTRIES; j++) {
            if(distanceMatrix[i][j] == THEORETICAL_MAX) {
                cout << "-" << " ";
            } else {
                cout << distanceMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    //TILL HERE
    //==============================


    numberOfNodes = planets.size();
    //fill all distances with max
    fill(distances , distances+numberOfNodes , THEORETICAL_MAX); 

    //planet A's distance is automatically 0
    distances[0] = 0;
    //planet A passes through no one
    //can track when we reached the start node later
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

bool containsEdge(Edge edge) {
    int start = edge.start->id;
    int end = edge.end->id;
    for (int i = 0; i < usedEdges.size(); ++i) {
        // if(&usedEdges[i] == &edge) {
        //     return true;
        // }
        if((usedEdges[i].start->id == start && usedEdges[i].end->id == end) 
            || 
            (usedEdges[i].start->id == end && usedEdges[i].end->id == start)
        ) {
            return true;
        }
    }
    return false;
}

void connect(char m[7][7], int a, int b)
{
    // cout << "I am reached" << endl;
    // cout << "I am connecting " << a << " and " << b << endl;
    switch (a) {
    case 1:     // A
        if (b == 4)     // connect to D
        {
            m[0][0] = '+';
            m[0][1] = '-';
            m[0][2] = '-';
            m[1][0] = '|';
        }
        if (b == 6)     // connect to F
        {
            m[0][6] = '+';
            m[0][5] = '-';
            m[1][6] = '|';
        }
        if (b == 10)     // connect to J
        {
            m[0][2] = '+';
            m[1][2] = '|';
        }
        if (b == 8)      // connect to H
        {
            m[0][4] = '+';
            m[1][4] = '|';
        }
        break;
    case 2:     // B
        if (b == 4)     // connect to D
        {
            m[3][0] = '|';
        }
        if (b == 5)     // connect to E
        {
            m[6][0] = '+';
            m[6][1] = '-';
            m[6][2] = '-';
            m[5][0] = '|';
        }
        if (b == 7)     // connect to G
        {
            m[4][1] = '-';
        }
        break;
    case 3:     // C
        if (b == 6)     // connect to F
        {
            m[3][6] = '|';
        }
        if (b == 5)     // connect to E
        {
            m[6][6] = '+';
            m[6][5] = '-';
            m[6][4] = '-';
            m[5][6] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[4][5] = '-';
        }
        break;
    case 4:     // D
        if (b == 10)     // connect to J
        {
            m[2][1] = '-';
        }
        break;
    case 5:     // E
        if (b == 7)     // connect to G
        {
            m[6][2] = '+';
            m[5][2] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[6][4] = '+';
            m[5][4] = '|';
        }
        break;
    case 6:     //
        if (b == 8)     // connect to H
        {
            m[2][5] = '-';
        }
        break;
    case 7:     // G
        if (b == 10)     // connect to J
        {
            m[3][2] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[4][3] = '-';
        }
        break;
    case 8:     // H
        if (b == 10)     // connect to J
        {
            m[2][3] = '-';
        }
        if (b == 9)     // connect to I
        {
            m[3][4] = '|';
        }
        break;
    }
}


void initmap(char m[7][7])
{
    for (int i=0; i<7; i++)
        for (int j=0; j<7; j++)
           m[i][j] = ' ';
}

void setPlanetsGraph(char m[7][7])
{
    m[0][3] = 'A';
    m[4][0] = 'B';
    m[4][6] = 'C';
    m[2][0] = 'D';
    m[6][3] = 'E';
    m[2][6] = 'F';
    m[4][2] = 'G';
    m[2][4] = 'H';
    m[4][4] = 'I';
    m[2][2] = 'J';
}


void setEdges(char m[7][7]) {
    for(int i = 0; i < usedEdges.size(); ++i) {
        // cout << usedEdges[i].start->id + 1 << endl;
        connect(m, usedEdges[i].start->id + 1, usedEdges[i].end->id + 1);
    }
    cout << usedEdges.size() << endl;
}

void display(char m[7][7])
{
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<7; j++)
           cout << m[i][j];
        cout << endl;
    }
}

void displayShortestDistances() {
    cout << setw(30) << left << "Planet" << setw(30) << left << "Shortest Distance from A" << setw(30) << left << "Passes Through" << endl;
    for(int i = 0; i < numberOfNodes; i++) {
        cout << setw(30) << left << (char)(i + 65) << setw(30) << left << distances[i];
        cout << (char)(i + 65) << " - ";
        int passingThrough = passesThrough[i];
        //till it reaches planet A
        if(passingThrough < i) {
            connect(m, passingThrough + 1, i + 1);
        } else {
            connect(m, i + 1, passingThrough + 1);
        }
        while(passingThrough != -1) {
            // //to next node in path
            cout << (char)(passingThrough + 65) << " - ";
            int passedThrough = passingThrough;
            passingThrough = passesThrough[passingThrough];

            if(passingThrough != -1) {
                // Edge edge = findEdge(passedThrough, passingThrough);
                // cout << "yolo" << passedThrough << " " << passingThrough << endl;
                if(passedThrough + 1 < passingThrough + 1) {
                    connect(m, passedThrough + 1, passingThrough + 1); 
                    cout << passedThrough + 1 << " " << passingThrough + 1<< endl;
                } else {
                    connect(m, passingThrough + 1, passedThrough + 1);
                    cout << passingThrough + 1 << " " << passedThrough + 1 << endl << endl;
                }
                
                // usedEdges.push_back(edge);
                // if (!containsEdge(edge)) {
                //     usedEdges.push_back(edge);
                // }                
            }
        }
        cout << endl;
    }
    display(m);
}

void displayGraph() {
    // cout << "        A     " << endl;
    // cout << "  ⁄    / \\   ⧹ " << endl;
    // cout << " D    J   H   F" << endl;
    // cout << " |    |   |   |" << endl;
    // cout << " B    G   I   C" << endl;
    // cout << "  ⧹    \\  /  ⁄" << endl;
    // cout << "        E     " << endl;
}

void dijkstra() {
    initmap(m);
    setPlanetsGraph(m);
    // setEdges(m);

    for(int i = 0; i < numberOfNodes - 1; i++) {
        int nearestIndex = getNearestAdjacent();
        nodesVisited[nearestIndex] = true;
        for(int adjacent = 0; adjacent < numberOfNodes; adjacent++) {
            if (
                (!nodesVisited[adjacent])
                &&
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
    dijkstra();
    displayShortestDistances();
    // displayGraph();
}

#endif