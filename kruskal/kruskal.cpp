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
    this->value = profit/weight;
};

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

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void printArray (T A[], int n) {
  for (int i = 0; i < n; i++)
    cout << A[i] << " ";
  cout << endl;
}

template <typename T>
class PriorityQueue {
  vector<T> A;

  void heapify_enqueue (int index) {   // used in enqueue.
    if (index == 0)                    // if already at root.
      return;
    
    // parent index
    int parent = (index-1)/2;
    
    // swap if parent is smaller
    if (A[index] > A[parent]) {
        swap(A[index], A[parent]);
    // recursion of the function
        heapify_enqueue(index);
    }



  }
    
  void heapify_dequeue (int index) {   // used in dequeue.
    int max;                           // max index
    // left child index
    int left = 2*index + 1;
    // right child index
    int right = 2*index + 2;
    
    // compare and find the greatest child
    if (right < A.size()) {
        if (A[left] > A[right]) {
            max = left;
        } else {
            max = right;
        }
        if (A[index] > A[max]) {
            max = index;
        }
    } else if (left < A.size()) {
        if (A[left] > A[index]) {
            max = left;
        } else {
            max = index;
        }
    } else {
        max = index;
    }
    if (max != index) {
      swap (A[index], A[max]);
      heapify_dequeue (max);
    }
  }
  
 public:
  void enqueue (T element) {
    A.push_back (element);
    heapify_enqueue (A.size()-1);  // start at last element.
  }
  
  T dequeue() {
    T removed_element = A[0];
    A[0] = A[A.size()-1];          // copy last element to root.
    A.pop_back();                  // remove last element.
    heapify_dequeue (0);           // start at root.
    return removed_element;
  }
  
  int size() {
    return A.size();
  }

  void print() {
    for (int i = 0; i < A.size(); i++)
      cout << A[i] << " ";
    cout << endl;
  }  
};

void kruskalmst()

int main() {
    loadFromFile();
    for(int i = 0; i < numP; i++) {
        for(int j = 0; j < numP; j++) {
            planets[i].cloud[]
        }
    }
}