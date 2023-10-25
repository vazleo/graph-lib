#include "FibonacciHeap.h"
#include "graphs.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/resource.h>
#include <ctime>
#include <limits.h>

// long get_memory_usage_kb() {
//     struct rusage usage;
//     getrusage(RUSAGE_SELF, &usage);
//     return usage.ru_maxrss; // bytes
// }

// int main(){
//     long baseline = get_memory_usage_kb();
//     cout << "Baseline: " << baseline << " KB" << endl;

//     Graph a = Graph("studie-cases/grafo_6.txt", "vector");
//     std::cout << "Memory usage: " << get_memory_usage_kb() - baseline << " KB" << std::endl;
// } 



// int main(){
//     // average bfs and dfs time, running 100 BFS with random vertices
    

//     Graph a = Graph("studie-cases/grafo_6.txt", "vector");
//     int random_vertex = (rand() % a.n) + 1;
    
//     double elapsed_time = 0;
//     for(int i = 0; i < 10; i++){
//         clock_t start = clock();
//         a.dfs(random_vertex);
//         clock_t end = clock();
//         elapsed_time += double(end - start) / CLOCKS_PER_SEC;
//     }
//     elapsed_time /= 10;

//     cout << elapsed_time << endl;
// }


// int main(){
//     // Determine o pai dos veertices 10, 20, 30 na arvore geradora
//     // induzida pela BFS e pela DFSquando iniciamos a busca nos 
//     // veertices 1, 2, 3.

//     Graph a = Graph("studie-cases/grafo_5.txt", "vector");
//     a.dfs(1);
//     a.bfs(1);
//     a.dfs(2);
//     a.bfs(2);
//     a.dfs(3);
//     a.bfs(3);
// }

// int main(){
//     // Determine a distancia entre os seguintes pares de veertices 
//     // (10,20), (10,30), (20,30).

//     Graph a = Graph("studie-cases/grafo_6.txt", "vector");
//     cout << a.distance(10, 20) << endl;
//     cout << a.distance(10, 30) << endl;
//     cout << a.distance(20, 30) << endl;
// }

// int main(){
//     //Obtenha as componentes conexas do grafo. Quantas componentes conexas tem o grafo? Qual
//     //´e o tamanho da maior e da menor componente conexa?

//     Graph a = Graph("studie-cases/grafo_6.txt", "vector");
//     a.connected_components();
// }

// int main(){
//     Graph a = Graph("studie-cases/grafo_6.txt", "vector");
//     cout << a.diameter() << endl;
// }

int main(){
    Graph a = Graph("studie-cases/a.txt", "vector", 1);
    // for(auto i : a.weights)
    //     cout << i.second << endl;
    
    // auto b = a.vectorDijsktra(1);
    // for(auto i : b.first)
    //     cout << i << endl;

    auto b = a.heapDijkstra(1);
    for(auto i : b.second)
        cout << i << endl;
}