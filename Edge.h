#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Planet.h"
using namespace std;

class Edge {
    public:
        Planet* start;
        Planet* end;
        int distance;
        Edge(Planet* start, Planet* end);
};

#endif