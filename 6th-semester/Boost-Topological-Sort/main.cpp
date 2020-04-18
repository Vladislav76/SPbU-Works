#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/topological_sort.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace boost;
using namespace std;

pair<vector<int>,double> top_sort(const string &filename) {
    typedef adjacency_list< vecS, vecS, directedS> Graph;
    
    ifstream infile(filename);
  
    string str;
    for (int i = 1; i <= 7; i++) {
        infile >> str;
    }

    int n, m;
    infile >> n >> n >> m;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int f, s, tmp;
        infile >> f >> s >> tmp;\
        edges[i] = {f - 1, s - 1};
    }
    
    infile.close();
   
    Graph G(edges.begin(), edges.end(), n);

    vector<int> c;
    
    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    topological_sort(G, std::back_inserter(c));
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double time = (end_time.tv_sec - start_time.tv_sec) * 1e6 +
                  (end_time.tv_nsec - start_time.tv_nsec) * 1e-3;
    
    return make_pair<>(c, time);
}


int main(int argc, char **argv) {
    if (argc > 1) {
        
        double time = 0;
        int reps = 1;
        
        if (argc > 2) {
            reps = atoi(argv[2]);
        }
        
        vector<int> order;
        
        for (int i = 1; i <= reps; i++) {
            auto result = top_sort(argv[1]);
            order = result.first;
            time += result.second;
        }
        printf("Average time: %f mcs\n", time / reps);
        
        cout << "A topological ordering:\n";
        for (vector<int>::reverse_iterator ii = order.rbegin(); ii != order.rend(); ii++)
            cout << ((*ii) + 1) << " ";
        cout << endl;
    } else {
        printf("File path is not specified");
    }

    return 0;
}
