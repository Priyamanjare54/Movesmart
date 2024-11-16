#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
using namespace std;

typedef pair<int, int> pii; // {distance, node}

// Structure to represent a traffic signal
struct TrafficSignal {
    int id;                // Intersection ID
    int trafficLoad;       // Current traffic load at the intersection
};

// Function to simulate traffic signal control
void manageTrafficSignals(priority_queue<pii, vector<pii>, greater<pii>>& pq, 
                          unordered_map<int, TrafficSignal>& signals) {
    cout << "\n--- Traffic Signal Management ---\n";
    while (!pq.empty()) {
        int id = pq.top().second; // Intersection ID with the highest priority
        pq.pop();
        cout << "Green light at Intersection " << id 
             << " (Traffic Load: " << signals[id].trafficLoad << ")\n";
        signals[id].trafficLoad -= 5; // Reduce traffic after green light
    }
}

// Dijkstra's Algorithm for shortest path
void dijkstra(int src, vector<vector<pii>>& adj, int V) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Output the shortest distance to all nodes
    cout << "\n--- Shortest Path Calculation ---\n";
    for (int i = 0; i < V; ++i) {
        cout << "Distance from Intersection " << src << " to " << i 
             << " is " << (dist[i] == INT_MAX ? -1 : dist[i]) << "\n";
    }
}

// Main simulation function
int main() {
    int V = 5; // Number of intersections
    vector<vector<pii>> adj(V);

    // Define road network
    adj[0].push_back({1, 4}); // Road from 0 to 1 with weight 4
    adj[0].push_back({2, 2}); // Road from 0 to 2 with weight 2
    adj[1].push_back({3, 5});
    adj[2].push_back({1, 1});
    adj[2].push_back({3, 8});
    adj[3].push_back({4, 6});

    // Traffic signals and their initial load
    unordered_map<int, TrafficSignal> signals = {
        {0, {0, 10}},
        {1, {1, 20}},
        {2, {2, 15}},
        {3, {3, 25}},
        {4, {4, 10}}
    };

    // Priority queue for traffic signals
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (auto& signal : signals) {
        pq.push({signal.second.trafficLoad, signal.second.id});
    }

    // Manage traffic signals
    manageTrafficSignals(pq, signals);

    // Find shortest paths
    dijkstra(0, adj, V);

    return 0;
}

