// Kit Pollinger
// 210 lab 34 | Net Graph
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

const int SIZE = 12;                        // Updated to 13 nodes
const int INF = numeric_limits<int>::max(); // Dijkstra's Algorithm

struct Edge
{
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Alias for pair<int, int>

class Graph
{
public:
    vector<vector<Pair>> adjList;  // Adjacency list representation of the graph
    vector<string> componentNames; // Names/descriptions for nodes (Step 3)

    // Constructor to initialize the graph with edges
    Graph(vector<Edge> const &edges, vector<string> const &names)
    {
        adjList.resize(SIZE);
        componentNames = names;

        for (auto &edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight)); // Undirected graph
        }
    }
    // Print the adjacency list
    void printGraph()
    {
        cout << "Step 1 - 2\n";
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
                cout << endl;
        }
    }
    // Print electrical network topology with component names (Step 3)
    void printGrid()
    {
        cout << "Step 3\n";
        cout << "Electrical Network Topology:\n================================\n";
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << componentNames[i] << " connects to:\n";
            for (Pair v : adjList[i])
            {
                cout << "   " << componentNames[v.first]
                     << " (Transmission Capacity: " << v.second << " MW)\n";
            }
            cout << endl;
        }
    }
    // DFS Traversal
    void DFSsearch(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        for (auto &neighbor : adjList[v])
        {
            int next = neighbor.first;
            if (!visited[next])
            {
                DFSsearch(next, visited);
            }
        }
    }
    void DFS(int start)
    {
        vector<bool> visited(adjList.size(), false);
        cout << "DFS starting from vertex " << start << ":\n";
        DFSsearch(start, visited);
        cout << endl;
    }
    // BFS Traversal
    void BFS(int start)
    {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from vertex " << start << ":\n";
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &neighbor : adjList[v])
            {
                int next = neighbor.first;
                if (!visited[next])
                {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
        cout << endl;
    }

    // Trace power flow using DFS (Step 3)
    void tracePowerFlow(int start)
    {
        vector<bool> visited(adjList.size(), false);
        cout << "\nTracing Power Flow (DFS) from " << componentNames[start] << ":\n";
        cout << "=======================================\n";
        DFSsearch(start, visited);
        cout << endl;
    }

    // Analyze service areas layer-by-layer using BFS (Step 3)
    void analyzeServiceAreas(int start)
    {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "Layer-by-Layer Network Inspection (BFS) from "
             << componentNames[start] << ":\n";
        cout << "=================================================\n";

        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << "Checking " << componentNames[v] << endl;

            for (auto &neighbor : adjList[v])
            {
                int next = neighbor.first;
                if (!visited[next])
                {
                    cout << "   Next service area: " << componentNames[next]
                         << " (Transmission Capacity: " << neighbor.second << " MW)\n";
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
        cout << endl;
    }
    // Shortest Path using Dijkstra's Algorithm
    void findShortestPaths(int start)
    {
        vector<int> dist(SIZE, INF); // Initialize distances to all nodes as infinity
        dist[start] = 0;

        // Priority queue to store (distance, vertex) pairs
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            // If the distance in the priority queue is outdated, skip processing
            if (currentDist > dist[currentNode])
                continue;

            // Process all neighbors of the current node
            for (auto &neighbor : adjList[currentNode])
            {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                // Relaxation step
                if (dist[currentNode] + edgeWeight < dist[nextNode])
                {
                    dist[nextNode] = dist[currentNode] + edgeWeight;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        // Print shortest paths
        cout << "Step 4" << endl;
        cout << "Shortest path from node " << start << ":\n";
        for (int i = 0; i < SIZE; i++)
        {
            cout << start << " -> " << i << " : ";
            if (dist[i] == INF)
                cout << "INF";
            else
                cout << dist[i];
            cout << endl;
        }
    }

    //MST
    //Spanning Tree
    void FindMST(){
        {
        //Change all edges into a single list
        vector<Edge> allEdges;
        for (int i = 0; i < adjList.size(); i++)
        {
            for (auto &neighbor : adjList[i])
            {
                if (i < neighbor.first) // Avoid duplicating edges in undirected graph
                    allEdges.push_back({i, neighbor.first, neighbor.second});
            }
        }

        // Sort edges by weight
        sort(allEdges.begin(), allEdges.end(), [](Edge const &a, Edge const &b)
             { return a.weight < b.weight; });

        // Union-Find setup
        vector<int> parent(SIZE), rank(SIZE, 0);
        for (int i = 0; i < SIZE; i++)
            parent[i] = i;

        function<int(int)> find = [&](int v)
        {
            if (v == parent[v])
                return v;
            return parent[v] = find(parent[v]); // Path compression
        };

        auto unionSets = [&](int u, int v)
        {
            u = find(u), v = find(v);
            if (u != v)
            {
                if (rank[u] < rank[v])
                    swap(u, v);
                parent[v] = u;
                if (rank[u] == rank[v])
                    rank[u]++;
            }
        };

        // Step 4: Build MST using Kruskal's Algorithm
        vector<Edge> mstEdges;
        for (auto &edge : allEdges)
        {
            if (find(edge.src) != find(edge.dest))
            {
                mstEdges.push_back(edge);
                unionSets(edge.src, edge.dest);
            }
        }

        // Step 5: Print the MST edges
        cout << "Step 5\nMinimum Spanning Tree edges:\n";
        for (auto &edge : mstEdges)
        {
            cout << "Edge from " << componentNames[edge.src]
                 << " to " << componentNames[edge.dest]
                 << " with capacity: " << edge.weight << " units\n";
        }
        cout << endl;
        }
    }

};

int main()
{
    // Define edges for the graph
    vector<Edge> edges = {
        // Original edges (Step 1)
        /*
        // Creates a vector of graph edges/weights
        vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        original nodes
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
        };
        */
        //Removed Nodes {2,5,5} and {5,6,6}
        {0, 1, 15},{0, 2, 8},{0, 3, 21},{2, 3, 6},{2, 6, 2},{4, 5, 9},{2, 4, 4},
        // adding 6 new nodes
        {7, 8, 10},{9, 10, 11},{11, 1, 7},{1, 8, 13},{3, 9, 14},{6, 7, 15},
        // Nodes for Step 3
        {0, 1, 150},{0, 2, 300},{1, 3, 100},{1, 4, 200},{2, 5, 250},{3, 6, 50},{4, 6, 70}
        };

    // Define component descriptions for Step 3
    vector<string> names = {
        "Power Plant A", "Substation B", "Substation C", "Residential Area D",
        "Commercial Area E", "Substation F", "Transformer G", "Industrial Park H",
        "Residential Area I", "Substation J", "Transformer K", "Power Hub L", "Backup Station M"};

    // Create the graph
    Graph graph(edges, names);

    // Step 1 and Step 2 Outputs
    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    // Step 3 Outputs
    graph.printGrid();
    graph.tracePowerFlow(0);
    graph.analyzeServiceAreas(0);

    // Step 4 Output: Shortest Path
    graph.findShortestPaths(0);
    //Step 5: FindMST
    graph.FindMST();

    //Step 6
    cout << "Step 6\n";
    cout << "Electrical Network Menu:\n";
    int choice;
    while (choice != 0){
        cout << "[1] Electrical network topology\n"
        << "[2] Check contaminant spread (BFS)\n"
        << "[3] Plan inspection route (DFS)\n"
        << "[4] Calculate shortest paths\n"
        << "[5] Find Minimum Spanning Tree\n"
        << "[0] Exit\n"
        << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            graph.printGrid();
            break;
        case 2:
            graph.BFS(0);
            break;
        case 3:
            graph.DFS(0);
            break;
        case 4:
            graph.findShortestPaths(0);
            break;
        case 5:
            graph.FindMST();
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}

