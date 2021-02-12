#ifndef PLANET_H
#define PLANET_H

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

#endif