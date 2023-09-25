#include <iostream>
#include <fstream>
#define VECTOR 0;
#define MATRIX 1;
using namespace std;

class AdjacencyMatrix {
    
};

class AdjacencyVector {

};

class Graph {
    public:
        int n, m; 
        bool representation;
        AdjacencyMatrix adj_mx;
        AdjacencyVector adj_v;

        Graph(const char* file, const char* adj_representation){

            ifstream graph_input;
            graph_input.open(file);

            graph_input >> n;

            if(adj_representation == "vector")
                representation = VECTOR;
            if(adj_representation == "matrix")
                representation = MATRIX;
        
            int v1, v2;
            while(!graph_input.eof()){
                graph_input >> v1 >> v2;
            }

            graph_input.close();

        }

        void show(){
            cout << representation;
        }
};

/*
   
*/