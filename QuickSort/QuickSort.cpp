#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

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
    if(weight == 0){
        this->value =0;
    } else {
        this->value = static_cast<double>(profit)/static_cast<double>(weight);
    }
    cout << this->value << endl;
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
}


//Adjacency list 
void addEdge(vector<string> adj[], int u, string v) 
{ 
    adj[u].push_back(v); 
   
} 

void printGraph (vector<string> adj[], int V) 
{ 
    for (int v = 0; v < V; ++v) 
    { 
        cout << v ;
        if (adj[v].empty()){
                 cout << "->No adjacency";
             } 
    
        for (auto x : adj[v]) {
            cout << "->" << x; 
           
        }
        printf("\n"); 
    } 
}  

void Adjacencylist() {
        
        cout << " "<< endl;
        cout << "Adjacency list "<< endl;
         int V = 10; 

        for(int i = 0; i < 10; i++) {
            cout << (char)(i + 65) << " ";
            for (int j = 0; j < 10; j++) {
                if(distanceMatrix[i][j] != THEORETICAL_MAX) {
                    cout << "| " << (char)(j + 65) << "(" << distanceMatrix[i][j] << ") | -> ";
                }
            }
            cout << endl;
        }
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


void quicksortEdges(vector<Edge> &value, int left, int right) {

    if(left < right) {
        int pivotIndex = partitionEdge(value, left, right);
        quicksortEdges(value, left, pivotIndex - 1);
        quicksortEdges(value, pivotIndex, right);   
    }
}


//PLANET
int partitionPlanet(vector<Planet> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = values[pivotIndex].value;
    int x = left;
    int y = right;

    while(x <= y) {
        while(values[x].value > pivotValue) {
            x++;
        }
        while(values[y].value < pivotValue) {
            y--;
        }

        //This part is for swapping
        
        if(x <= y) {
            Planet temp = values[x];
            values[x] = values[y];
            values[y] = temp;

            x++;
            y--;
        }
    }
    return x;   
}

void quicksortPlanet(vector<Planet> &value, int left, int right) {

    if(left < right) {
        int pivotIndex = partitionPlanet(value, left, right);
        quicksortPlanet(value, left, pivotIndex - 1);
        quicksortPlanet(value, pivotIndex, right);   
    }
}
    int main() {
        loadFromFile();
        initializeMatrices();
        Adjacencylist();

        //EDGES
        cout << "  " << endl;
        cout << " " << endl;
        cout << "Edges sorted in ascending order of distance: " << endl;
        quicksortEdges(edges, 0, edges.size() - 1);  

        //Print the list
         for (int i = 0; i < edges.size(); i++) {
             cout << (char)(edges[i].start->id + 65) << " " << (char)(edges[i].end->id + 65) << " -> "<< edges[i].distance << endl;
        }
        

        //PLANETS
        cout << "  " << endl;
        cout << "  " << endl;
        cout << "List of planets in descending order of value: " << endl;
        quicksortPlanet(planets, 0, planets.size() - 1); 

        //Print the list
        cout << setw(7) << "ID" << setw(15) << "Name" << setw(15) << "X"<< setw(15) << "Y"<< setw(15)<< "Z"<< setw(15)<< "Weight" << setw(15) << "Profit" <<setw(15) << "Value" << endl << endl;
        for (int i = 0; i < planets.size(); i++) {
            cout << setw(7) << planets[i].id << setw(15) << planets[i].name << setw(15) << planets[i].x << setw(15)<< planets[i].y<< setw(15)<< planets[i].y <<setw(15)<< planets[i].weight << setw(15) << planets[i].profit << endl << setw(15) << planets[i].value << endl;
         }
        
    return 0;
 
}

