//Sidharrth Nagappan
//1181102313

#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
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


const int capacity = 80;
const int numItems = 10;
int Knapsack[numItems + 1][capacity + 1];
vector<int> weights;
vector<int> profits;

//custom sort function
struct sortByWeight
{
    bool operator()( const Planet& lx, const Planet& rx ) const {
        return lx.weight < rx.weight;
    }
};

void initializeMatrices() {
    //sort based on weights
    sort( planets.begin(), planets.end(), sortByWeight());
    Planet dummy(0,"",0,0,0,0,0);
    planets.insert(planets.begin(), dummy);
}

int knapsack() {
    cout << "The 0/1 Knapsack Table: " << endl;
    //for each item
    for(int i = 0; i <= numItems; i++) {
        //till reaching max capacity
        for(int w = 0; w <= capacity; w++) {
            //first row and col by default 0
            //counting starts from 0
            if(i == 0 || w == 0) {
                Knapsack[i][w] = 0;
            } else if(planets[i].weight <= w) {
              //if the current capacity can fit the item
              //check if adding that item yields greater profit than bag without the planet
                Knapsack[i][w] = max(planets[i].profit + Knapsack[i-1][w-planets[i].weight], 
                                    Knapsack[i-1][w]);
            } else {
                //if not then don't take the planet
                //get value from row above
                Knapsack[i][w] = Knapsack[i-1][w];
            }
            cout << setw(5) << Knapsack[i][w] << " ";
        }
        cout << endl;
    }

    cout << "What planets to pass through boss?" << endl << endl;
    int i = numItems;
    int j = capacity;

    //iterate through table to see what items we take
    while(i > 0 && j > 0) {
        //if the value is not the same as the row above
        //that planet has been taken
        if(Knapsack[i][j] != Knapsack[i-1][j]) {
            cout << "Planet " << (char)(planets[i].id + 65) << " is taken with benefit = " << planets[i].profit 
            << " and weight = " << planets[i].weight << endl;
            j = j - planets[i].weight;
            i--;
        } else {
            i--;
        }
    }
}

int main() {
    loadFromFile();
    initializeMatrices();
    knapsack();
}

#endif