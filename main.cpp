//Kit Pollinger
//210 lab 34 | Net Graph
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//Changed Size from 7 to 12
const int SIZE = 12; 

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
    void DFSsearch(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto &neighbor : adjList[v]) {
            int next = neighbor.first;
            if (!visited[next]) {
                DFSsearch(next, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(adjList.size(), false);
        cout << "DFS starting from vertex " << start << ":\n";
        DFSsearch(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from vertex " << start << ":\n";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
        cout << endl;
    }
    
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        //Change weight from {0,1,12} - {0,1,15}
        //Removed 2 Nodes {5,6,6} / {2,5,5}
        //7 Nodes (9 Original)
        {0,1,15},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{4,5,9},{2,4,4},
        //adding 6 new nodes
        {6, 7, 10}, {6, 8, 15}, {6, 9, 5},{7, 6, 10}, {7, 8, 3}, {7, 10, 7},
        {8, 6, 15}, {8, 7, 3}, {8, 9, 7},{9, 6, 5}, {9, 8, 7}, {9, 10, 2},
        {10, 9, 2}, {10, 7, 7}, {10, 11, 3},{11, 10, 3}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    //DFS and BFS
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
