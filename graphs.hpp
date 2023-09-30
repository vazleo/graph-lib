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
        vector<vector<bool>> m;
    
    void initialize(int n){
        for (int i = 0; i < n; i++) {
            vector<bool> new_row(n, 0);
            m.push_back(new_row);
        }
    }

    void insert(int vertex1, int vertex2){
        m[vertex1 - 1][vertex2 - 1] = 1;
        m[vertex2 - 1][vertex1 - 1] = 1;
    }

    void print(){
        for (int i = 0; i < m.size(); i++) {
            for (int j = 0; j < m[i].size(); j++) {
                cout << m[i][j] << " ";
            }
            cout << "\n";   // endl performs significantly worse than \n
        }
    }
};

class AdjacencyVector {
    public:
        vector<vector<int>> v;

    void initialize(int n){
        for (int i = 0; i < n; i++) {
            v.push_back({});
        }
    }

    void insert(int vertex1, int vertex2){
        v[vertex1 - 1].push_back(vertex2);          
        v[vertex2 - 1].push_back(vertex1);
    }

    void print(){     
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                cout << v[i][j] << " ";
            }
            cout << "\n";   // endl performs significantly worse than \n
        }
    }
};

class Graph {
    public:
        int n, m;                   // number of vertices (n) and edges (m)                      
        bool representation;        // graph representation -> vector (0 - false) | matrix (1 - true)
        AdjacencyMatrix adj_mx;
        AdjacencyVector adj_v;

        Graph(const char* file, const char* adj_representation){ 
            ifstream graph_input;       // open file
            graph_input.open(file);

            graph_input >> n;           // set N

            if(strcmp(adj_representation, "vector") == 0){   // set graph representation and its data structure
                representation = VECTOR;
                adj_v.initialize(n);
            }
            if(strcmp(adj_representation, "matrix") == 0){
                representation = MATRIX;

                adj_mx.initialize(n);
            }
        
            int v1, v2;         
            while(!graph_input.eof()){      // read incoming edges
                graph_input >> v1 >> v2;
                if(representation)
                    adj_mx.insert(v1, v2);
                else
                    adj_v.insert(v1, v2);
                    
            }
            
            graph_input.close();        // close file

        }

    void show_representation(){
        cout << representation << "\n";
    }

    void print(){
        if(representation){
            adj_mx.print(); 
        }
        else{
            adj_v.print();
        }
    }
};

/*
   
*/