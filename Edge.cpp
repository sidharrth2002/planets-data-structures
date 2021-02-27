#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Planet.h"
#include "Edge.h"
using namespace std;

Edge::Edge(Planet* start, Planet* end) {
    this->start = start;
    this->end = end;
    //calculate distance between planets
    this->distance = sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2) + pow(end->z - start->z, 2));
};