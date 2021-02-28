#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
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

void loadFromFile() {
  //   ifstream input;
  //   input.open("../A2planets.txt");
  //   string name;
  //   int x, y, z, weight, profit;

  //   int i = 0;
  //   //create planets
  //   while(input >> name >> x >> y >> z >> weight >> profit) {
  //       Planet planet(i++, name, x, y, z, weight, profit);
  //       planets.push_back(planet);
  //   }
  //  input.close();

  //   //assuming planet A is in the first index, B second and so on
  //   //create the edges based on the map
  //   input.open("../routes.txt");
  //   char startPlanet, endPlanet;
  //   int start, end;
  //   while(input >> startPlanet >> endPlanet) {
  //       //convert planet char to integer
  //       start = (int)startPlanet - 65;
  //       end = (int)endPlanet - 65;
  //       Edge edge(&planets[start], &planets[end]);
  //       edges.push_back(edge);
  //   }
  //   // cout << edges[2].start->id << endl;
  //   input.close();
}

bool compare(const Edge lhs, const Edge rhs) {
   return lhs.distance < rhs.distance;
}

int getParent(int v, int parent[]){
    if(parent[v]==v){
      cout << "parent equals v" << endl;
        return v;
    }
    return getParent(parent[v],parent);
}

int main() {
    vector<Planet> planets;
    vector<Edge> edges;
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

    int n,E;
    n = 10;
    E = 18;
    cout << "1" << endl;
    cout << "Size is " << edges.size() << endl;

    sort(edges.begin(),edges.end(),&compare);

    // vector<Edge> output;
    Edge output[n-1];

    int parent[n];
    for(int i=0;i<n;i++){
        parent[i]=i;
    }

    cout << "2" << endl;
    int count=0;
    int j=0;

    while(count<n-1){
        cout << edges[j].start->id << endl;
        Edge currentEdge=edges[j];
        cout << currentEdge.start->id << endl;
        int p1=getParent(currentEdge.start->id,parent);
        int p2=getParent(currentEdge.end->id,parent);
        cout << p1 << endl;
        cout << p2 << endl;
        if(p1!=p2){
            cout << "j is " << j << endl;
            output[count]=currentEdge;
            count++;
            parent[p1]=p2;
        }
        j++;
    }

    cout << "3" << endl;
    for(int i=0;i<n-1;i++){
        if(output[i].start<output[i].end){
            cout<<output[i].start->name <<" "<< output[i].end->name <<" "<< output[i].distance<<endl;
        }
        else cout<<output[i].start->name <<" "<< output[i].end->name <<" "<< output[i].distance<<endl;
    }
    
    cout << "4" << endl;

    return 0;
}