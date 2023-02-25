#include <iostream>
#include <vector>
#include <limits>
#include <float.h>
#include <unordered_map>
#include <algorithm>


using namespace std;

struct four_coordinate {
    double a;
    double b;
    double c;
    double d;
};

struct three_coordinate {
    double x;
    double y;
    double z;
};

struct Edge {
    int u;
    int v;
    double weight;

    Edge(int u, int v, double weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

bool compareEdges(Edge& e1, Edge& e2) {
    return e1.weight < e2.weight;
}

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) {
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }
    }
};

vector<std::unordered_map<double, double> > kruskalMST(const vector<std::unordered_map<double, double> >& graph) {
    int n = graph.size();
    vector<std::unordered_map<double, double> > mst(n);  // The minimum spanning tree
    vector<Edge> edges;  // All edges in the graph
    DisjointSet ds(n);  // Disjoint set data structure for checking cycles

    // Add all edges to the list of edges
    for (int u = 0; u < n; u++) {
        for (auto& [v, weight] : graph[u]) {
            if (u < v) {  // add the edge only once, based on its direction
                Edge e = Edge(u, v, weight);
                edges.push_back(e);
            }
        }
    }

    // Sort the edges in non-decreasing order by weight
    std::sort(edges.begin(), edges.end(), compareEdges);

    // Add edges to the minimum spanning tree until all vertices are connected
    int count = 0;
    for (int i = 0; i < edges.size() && count < n - 1; i++) {
        Edge e = edges[i];
        int u = e.u;
        int v = e.v;
        if (ds.find(u) != ds.find(v)) {
            ds.merge(u, v);
            mst[u].insert(make_pair(v, e.weight));
            // mst[v].insert(make_pair(u, e.weight));
            count++;
        }
    }

    double max = DBL_MIN;
    for (int i = 0; i < n; i++) {
        std::__1::unordered_map<double, double>::iterator it = mst[i].begin();
        while (it != mst[i].end()) {
            if (it->second > max) {
                max = it->second;
            }
            it++;
        }
    }

    printf("%f ", max);

    return mst;
}

vector<std::unordered_map<double, double> > generateCompleteGraph(int n) {
    vector<std::unordered_map<double, double> > graph(n);

    // // // UNCOMMENT FOR 4-D COORDINATE EXAMPLE
    // vector<four_coordinate > locs;
    // for (int i = 0; i < n; i++) {
    //     four_coordinate loc = {.a = (double) rand() / RAND_MAX, .b = (double) rand() / RAND_MAX, .c = (double) rand() / RAND_MAX, .d = (double) rand() / RAND_MAX};
    //     locs.push_back(loc);
    // }
    // int count = 0;
    // for (int u = 0; u < n; u++) {
    //     for (int v = u + 1; v < n; v++) {
    //         double weight = abs(locs[u].a - locs[v].a) + abs(locs[u].b - locs[v].b) + abs(locs[u].c - locs[v].c) + abs(locs[u].d - locs[v].d);
    //         if (weight < 2.1 * pow(n,-.238)) {
    //             weight = sqrt(pow(locs[u].a - locs[v].a, 2) + pow(locs[u].b - locs[v].b, 2) + pow(locs[u].c - locs[v].c, 2) + pow(locs[u].d - locs[v].d, 2));
    //             graph[u].insert(make_pair(v, weight));
    //             count++;
    //         }
    //     }
    // }
    
    // //UNCOMMENT FOR 3-D COORDINATE EXAMPLE
    
    //  vector<three_coordinate > locs;
     
    //  for (int i = 0; i < n; i++) {
    //      three_coordinate loc = {.x = (double) rand() / RAND_MAX, .y = (double) rand() / RAND_MAX, .z = (double) rand() / RAND_MAX};
    //      locs.push_back(loc);
    //  }
    //  double sqrt3 = sqrt(3);
    //  int count = 0;
    //  for (int u = 0; u < n; u++) {
    //      for (int v = u + 1; v < n; v++) {
    //          double manhattan = abs(locs[u].x - locs[v].x) + abs(locs[u].y - locs[v].y) + abs(locs[u].z - locs[v].z);
    //          double weight = manhattan;
    //           if (weight < 2.12 * pow(n, -.328)) {
                
    //             weight = sqrt(pow(locs[u].x - locs[v].x, 2) + pow(locs[u].y - locs[v].y, 2) + pow(locs[u].z - locs[v].z, 2));
    //             graph[u].insert(make_pair(v, weight));
    //             count++;
    //          }
    //      }
    //  }
     

    // UNCOMMENT FOR 2-D COORDINATE EXAMPLE
    // vector<pair<double, double> > locs;
    // for (int i = 0; i < n; i++) {
    //     pair<double, double> loc((double) rand() / RAND_MAX, (double) rand() / RAND_MAX);
    //     locs.push_back(loc);
    // }
    // int count = 0;
    // for (int u = 0; u < n; u++) {
    //     for (int v = u + 1; v < n; v++) {
    //         double weight = sqrt(pow(locs[u].first - locs[v].first, 2) + pow(locs[u].second - locs[v].second, 2));
    //         if (weight < 1.74*pow(n,-0.489)) {
    //             graph[u].insert(make_pair(v, weight));
    //             count++;
    //         }
    //     }
    // }

     //UNCOMMENT FOR 0-D COORDINATE EXAMPLE
    int count = 0;
    for (int u = 0; u < n; u++) {
         for (int v = u + 1; v < n; v++) {
             double weight = (double) rand() / RAND_MAX;
             if (weight < 4.01 * pow(n,-0.998)) {
                 graph[u].insert(make_pair(v, weight));
                // graph[v].insert(make_pair(u, weight));
                 count++;
             }     
         }
     }

    printf("%i ", count);

    return graph;
}


int main() {
    int numTrials = 5;
    int maxN = 262144;
    vector<double> nValues;
    vector<double> avgWeights;
    for (int n = 128; n <= 32768; n *= 2) {
        double avgWeight = 0;
        for (int i = 0; i < numTrials; i++) {
            vector<std::unordered_map<double, double> > graph = generateCompleteGraph(n);
            vector<std::unordered_map<double, double> > mst = kruskalMST(graph);
            double total_weight = 0;
            for (int u = 0; u < n; u++) {
                std::__1::unordered_map<double, double>::iterator testing = mst[u].begin();
                while (testing != mst[u].end()) {
                    total_weight += testing->second; // take the square root of the squared weight
                    testing++;
                }
            }
            avgWeight += total_weight;
        }
        avgWeight /= numTrials;
        nValues.push_back(n);
        avgWeights.push_back(avgWeight);
        cout << "n " << n << " " << avgWeight << endl;
    }

    return 0;

}

