#include <iomanip>
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
};

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

const int THEORETICAL_MAX = 1000000;
const int MAX_ENTRIES = 10;
int distanceMatrix[MAX_ENTRIES][MAX_ENTRIES];



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
}

//QUICK SORT BEGINS HERE
//EDGES
int partitionEdge(vector<Edge> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = values[pivotIndex].distance;
    int x = left;
    int y = right;

    while(x <= y) {
        while(values[x].distance < pivotValue) {
            x++;
        }
        while(values[y].distance > pivotValue) {
            y--;
        }

        //This part is for swapping
        
        if(x <= y) {
            Edge temp = values[x];
            values[x] = values[y];
            values[y] = temp;

            x++;
            y--;
        }
    }
    return x;   
}


void quicksort(vector<Edge> &value, int left, int right) {

    if(left < right) {
        int pivotIndex = partitionEdge(value, left, right);
        quicksort(value, left, pivotIndex - 1);
        quicksort(value, pivotIndex, right);   
    }
}


//PLANET
int partition(vector<Planet> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = values[pivotIndex].profit;
    int i = left;
    int j = right;
    
 
    while(i <= j) {
        while(values[i].profit > pivotValue) {
            i++;
        }
        while(values[j].profit < pivotValue) {
            j--;
        }

        //This part is for swapping
        if(i <= j) {
            Planet temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j++;
        }
    }
    return i;
    
}

void quicksort(vector<Planet> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

    int main() {
        loadFromFile();
        initializeMatrices();
        
        //EDGES
        cout << "  " << endl;
        cout << " " << endl;
        cout << "Edges sorted by ascending order of distance: " << endl;
        quicksort(edges, 0, edges.size() - 1);  

        //Print the list
         for (int i = 0; i < edges.size(); i++) {
             cout << edges[i].start->name<< " " << edges[i].end->name << " "<< edges[i].distance<<  endl;
        }
        

        //PLANETS
        cout << "  " << endl;
        cout << "  " << endl;
        cout << "Planet sorted by profits " << endl;
        quicksort(planets, 0, planets.size() - 1); 

        //Print the list
        for (int i = 0; i < planets.size(); i++) {
            cout << planets[i].profit<< " "  << planets[i].name << endl;
         }
        
    return 0;
 
}