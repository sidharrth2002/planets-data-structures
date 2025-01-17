//Sidharrth Nagappan
//1181102313
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <map> 
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
        double value;
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
    if (weight != 0) {
        this->value = profit/weight;
    }
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
    this->distance = round(sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2) + pow(end->z - start->z, 2)));
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

//dijkstra starts from here
//basically infinity lah
const int THEORETICAL_MAX = 1000000;
const int MAX_ENTRIES = 10;
int distanceMatrix[MAX_ENTRIES][MAX_ENTRIES];
int distances[MAX_ENTRIES];
bool nodesVisited[MAX_ENTRIES] = {0};
int numberOfNodes;
int passesThrough[MAX_ENTRIES];
char finalGraph[11][11];

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
        distanceMatrix[edges[i].end->id][edges[i].start->id] = edges[i].distance;
        distanceMatrix[edges[i].start->id][edges[i].start->id] = 0;
        distanceMatrix[edges[i].end->id][edges[i].end->id] = 0;
    }
    //to print the adjacency matrix (can make it look better)
    cout << "ADJACENCY MATRIX: " << endl;
    cout << "=================================================================" << endl;
    for(int k = 0; k < MAX_ENTRIES; k++) {
        if(k == 0) {
            cout << setw(8) << (char)(k+65) << " ";
        } else {
            cout << setw(4) << (char)(k+65) << " ";
        }
    }
    cout << endl;
    for(int i = 0; i < MAX_ENTRIES; i++) {
        cout << setw(4) << (char)(i + 65) << " ";
        for(int j = 0; j < MAX_ENTRIES; j++) {
            if(distanceMatrix[i][j] == THEORETICAL_MAX) {
                cout << setw(4) << "-" << " ";
            } else {
                cout << setw(4) << distanceMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl << "=================================================================" << endl;
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

//larger scale
void connect(int a, int b) {
    switch (a) {
    case 1:     // A
        if (b == 4)     // connect to D
        {
            finalGraph[0][0] = '+';
            finalGraph[0][1] = '-';
            finalGraph[0][2] = '-';
            finalGraph[0][3] = '-';
            finalGraph[0][4] = '-';
            finalGraph[1][0] = '|';
            finalGraph[2][0] = '|';
        }
        if (b == 6)     // connect to F
        {
            finalGraph[0][6] = '-';
            finalGraph[0][7] = '-';
            finalGraph[0][8] = '-'; 
            finalGraph[0][9] = '-';       
            finalGraph[0][10] = '+';
            finalGraph[1][10] = '|';
            finalGraph[2][10] = '|';
        }
        if (b == 10)     // connect to J
        {
            finalGraph[0][4] = '-';
            finalGraph[0][3] = '+';
            finalGraph[1][3] = '|';
            finalGraph[2][3] = '|';
        }
        if (b == 8)      // connect to H
        {
            finalGraph[0][6] = '-';
            finalGraph[0][7] = '+';
            finalGraph[1][7] = '|';
            finalGraph[2][7] = '|';
        }
        break;
    case 2:     // B
        if (b == 4)     // connect to D
        {
            finalGraph[6][0] = '|';
            finalGraph[5][0] = '|';
            finalGraph[4][0] = '|';
        }
        if (b == 5)     // connect to E
        {
            finalGraph[8][0] = '|';
            finalGraph[9][0] = '|';
            finalGraph[10][0] = '+';
            finalGraph[10][1] = '-';
            finalGraph[10][2] = '-';
            finalGraph[10][3] = '-';
            finalGraph[10][4] = '-';
        }
        if (b == 7)     // connect to G
        {
            finalGraph[7][1] = '-';
            finalGraph[7][2] = '-';
        }
        break;
    case 3:     // C
        if (b == 6)     // connect to F
        {
            finalGraph[6][10] = '|';
            finalGraph[5][10] = '|';
            finalGraph[4][10] = '|';
        }
        if (b == 5)     // connect to E
        {
            finalGraph[8][10] = '|';
            finalGraph[9][10] = '|';
            finalGraph[10][10] = '+';
            finalGraph[10][9] = '-';
            finalGraph[10][8] = '-';
            finalGraph[10][7] = '-';
            finalGraph[10][6] = '-';
        }
        if (b == 9)     // connect to I
        {
            finalGraph[7][9] = '-';
            finalGraph[7][8] = '-';
        }
        break;
    case 4:     // D
        if (b == 10)     // connect to J
        {
            finalGraph[3][1] = '-';
            finalGraph[3][2] = '-';
        }
        break;
    case 5:     // E
        if (b == 7)     // connect to G
        {
            finalGraph[10][4] = '-';
            finalGraph[10][3] = '+';
            finalGraph[9][3] = '|';
            finalGraph[8][3] = '|';
        }
        if (b == 9)     // connect to I
        {
            finalGraph[10][6] = '-';
            finalGraph[10][7] = '+';
            finalGraph[9][7] = '|';
            finalGraph[8][7] = '|';
        }
        break;
    case 6:     // F
        if (b == 8)     // connect to H
        {
            finalGraph[3][9] = '-';
            finalGraph[3][8] = '-';
        }
        break;
    case 7:     // G
        if (b == 10)     // connect to J
        {
            finalGraph[6][3] = '|';
            finalGraph[5][3] = '|';
            finalGraph[4][3] = '|';
        }
        if (b == 9)     // connect to I
        {
            finalGraph[7][4] = '-';
            finalGraph[7][5] = '-';
            finalGraph[7][6] = '-';
        }
        break;
    case 8:     // H
        if (b == 10)     // connect to J
        {
            finalGraph[3][6] = '-';
            finalGraph[3][5] = '-';
            finalGraph[3][4] = '-';
        }
        if (b == 9)     // connect to I
        {
            finalGraph[4][7] = '|';
            finalGraph[5][7] = '|';
            finalGraph[6][7] = '|';
        }
        break;
    }
}


void initmap() {
    for (int i=0; i<11; i++)
        for (int j=0; j<11; j++)
           finalGraph[i][j] = ' ';
}

void setPlanetsGraph() {
    finalGraph[0][5] = 'A';
    finalGraph[7][0] = 'B';
    finalGraph[7][10] = 'C';
    finalGraph[3][0] = 'D';
    finalGraph[10][5] = 'E';
    finalGraph[3][10] = 'F';
    finalGraph[7][3] = 'G';
    finalGraph[3][7] = 'H';
    finalGraph[7][7] = 'I';
    finalGraph[3][3] = 'J';
}

void displayGraph() {
    cout << endl;
    cout << "FINAL GRAPH: " << endl;
    for (int i=0; i<11; i++)
    {
        cout << "  ";
        for (int j=0; j<11; j++)
           cout << finalGraph[i][j] << " ";
        cout << endl;
    }
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

void dijkstra() {
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

void displayShortestDistances() {
    cout << setw(30) << left << "Planet" << setw(30) << left << "Shortest Distance from A" << setw(30) << left << "Passes Through" << endl;
    for(int i = 0; i < numberOfNodes; i++) {
        cout << setw(30) << left << (char)(i + 65) << setw(30) << left << distances[i];
        cout << (char)(i + 65) << "  ";
        int passingThrough = passesThrough[i];
        //till it reaches planet A
        if(passingThrough < i) {
            connect(passingThrough + 1, i + 1);
        } else {
            connect(i + 1, passingThrough + 1);
        }
        while(passingThrough != -1) {
            // //to next node in path
            cout << (char)(passingThrough + 65) << "  ";
            int passedThrough = passingThrough;
            passingThrough = passesThrough[passingThrough];

            if(passingThrough != -1) {
                if(passedThrough + 1 < passingThrough + 1) {
                    connect(passedThrough + 1, passingThrough + 1); 
                } else {
                    connect(passingThrough + 1, passedThrough + 1);
                }                
            }
        }
        cout << endl;
    }
}

int main() {
    loadFromFile();
    initializeMatrices();
    initmap();
    setPlanetsGraph();
    dijkstra();
    displayShortestDistances();
    displayGraph();
}

#endif