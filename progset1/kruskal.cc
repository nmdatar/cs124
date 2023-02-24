#include <iostream>
#include <vector>
#include <limits>
#include <float.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

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
    sort(edges.begin(), edges.end(), compareEdges);

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

    // double max = DBL_MIN;
    // for (int i = 0; i < n; i++) {
    //     std::__1::unordered_map<double, double>::iterator it = mst[i].begin();
    //     while (it != mst[i].end()) {
    //         if (it->second > max) {
    //             max = it->second;
    //         }
    //         it++;
    //     }
    // }

    // printf("%f ", max);

    return mst;
}

vector<std::unordered_map<double, double> > generateCompleteGraph(int n) {
    vector<std::unordered_map<double, double> > graph(n);
    int count = 0;
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            double weight = (double) rand() / RAND_MAX;
            // if (n <= 1024 && weight < .05 - 4.19153e-05 * n) {
            //     graph[u].insert(make_pair(v, weight));
            //     graph[v].insert(make_pair(u, weight));
            //     count++;
            // }
            if (weight < .002 / ((double ) n / 2048)) {
                graph[u].insert(make_pair(v, weight));
                graph[v].insert(make_pair(u, weight));
                count++;
            }     
        }
    }

    printf("%i ", count);

    return graph;
}


int main() {
    int numTrials = 1;
    int maxN = 262144;
    vector<double> nValues;
    vector<double> avgWeights;
    for (int n = 262144; n <= maxN; n *= 2) {
        double avgWeight = 0;
        for (int i = 0; i < numTrials; i++) {
            vector<std::unordered_map<double, double> > graph = generateCompleteGraph(n);
            vector<std::unordered_map<double, double> > mst = kruskalMST(graph);
            double weight = 0;
            for (int u = 0; u < n; u++) {
                std::__1::unordered_map<double, double>::iterator  testing = mst[u].begin();
                while (testing != mst[u].end()) {
                    weight += testing->second;
                    testing++;
                }
                // for (int v = 0; v < n; v++) {
                //     weight += mst[u][v];
                // }
            }
            avgWeight += weight;
        }
        avgWeight /= numTrials;
        nValues.push_back(n);
        avgWeights.push_back(avgWeight);
        cout << "n " << n << " " << avgWeight << endl;
    }

    return 0;

}
