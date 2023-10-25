#include <cstddef>
#include <iostream>
#include <cstring>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
#include <stack>
#include <algorithm>
#include <unistd.h>
#include <map>
#include <limits>

#include "FibonacciHeap.h"

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
        // reserve memory to not realocate every time a new element is added
        v.reserve(n);
        for (int i = 0; i < n; i++)
            v.push_back({});
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
        bool representation;        // 0 - vector, 1 - matrix
        bool weighted;              // 0 - unweighted, 1 - weighted
        bool negative_weights = 0;      // 0 - no negative weights, 1 - negative weights
        float max_float = 10000000;
        
        map<pair<int, int>, float> weights;    // map of weights of edges
        AdjacencyMatrix adj_mx;
        AdjacencyVector adj_v;

        Graph(const char* file, const char* adj_representation, bool weighted){ 
            ifstream graph_input;       // open file
            graph_input.open(file);

            graph_input >> n;           // read number of vertices

            if(strcmp(adj_representation, "vector") == 0){   // set graph representation and its data structure
                representation = VECTOR;
                adj_v.initialize(n);
            }
            if(strcmp(adj_representation, "matrix") == 0){
                representation = MATRIX;
                adj_mx.initialize(n);
            }
        
            int v1, v2;
            float weight;
            m = 0;        
            
            while(graph_input >> v1 >> v2){     // read edges
                if(representation)              // check if graph is represented by matrix or vector
                    adj_mx.insert(v1, v2);
                else
                    adj_v.insert(v1, v2);

                if(weighted){
                    graph_input >> weight;
                    if(weight < 0) negative_weights = 1;
                    pair<int, int> ordered_pair = (v1 < v2) ? std::make_pair(v1, v2) : std::make_pair(v2, v1);
                    weights[ordered_pair] = weight;
                }
                m++;
            }
            m--;                                // last line of file is read twice

            graph_input.close();        // close file
        }

    pair<vector<float>, vector<int>> vectorDijsktra(int vertex){
        if(negative_weights){
            cout << "Graph has negative weights, cannot use Dijkstra's algorithm\n";
            return {};
        }

        vector<float> distance(n, max_float);      
        vector<bool> visited(n, 0);                
        vector<int> parent(n, -1);
        
        distance[vertex - 1] = 0;                  

        for (int i = 0; i < n; i++) {

            int min_distance = max_float, min_index;
            for (int j = 0; j < n; j++) { 
                if(!visited[j] && distance[j] <= min_distance){
                    min_distance = distance[j];
                    min_index = j;
                }
            }
           
            for (auto i : distance) {
                cout << i << " ";
            }
            cout << endl << "min_index: " << min_index + 1 << endl;

            visited[min_index] = 1;

            // assume graph is represented by vector
            for (int j = 0; j < adj_v.v[min_index].size(); j++) {  
                int neighbor_index = adj_v.v[min_index][j] - 1;
                if(distance[min_index] + weights[order_pair(min_index + 1, neighbor_index + 1)] < distance[neighbor_index]){
                    distance[neighbor_index] = distance[min_index] + weights[order_pair(min_index + 1, neighbor_index + 1)];
                    parent[neighbor_index] = min_index + 1;D
                }
            }
        }
        return make_pair(distance, parent);
    }

    pair<vector<float>, vector<int>> heapDijkstra(int vertex){
        if(negative_weights){
            cout << "Graph has negative weights, cannot use Dijkstra's algorithm\n";
            return {};
        }

        vector<float> distance(n, max_float);
        vector<bool> visited(n, 0);                 
        vector<int> parent(n, -1);
        FibonacciHeap heap;
        vector<Node*> vertices(n);

        for (int i = 0; i < n; i++) {
            vertices[i] = new Node(i + 1, max_float);
            heap.insertVertex(vertices[i]);
        }

        vertices[vertex - 1]->key = 0;
        heap.decreaseKey(0, vertices[vertex - 1]);

        while(!heap.isEmpty()){
            Node* current = heap.deleteMin();
            visited[current->data - 1] = 1;
            distance[current->data - 1] = current->key;
            
            for (int i = 0; i < adj_v.v[current->data - 1].size(); i++) {           // assume graph is represented by vector
                if(!visited[adj_v.v[current->data - 1][i] - 1]){
                    if(current->key + weights[order_pair(current->data, adj_v.v[current->data - 1][i])] < vertices[adj_v.v[current->data - 1][i] - 1]->key){
                        vertices[adj_v.v[current->data - 1][i] - 1]->key = current->key + weights[order_pair(current->data, adj_v.v[current->data - 1][i])];
                        heap.decreaseKey(vertices[adj_v.v[current->data - 1][i] - 1]->key, vertices[adj_v.v[current->data - 1][i] - 1]);
                    }
                }
            }
        }

        return make_pair(distance, parent);
    }

    pair<int, int> order_pair(int v1, int v2){
        return (v1 < v2) ? std::make_pair(v1, v2) : std::make_pair(v2, v1);
    }


    // vector<float> heapDijkstra(int vertex){
    //     vector<float> distance(n, -1);
    //     vector<bool> visited(n, 0);
    //     FibonacciHeap heap;
    //     vector<Node*> vertices(n);

    //     for (int i = 0; i < n; i++) {
    //         vertices[i] = new Node(i + 1, INT_MAX);
    //         heap.insertVertex(vertices[i]);
    //     }

    //     vertices[vertex - 1]->key = 0;
    //     heap.decreaseKey(0, vertices[vertex - 1]);

    //     while(!heap.isEmpty()){
    //         Node* current = heap.deleteMin();
    //         visited[current->data - 1] = 1;
    //         distance[current->data - 1] = current->key;
            
    //         for (int i = 0; i < adj_v.v[current->data - 1].size(); i++) {           // assume graph is represented by vector
    //             if(!visited[adj_v.v[current->data - 1][i] - 1]){
    //                 if(current->key + weights[make_pair(current->data, adj_v.v[current->data - 1][i])] < vertices[adj_v.v[current->data - 1][i] - 1]->key){
    //                     vertices[adj_v.v[current->data - 1][i] - 1]->key = current->key + weights[make_pair(current->data, adj_v.v[current->data - 1][i])];
    //                     heap.decreaseKey(vertices[adj_v.v[current->data - 1][i] - 1], vertices[adj_v.v[current->data - 1][i] - 1]->key);
    //                 }
    //             }
    //         }
    //     }

    //     return distance;
    // }

    void bfs(int vertex){
        vector<bool> visited(n, 0);
        vector<int> parent(n, -1);
        vector<int> level(n, -1);
        queue<int> queue;

        visited[vertex - 1] = 1;
        queue.push(vertex);                // push root to queue
        level[vertex - 1] = 0;             // level of the root is 0

        while(!queue.empty()){
            int current = queue.front();
            queue.pop();

            if(representation){                // check if graph is represented by matrix or vector
                for (int i = 0; i < adj_mx.m[current - 1].size(); i++) {
                    if(adj_mx.m[current - 1][i] && !visited[i]){
                        visited[i] = 1;
                        parent[i] = current;
                        level[i] = level[current - 1] + 1;
                        queue.push(i + 1);
                    }
                }
            }
            else{
                for (int i = 0; i < adj_v.v[current - 1].size(); i++) {
                    if(!visited[adj_v.v[current - 1][i] - 1]){
                        visited[adj_v.v[current - 1][i] - 1] = 1;
                        parent[adj_v.v[current - 1][i] - 1] = current;
                        level[adj_v.v[current - 1][i] - 1] = level[current - 1] + 1;
                        queue.push(adj_v.v[current - 1][i]);
                    }
                }
            }
        }

        ofstream output;
        output.open("bfs(" + to_string(vertex) + ")spanning_tree.txt");
        for (int i = 0; i < parent.size(); i++) {
            output << parent[i] << " " << level[i] << "\n";
        }
        output.close();
    }

    void dfs(int vertex){
        vector<bool> visited(n, 0);
        vector<int> parent(n, -1);
        vector<int> level(n, -1);
        stack<int> stack;

        visited[vertex - 1] = 1;
        stack.push(vertex);                // push root to stack
        level[vertex - 1] = 0;             // level of the root is 0

        while(!stack.empty()){
            int current = stack.top();
            stack.pop();
            
            if(representation){                // check if graph is represented by matrix or vector
                for (int i = 0; i < adj_mx.m[current - 1].size(); i++) {
                    if(adj_mx.m[current - 1][i] && !visited[i]){
                        visited[i] = 1;
                        parent[i] = current;
                        level[i] = level[current - 1] + 1;
                        stack.push(i + 1);
                    }
                }
            }
            else{
                for (int i = 0; i < adj_v.v[current - 1].size(); i++) {
                    if(!visited[adj_v.v[current - 1][i] - 1]){
                        visited[adj_v.v[current - 1][i] - 1] = 1;
                        parent[adj_v.v[current - 1][i] - 1] = current;
                        level[adj_v.v[current - 1][i] - 1] = level[current - 1] + 1;
                        stack.push(adj_v.v[current - 1][i]);
                    }
                }
            }
        }
        
        ofstream output;
        output.open("dfs(" + to_string(vertex) + ")spanning_tree.txt");
        for (int i = 0; i < parent.size(); i++) {
            output << parent[i] << " " << level[i] << "\n";
        }
        output.close();
    }

     int distance(int vertex1, int vertex2){    // distance between two vertices
        if(vertex1 == vertex2)
            return 0;

        vector<bool> visited(n, 0);
        vector<int> level(n, -1);
        queue<int> queue;

        visited[vertex1 - 1] = 1;
        queue.push(vertex1);                // push root to queue
        level[vertex1 - 1] = 0;             // level of the root is 0

        while(!queue.empty()){
            int current = queue.front();
            queue.pop();

            if(representation){                // check if graph is represented by matrix or vector
                for (int i = 0; i < adj_mx.m[current - 1].size(); i++) {
                    if(adj_mx.m[current - 1][i] && !visited[i]){
                        if(i + 1 == vertex2)
                            return level[current - 1] + 1;
                        visited[i] = 1;
                        level[i] = level[current - 1] + 1;
                        queue.push(i + 1);
                    }
                }
            }
            else{
                for (int i = 0; i < adj_v.v[current - 1].size(); i++) {
                    if(!visited[adj_v.v[current - 1][i] - 1]){
                        if(adj_v.v[current - 1][i] == vertex2)
                            return level[current - 1] + 1;
                        visited[adj_v.v[current - 1][i] - 1] = 1;
                        level[adj_v.v[current - 1][i] - 1] = level[current - 1] + 1;
                        queue.push(adj_v.v[current - 1][i]);
                    }
                }
            }
        }
        return -1;
    }

    int diameter(){
        int diameter = 0;
        bool infinite = 0;
        
        for (int i = 0; i < n; i++) {
            vector<bool> visited(n, 0);
            vector<int> level(n, -1);
            queue<int> queue;

            visited[i] = 1;
            queue.push(i + 1);                // push root to queue
            level[i] = 0;                       // level of the root is 0

            while(!queue.empty()){
                int current = queue.front();
                queue.pop();

                if(representation){                // check if graph is represented by matrix or vector
                    for (int i = 0; i < adj_mx.m[current - 1].size(); i++) {
                        if(adj_mx.m[current - 1][i] && !visited[i]){
                            visited[i] = 1;
                            if(level[current - 1] + 1 > diameter)
                                diameter = level[current - 1] + 1;
                            level[i] = level[current - 1] + 1;
                            queue.push(i + 1);
                        }
                    }
                }
                else{
                    for (int i = 0; i < adj_v.v[current - 1].size(); i++) {
                        if(!visited[adj_v.v[current - 1][i] - 1]){
                            visited[adj_v.v[current - 1][i] - 1] = 1;
                            if(level[current - 1] + 1 > diameter)
                                diameter = level[current - 1] + 1;
                            level[adj_v.v[current - 1][i] - 1] = level[current - 1] + 1;
                            queue.push(adj_v.v[current - 1][i]);
                        }
                    }
                }
            }
            
            if(i == 0){         // check if graph is connected, if not, diameter is infinite
                for (int i = 0; i < visited.size(); i++) {
                    if(!visited[i])
                        return -1;
                }
            }
        }

        return diameter;
    }

    // aproximate diameter
    int aprox_diameter(int number_of_samples){
        int diameter = 0;
        bool infinite = 0;
        
        for (int i = 0; i < number_of_samples; i++) {
            vector<bool> visited(n, 0);
            vector<int> level(n, -1);
            queue<int> queue;

            int random_vertex = (rand() % n) + 1;
            visited[random_vertex - 1] = 1;
            queue.push(random_vertex);                // push root to queue
            level[random_vertex - 1] = 0;                       // level of the root is 0

            while(!queue.empty()){
                int current = queue.front();
                queue.pop();

                if(representation){                // check if graph is represented by matrix or vector
                    for (int i = 0; i < adj_mx.m[current - 1].size(); i++) {
                        if(adj_mx.m[current - 1][i] && !visited[i]){
                            visited[i] = 1;
                            if(level[current - 1] + 1 > diameter)
                                diameter = level[current - 1] + 1;
                            level[i] = level[current - 1] + 1;
                            queue.push(i + 1);
                        }
                    }
                }
                else{
                    for (int i = 0; i < adj_v.v[current - 1].size(); i++) {
                        if(!visited[adj_v.v[current - 1][i] - 1]){
                            visited[adj_v.v[current - 1][i] - 1] = 1;
                            if(level[current - 1] + 1 > diameter)
                                diameter = level[current - 1] + 1;
                            level[adj_v.v[current - 1][i] - 1] = level[current - 1] + 1;
                            queue.push(adj_v.v[current - 1][i]);
                        }
                    }
                }
            }
            
            if(i == 0){
                for (int i = 0; i < visited.size(); i++) {
                    if(!visited[i])
                        return -1;
                }
            }
        }

        return diameter;
    }

    void connected_components(){
        vector<bool> visited(n, 0);
        vector<vector <int>> components_vertices;
        int components = 0;

        for (int i = 0; i < n; i++) {
            if(!visited[i]){
                components_vertices.push_back({});
                components++;
                queue<int> queue;

                visited[i] = 1;
                queue.push(i + 1);                //push first vertex of component to queue
                components_vertices[components - 1].push_back(i + 1);

                while(!queue.empty()){
                    int current = queue.front();
                    queue.pop();

                    if(representation){                // check if graph is represented by matrix or vector
                        for (int i = 0; i < adj_mx.m[current - 1].size(); i++) {
                            if(adj_mx.m[current - 1][i] && !visited[i]){
                                visited[i] = 1;
                                components_vertices[components - 1].push_back(i + 1);
                                queue.push(i + 1);
                            }
                        }
                    }
                    else{
                        for (int i = 0; i < adj_v.v[current - 1].size(); i++) {
                            if(!visited[adj_v.v[current - 1][i] - 1]){
                                visited[adj_v.v[current - 1][i] - 1] = 1;
                                components_vertices[components - 1].push_back(adj_v.v[current - 1][i]);
                                queue.push(adj_v.v[current - 1][i]);
                            }
                        }
                    }
                }
            }
        }
        
        ofstream output;
        output.open("connected_components.txt");
        output << components << "\n";
        sort(components_vertices.begin(), components_vertices.end(), [](const vector<int> & a, const vector<int> & b){ return a.size() > b.size(); }); // order components by size in descending order
        for (int i = 0; i < components_vertices.size(); i++) {
            output << components_vertices[i].size() << "\n";
            for (int j = 0; j < components_vertices[i].size(); j++) {
                output << components_vertices[i][j] << " ";
            }
            output << "\n";
        }
    }

    void output_file(){
        ofstream output;
        output.open("output.txt");
        output << "n: " << n << " " << "m: " << m << "\n";
        
        int min_degree = n, max_degree = 0, sum_degree = 0;
        vector<int> degrees;
        for (int i = 0; i < n; i++) {
            int degree = 0;
            if(representation)             // check if graph is represented by matrix or vector
                degree = count(adj_mx.m[i].begin(), adj_mx.m[i].end(), 1); 
            else
                degree = adj_v.v[i].size();
            
            if(degree < min_degree)
                min_degree = degree;
            if(degree > max_degree)
                max_degree = degree;
            sum_degree += degree;
            degrees.push_back(degree);
        }

        output << "min degree: " << min_degree << "\nmax degree: " << max_degree << "\naverage degree:" << sum_degree/float(n) << "\nmedian degree:";
    
        nth_element(degrees.begin(), degrees.begin() + degrees.size()/2, degrees.end());    // find median without sorting - O(n)
        
        if (degrees.size() % 2 == 0){   // if number of vertices is even, median is the average of the two middle values
            nth_element(degrees.begin(), degrees.begin() + degrees.size()/2 - 1, degrees.end());
            output << (degrees[degrees.size()/2 - 1] + degrees[degrees.size()/2])/2.0;
        }
        else                        // if number of vertices is odd, median is the middle value
            output << degrees[degrees.size()/2]; 
        
        output.close();
    }
};

/*
   
*/