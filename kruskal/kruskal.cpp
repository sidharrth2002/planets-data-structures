#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

// classes:
class Planet {
    public:
        string name;
        int id;
        int x;
        int y;
        int z;
        int weight;
        int profit;
        int cloud[10];
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
    if(weight != 0) {
        this->value = profit/weight;
    }
};

class Edge {
    public:
        Planet* start;
        Planet* end;
        double distance;
        Edge() {}
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

//Loading from file:
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

//sort edges
bool compare(const Edge lhs, const Edge rhs) {
   return lhs.distance < rhs.distance;
}

//identify parent node
int getParent(int v, int parent[]){
    if(parent[v]==v){
        return v;
    }
    return getParent(parent[v],parent);
}

int main() {
    loadFromFile();
    int n = 10;
    int E = 18;
    //sort edges
    sort(edges.begin(),edges.end(),&compare);
    Edge output[n-1];

    // identify parent for each node
    int parent[n];
    for(int i=0;i<n;i++){
        parent[i]=i;
    }

    int count=0;
    int j=0;
    while(count<n-1){
        Edge currentEdge=edges[j];
        int p1=getParent(currentEdge.start->id,parent);
        int p2=getParent(currentEdge.end->id,parent);
        if(p1!=p2){
            output[count]=currentEdge;
            count++;
            parent[p1]=p2;
        }
        j++;
    }

    // print table
    cout << endl;   
    cout << "Edges:" << endl;
    cout << endl;
    cout << "src \tdest \twt" << endl;
 
    for(int i=0;i<n-1;i++){
        if(output[i].start<output[i].end){
            cout<<output[i].start->name.substr(7,1) <<"\t"<< output[i].end->name.substr(7,1) <<"\t"<< output[i].distance<<endl;
        }
        else cout<<output[i].start->name.substr(7,1) <<"\t"<< output[i].end->name.substr(7,1) <<"\t"<< output[i].distance<<endl;
    }


    // print graph
    cout << endl;   
    cout << "Graph:" << endl;
    cout << endl;
    string array[7][7] = {
        {"+", "-", "-", "A" ,"-", "-", "+"},
        {"|", " ", " ", " " ," ", " ", "|" },
        {"D", " ", "J", "-" ,"H", " ", "F"},
        {"|", " ", " ", " " ,"|", " ", " " },
        {"B", "-", "G", "-" ,"I", "-", "C"},
        {"|", " ", " ", " " ," ", " ", " " },
        {"+", "-", "-", "E" ," ", " ", " " },
    };
    for (int i = 0; i < 7; ++i){
        for(int j = 0; j < 7; ++j){
			cout << array[i][j];
		}
		cout << endl; // start a new row
    }


    return 0;
}