//Sidharrth Nagappan
//1181102313

#ifndef KNAPSACK_H
#define KNAPSACK_H
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
    }};

class Edge {
    public:
        Planet* start;
        Planet* end;
        double distance;
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

const int capacity = 80;
const int numItems = 10;
int Knapsack[numItems + 1][capacity + 1];
vector<int> weights;
vector<int> profits;

//custom sort function
struct sortByWeight
{
    bool operator()( const Planet& lx, const Planet& rx ) const {
        return rx.weight < lx.weight;
    }
};

void initializeMatrices() {
    //sort based on weights
    sort( planets.begin(), planets.end(), sortByWeight());
    Planet dummy(0,"",0,0,0,0,0);
    planets.insert(planets.begin(), dummy);
}

void knapsack() {
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
            cout << setw(3) << Knapsack[i][w] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "What planets to pass through boss?" << endl << endl;
    int i = numItems;
    int j = capacity;

    int totalBenefit = 0;
    int totalWeight = 0;

    //iterate through table to see what items we take
    while(i > 0 && j > 0) {
        //if the value is not the same as the row above
        //that planet has been taken
        if(Knapsack[i][j] != Knapsack[i-1][j]) {
            cout << "Planet " << (char)(planets[i].id + 65) << " with benefit = " << planets[i].profit 
            << " and weight = " << planets[i].weight << endl;
            totalBenefit += planets[i].profit;
            totalWeight += planets[i].weight;
            j = j - planets[i].weight;
            i--;
        } else {
            i--;
        }
    }
    cout << endl << "===================================" << endl;
    cout << "TOTAL BENEFIT = " << totalBenefit << endl;
    cout << "TOTAL WEIGHT = " << totalWeight << endl;
    cout << "===================================" << endl;
}

void showPlanets() {
    cout << "PLANETS SUMMARY: " << endl << endl;
    cout << setw(7) << "ID" << setw(15) << "Name" << setw(15) << "X"<< setw(15) << "Y"<< setw(15)<< "Z"<< setw(15)<< "Weight" << setw(15) << "Profit" << setw(15) << endl << endl;
    for (int i = 0; i < planets.size(); i++) {
        cout << setw(7) << planets[i].id << setw(15) << planets[i].name << setw(15) << planets[i].x << setw(15)<< planets[i].y<< setw(15)<< planets[i].z <<setw(15)<< planets[i].weight << setw(15) << planets[i].profit << endl;
    }
    cout << endl << endl;
}

int main() {
    loadFromFile();
    showPlanets();
    initializeMatrices();
    knapsack();
}

#endif