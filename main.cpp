//Kit Pollinger
//210 lab 34 | Net Graph
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Changed Size from 7 to 12
const int SIZE = 12; //Components in the network
/*
struct Edge {
    int src, dest, weight;
};
*/

//For Step 3
struct Edge {
    int src, dest, capacity; // capacity in Mw(Kilowatt)
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

/*
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
    */
//Step 3
class PowerGrid {
public:
    vector<vector<Pair>> adjList;
    vector<string> componentNames; // Descriptions for each vertex

    // Constructor
    PowerGrid(vector<Edge> const &edges, vector<string> const &names) {
        adjList.resize(SIZE);
        componentNames = names;

        // Build adjacency list
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int capacity = edge.capacity;

            adjList[src].push_back(make_pair(dest, capacity));
            adjList[dest].push_back(make_pair(src, capacity)); // Undirected
        }
    }

/*
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
*/

// Print the network's adjacency list
    void printGrid() {
        cout << "Electrical Network Topology:\n================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << componentNames[i] << " connects to:\n";
            for (Pair v : adjList[i]) {
                cout << "   " << componentNames[v.first] 
                     << " (Transmission Capacity: " << v.second << " MW)\n";
            }
            cout << endl;
        }
    }

    void DFSsearch(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << "Inspecting " << componentNames[v] << endl;

        for (auto &neighbor : adjList[v]) {
            int next = neighbor.first;
            if (!visited[next]) {
                DFSsearch(next, visited);
            }
        }
    }

    void tracePowerFlow(int start) {
        vector<bool> visited(adjList.size(), false);
        cout << "\nTracing Power Flow (DFS) from " << componentNames[start] << ":\n";
        cout << "=======================================\n";
        DFSsearch(start, visited);
        cout << endl;
    }

    void analyzeServiceAreas(int start) {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "Layer-by-Layer Network Inspection (BFS) from " 
             << componentNames[start] << ":\n";
        cout << "=================================================\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << "Checking " << componentNames[v] << endl;

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    cout << "   Next service area: " << componentNames[next] 
                         << " (Transmission Capacity: " << neighbor.second << " MW)\n";
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
        /*
        {0,1,15},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{4,5,9},{2,4,4},
        //adding 6 new nodes
        {6, 7, 10}, {6, 8, 15}, {6, 9, 5},{7, 6, 10}, {7, 8, 3}, {7, 10, 7},
        {8, 6, 15}, {8, 7, 3}, {8, 9, 7},{9, 6, 5}, {9, 8, 7}, {9, 10, 2},
        {10, 9, 2}, {10, 7, 7}, {10, 11, 3},{11, 10, 3}
        */

        //Edges of Graph for Electrical
        {0, 1, 150}, {0, 2, 300}, {1, 3, 100}, {1, 4, 200},{2, 5, 250}, {3, 6, 50}, {4, 6, 70},
        //adding 6 new nodes
        {5, 7, 180},{6, 8, 90}, {7, 9, 300}, {8, 10, 120}, {9, 11, 200},
        {10, 11, 150}, {2, 9, 220}, {4, 10, 160}, {1, 8, 110}
    };

    // Component descriptions
    vector<string> names = {
        "Power Plant A", "Substation B", "Substation C", "Residential Area D",
        "Commercial Area E", "Substation F", "Transformer G", "Industrial Park H",
        "Residential Area I", "Substation J", "Transformer K", "Commercial Area L"
    };

    /*
    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    //DFS and BFS
    graph.DFS(0);
    graph.BFS(0);
    */

   // Create the power grid
    PowerGrid grid(edges, names);

    // Print the grid structure
    grid.printGrid();
    // Trace power flow (DFS)
    grid.tracePowerFlow(0);
    // Analyze service areas (BFS)
    grid.analyzeServiceAreas(0);

    return 0;
}
