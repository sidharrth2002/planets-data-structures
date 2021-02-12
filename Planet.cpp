#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Planet.h"
using namespace std;

Planet::Planet(int id, string name, int x, int y, int z, int weight, int profit) {
    this->id = id;
    this->name = name;
    this->x = x;
    this->y = y;
    this->z = z;
    this->weight = weight;
    this->profit = profit;
};