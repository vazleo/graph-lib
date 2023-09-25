#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

#define VECTOR 0;
#define MATRIX 1;

using namespace std;

class AdjacencyMatrix {
    public:
        int n;
        bool **matrix;
    
    void initialize(int n){}

    void insert(int v1, int v2){}

};

class AdjacencyVector {
    public:
        int n;
        vector<vector<int>> v;
        // vector<int> *vector; init in initialize()?

    void initialize(int n){}

    void insert(int v1, int v2){}
};

class Graph {
    public:
        int n, m;                   // number of vertices (n) and edges (m)                      
        bool representation;        // graph representation -> vector (0) | matrix (1)
        AdjacencyMatrix adj_mx;
        AdjacencyVector adj_v;

        Graph(const char* file, const char* adj_representation){

            ifstream graph_input;       // open file
            graph_input.open(file);

            graph_input >> n;

            if(strcmp(adj_representation, "vector") == 0)   // set graph representation
                representation = VECTOR;
            if(strcmp(adj_representation, "matrix") == 0)
                representation = MATRIX;
        
            int v1, v2;         
            while(!graph_input.eof()){      // read incoming edges
                graph_input >> v1 >> v2;
            }

            graph_input.close();        // close file

        }

    void show(){
        cout << representation;
    }
};

/*
   
*/