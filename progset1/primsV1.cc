#include <iostream>
#include <vector>
#include <limits>
#include <float.h>
#include <unordered_map>
#include <math.h>

using namespace std;

struct Node {
    int index;
    double distance;
    
    Node(int index, double distance) {
        this->index = index;
        this->distance = distance;
    }
};

class BinaryHeapQueue {
private:
    vector<Node> heap;
    int size;

    void swap(int i, int j) {
        Node temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int i) {
        int parent = (i - 1) / 2;
        if (i > 0 && heap[i].distance < heap[parent].distance) {
            swap(i, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < size && heap[left].distance < heap[smallest].distance) {
            smallest = left;
        }
        if (right < size && heap[right].distance < heap[smallest].distance) {
            smallest = right;
        }
        if (smallest != i) {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

public:
    BinaryHeapQueue() {
        size = 0;
    }

    void push(int index, double distance) {
        Node newNode = Node(index, distance);
        heap.push_back(newNode);
        size++;
        heapifyUp(size - 1);
    }

    int pop() {
        if (size == 0) {
            return -1;
        }
        int index = heap[0].index;
        heap[0] = heap[size - 1];
        size--;
        heap.pop_back();
        heapifyDown(0);
        return index;
    }

    bool isEmpty() {
        return size == 0;
    }
};

vector<std::unordered_map<double, double> > primMST(const vector<std::unordered_map<double, double> >& graph) {
    int n = graph.size();
    vector<std::unordered_map<double, double> > mst(n);  // The minimum spanning tree
    vector<double> dist(n, numeric_limits<double>::max());  // The distance to each vertex from the current tree
    vector<bool> visited(n, false);  // Whether each vertex has been visited
    vector<int> parent(n, -1);  // The parent of each vertex in the minimum spanning tree
    BinaryHeapQueue pq;  // The vertices to visit

    // Start with vertex 0 and initialize distances and priority queue
    dist[0] = 0;
    pq.push(0, 0);

    while (!pq.isEmpty()) {
        // Get the next vertex to visit
        int u = pq.pop();

        // Add u to the minimum spanning tree
        visited[u] = true;
        if (parent[u] != -1) {  // We don't need to add an edge for the root vertex
            if (u < parent[u]) {  // add the edge only once, based on its direction
                if (graph[u].find(parent[u]) != graph[u].end()) {
                    mst[u].insert(make_pair(parent[u], graph[u].find(parent[u])->second));
                }
            } else {
                if (graph[parent[u]].find(u) != graph[parent[u]].end()){
                mst[parent[u]].insert(make_pair(u, graph[parent[u]].find(u)->second));
            }
             // mst[parent[u]][u] = graph[parent[u]][u];
            
        }
}

        // Update distances and priority queue for adjacent vertices
        for (int v = 0; v < n; v++) {
            if (v != u && !visited[v] && graph[u].find(v) != graph[u].end() && graph[u].find(v)->second < dist[v]) {
                dist[v] = graph[u].find(v)->second;
                pq.push(v, dist[v]);
                parent[v] = u;
            }
        }
    }

    // double max = DBL_MIN;
    // for (int i=0; i<n; i++) {
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
    int maxN = 65536;
    vector<double> nValues;
    vector<double> avgWeights;
    for (int n = 65536; n <= maxN; n *= 2) {
        double avgWeight = 0;
        for (int i = 0; i < numTrials; i++) {
            vector<std::unordered_map<double, double> > graph = generateCompleteGraph(n);
            vector<std::unordered_map<double, double> > mst = primMST(graph);
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
