//MSSV: 22520544
//Full name: Huynh Tran Quoc Huy

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <limits>
#include <algorithm>
#include <utility>
#include <functional>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

//Session 01 - Exercise 01
//Notes or Remarks: Implementing graph using adjacency list and matrix
class GraphAL {
private:
    int V; // Number of vertices
    list<int>* adj; // Adjacency list
public:
    GraphAL(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    void printGraph() {
        for (int v = 0; v < V; ++v) {
            cout << "Adjacency list of vertex " << v << "\n head ";
            for (auto x : adj[v])
                cout << "-> " << x;
            printf("\n");
        }
    }
    list<int>* getAdj() {
        return adj;
    }
    int getV() {
        return V;
    }
};

// Graph representation using adjacency matrix
class GraphAM {
private:
    int V; // Number of vertices
    int** adj; // Adjacency matrix
public:
    GraphAM(int V) {
        this->V = V;
        adj = new int* [V];
        for (int i = 0; i < V; ++i) {
            adj[i] = new int[V];
            for (int j = 0; j < V; ++j)
                adj[i][j] = 0;
        }
    }
    void addEdge(int v, int w) {
        adj[v][w] = 1;
    }
    void addEdge(int v, int w, int weight) {
        adj[v][w] = weight;
        adj[w][v] = weight; // Assuming undirected roads
    }
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j)
                cout << adj[i][j] << " ";
            cout << endl;
        }
    }
    int** getAdj() {
        return adj;
    }
    int getV() {
        return V;
    }
};

//Session 01 - Exercise 02
//Notes or Remarks: Depth-first search (DFS) recursive and iterative
void DFS_Recursive(GraphAL& g, int s, vector<bool>& visited) {
    visited[s] = true;
    cout << s << " ";
    for (auto u : g.getAdj()[s]) {
        if (!visited[u])
            DFS_Recursive(g, u, visited);
    }
}

void DFS_Iterative(GraphAL& g, int s) {
    vector<bool> visited(g.getV(), false);
    stack<int> stack;
    stack.push(s);
    visited[s] = true;
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
        cout << u << " ";
        for (auto v : g.getAdj()[u]) {
            if (!visited[v]) {
                stack.push(v);
                visited[v] = true;
            }
        }
    }
}

//Session 01 - Exercise 03
//Notes or Remarks: Breadth-first search (BFS)
vector<int> BFS(GraphAL& g, int s) {
    vector<bool> visited(g.getV(), false);
    vector<int> order;
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (auto v : g.getAdj()[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
        }
    }
    return order;
}

//Session 01 - Exercise 04
//Notes or Remarks: Detecting cycles in directed graphs
bool isCyclicDirectedDFS(GraphAL& g, int u, vector<bool>& visited, vector<bool>& recStack) {
    if (recStack[u])
        return true;
    if (visited[u])
        return false;
    visited[u] = true;
    recStack[u] = true;
    for (auto v : g.getAdj()[u])
        if (isCyclicDirectedDFS(g, v, visited, recStack))
            return true;
    recStack[u] = false;
    return false;
}
bool isCyclicDirected(GraphAL& g) {
    int V = g.getV();
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            if (isCyclicDirectedDFS(g, i, visited, recStack))
                return true;
    return false;
}
//Session 01 - Exercise 04
//Notes or Remarks: Detecting cycles in undirected graphs
bool isCyclicUndirectedDFS(GraphAL& g, int u, int parent, vector<bool>& visited) {
    visited[u] = true;
    for (auto v : g.getAdj()[u]) {
        if (!visited[v]) {
            if (isCyclicUndirectedDFS(g, v, u, visited))
                return true;
        }
        else if (v != parent)
            return true;
    }
    return false;
}
bool isCyclicUndirected(GraphAL& g) {
    int V = g.getV();
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            if (isCyclicUndirectedDFS(g, i, -1, visited))
                return true;
    return false;
}

//Session 01 - Exercise 05
//Notes or Remarks: Dijkstra's algorithm for shortest path
int minDistance(vector<int>& dist, vector<bool>& sptSet, int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; ++v) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

vector<int> Dijkstra(GraphAM& g, int src) {
    int V = g.getV();
    vector<int> dist(V, INT_MAX);
    vector<bool> sptSet(V, false);
    dist[src] = 0;
    for (int count = 0; count < V - 1; ++count) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;
        for (int v = 0; v < V; ++v) {
            if (!sptSet[v] && g.getAdj()[u][v] && dist[u] != INT_MAX && dist[u] + g.getAdj()[u][v] < dist[v])
                dist[v] = dist[u] + g.getAdj()[u][v];
        }
    }
    return dist;
}

//Session 01 - Exercise 06
//Notes or Remarks: Finding connected components
void DFS_ConnectedComponents(GraphAL& g, int u, vector<bool>& visited, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (auto v : g.getAdj()[u]) {
        if (!visited[v])
            DFS_ConnectedComponents(g, v, visited, component);
    }
}
vector<vector<int>> findConnectedComponents(GraphAL& g) {
    int V = g.getV();
    vector<bool> visited(V, false);
    vector<vector<int>> components;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            vector<int> component;
            DFS_ConnectedComponents(g, i, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

//Session 01 - Exercise 07
//Notes or Remarks: Finding bridges in an undirected graph
void findBridges(GraphAL& g, int u, int parent, vector<int>& disc, vector<int>& low, vector<bool>& visited, vector<pair<int, int>>& bridges) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    visited[u] = true;
    for (auto v : g.getAdj()[u]) {
        if (!visited[v]) {
            findBridges(g, v, u, disc, low, visited, bridges);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
                bridges.push_back({ u, v });
        }
        else if (v != parent)
            low[u] = min(low[u], disc[v]);
    }
}

void findBridgesUtil(GraphAL& g, vector<pair<int, int>>& bridges) {
    int V = g.getV();
    vector<bool> visited(V, false);
    vector<int> disc(V, -1);
    vector<int> low(V, -1);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            findBridges(g, i, -1, disc, low, visited, bridges);
        }
    }
}

//Session 01 - Exercise 08
//Notes or Remarks: Louvain method for community detection
double modularity(GraphAL& g, const vector<int>& community) {
    double m = 0; // Total number of edges
    for (int i = 0; i < g.getV(); ++i) {
        m += g.getAdj()[i].size();
    }
    m /= 2.0; // Since edges are counted twice

    double Q = 0;
    for (int i = 0; i < g.getV(); ++i) {
        for (int j : g.getAdj()[i]) {
            if (community[i] == community[j]) {
                Q += (1.0 - (g.getAdj()[i].size() * g.getAdj()[j].size()) / (2.0 * m));
            }
        }
    }
    Q /= (2.0 * m);
    return Q;
}


vector<int> louvainIteration(GraphAL& g, const vector<int>& community) {
    double m = 0; // Total number of edges
    for (int i = 0; i < g.getV(); ++i) {
        m += g.getAdj()[i].size();
    }
    m /= 2.0; // Since edges are counted twice

    int V = g.getV();
    vector<int> newCommunity(V);
    vector<double> deltaQ(V, 0.0);

    // Assign initial community to each node
    for (int i = 0; i < V; ++i) {
        newCommunity[i] = community[i];
    }

    // Calculate deltaQ for each node moving to its neighbors' communities
    for (int i = 0; i < V; ++i) {
        for (int j : g.getAdj()[i]) {
            if (newCommunity[i] != newCommunity[j]) {
                double deltaQ_ij = 0;
                for (int k : g.getAdj()[i]) {
                    if (newCommunity[k] == newCommunity[j]) {
                        deltaQ_ij += 1.0;
                    }
                }
                for (int k : g.getAdj()[j]) {
                    if (newCommunity[k] == newCommunity[i]) {
                        deltaQ_ij += 1.0;
                    }
                }
                deltaQ_ij -= 2.0 * (g.getAdj()[i].size() * g.getAdj()[j].size()) / (2.0 * m);
                if (deltaQ_ij > deltaQ[i]) {
                    deltaQ[i] = deltaQ_ij;
                    newCommunity[i] = newCommunity[j];
                }
            }
        }
    }

    return newCommunity;
}

vector<int> louvain(GraphAL& g) {
    int V = g.getV();
    vector<int> community(V);
    for (int i = 0; i < V; ++i) {
        community[i] = i; // Initially each node is in its own community
    }

    double prevQ = -1.0;
    double currQ = modularity(g, community);

    while (currQ > prevQ) {
        prevQ = currQ;
        community = louvainIteration(g, community);
        currQ = modularity(g, community);
    }

    return community;
}

//Session 01 - Exercise 09
//Notes or Remarks: PageRank algorithm
vector<double> PageRank(GraphAL& g, int iterations) {
    int V = g.getV();
    vector<double> ranks(V, 1.0 / V); // Initial ranks
    for (int iter = 0; iter < iterations; ++iter) {
        vector<double> newRanks(V, 0.0);
        for (int u = 0; u < V; ++u) {
            for (auto v : g.getAdj()[u]) {
                newRanks[v] += ranks[u] / g.getAdj()[u].size();
            }
        }
        ranks = newRanks;
    }
    return ranks;
}

//Session 01 - Exercise 10
//Notes or Remarks: Efficient Dijkstra's algorithm
vector<int> Dijkstra_PQ(GraphAM& g, int src) {
    int V = g.getV();
    vector<int> dist(V, INT_MAX);
    vector<bool> sptSet(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, src });
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        sptSet[u] = true;
        for (int v = 0; v < V; ++v) {
            if (!sptSet[v] && g.getAdj()[u][v] && dist[u] != INT_MAX && dist[u] + g.getAdj()[u][v] < dist[v]) {
                dist[v] = dist[u] + g.getAdj()[u][v];
                pq.push({ dist[v], v });
            }
        }
    }
    return dist;
}

vector<int> findOptimalDeliveryRoute(GraphAM& g, vector<int>& deliveryPoints) {
    int V = g.getV();
    int start = deliveryPoints[0]; // Starting point
    vector<int> route;
    route.push_back(start);

    while (!deliveryPoints.empty()) {
        int current = route.back();
        deliveryPoints.erase(find(deliveryPoints.begin(), deliveryPoints.end(), current)); // Remove current from list

        if (deliveryPoints.empty()) {
            break;
        }

        // Find the closest next delivery point
        int minDistance = INT_MAX;
        int nextPoint = -1;
        vector<int> distances = Dijkstra(g, current);

        for (int i = 0; i < V; ++i) {
            if (find(deliveryPoints.begin(), deliveryPoints.end(), i) != deliveryPoints.end() && distances[i] < minDistance) {
                minDistance = distances[i];
                nextPoint = i;
            }
        }

        route.push_back(nextPoint);
    }

    return route;
}

class SocialNetwork {
private:
    int V; // Number of users
    list<int>* adj; // Adjacency list (representing friendships)

public:
    SocialNetwork(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    int getV() {
        return V;
    }
    void addFriendship(int user1, int user2) {
        adj[user1].push_back(user2);
        adj[user2].push_back(user1); // Undirected graph for friendships
    }

    // Degree centrality (number of friends)
    vector<int> degreeCentrality() {
        vector<int> degrees(V, 0);
        for (int i = 0; i < V; ++i) {
            degrees[i] = adj[i].size();
        }
        return degrees;
    }

    // Betweenness centrality (calculates betweenness centrality for all nodes)
    vector<double> betweennessCentrality() {
        vector<double> betweenness(V, 0.0);
        for (int s = 0; s < V; ++s) {
            vector<int> predecessors(V, -1);
            vector<int> distances(V, INT_MAX);
            vector<int> sigma(V, 0);
            vector<double> delta(V, 0.0);

            // Breadth-First Search (BFS) from source node s
            queue<int> q;
            q.push(s);
            distances[s] = 0;
            sigma[s] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (distances[v] == INT_MAX) {
                        q.push(v);
                        distances[v] = distances[u] + 1;
                    }
                    if (distances[v] == distances[u] + 1) {
                        sigma[v] += sigma[u];
                        predecessors[v] = u;
                    }
                }
            }

            // Calculate dependency for each node
            for (int w = 0; w < V; ++w) {
                if (w != s && distances[w] != INT_MAX) {
                    delta[predecessors[w]] += (sigma[predecessors[w]] / sigma[w]) * (1 + delta[w]);
                }
            }

            // Accumulate betweenness centrality for each node
            for (int i = 0; i < V; ++i) {
                if (i != s) {
                    betweenness[i] += delta[i];
                }
            }
        }

        // Normalize betweenness centrality
        for (int i = 0; i < V; ++i) {
            betweenness[i] /= ((V - 1) * (V - 2));
        }

        return betweenness;
    }

    // Louvain community detection (simplified version)
    vector<int> louvain() {
        int V = this->V;
        vector<int> community(V);
        for (int i = 0; i < V; ++i) {
            community[i] = i; // Initially each node is in its own community
        }

        // (Simplified) One iteration of Louvain 
        for (int i = 0; i < V; ++i) {
            int bestCommunity = community[i];
            double bestModularityGain = 0.0;
            for (int neighbor : adj[i]) {
                if (community[i] != community[neighbor]) {
                    // Calculate potential modularity gain (simplified)
                    double gain = 0.0;
                    // (Actual modularity calculation would be more complex)
                    gain += adj[i].size();
                    gain -= adj[neighbor].size();
                    if (gain > bestModularityGain) {
                        bestModularityGain = gain;
                        bestCommunity = community[neighbor];
                    }
                }
            }
            if (bestCommunity != community[i]) {
                community[i] = bestCommunity;
            }
        }

        return community;
    }
};

//Session 01 - Exercise 11
//Notes or Remarks: Route planning for delivery service
class RoadNetwork {
private:
    int V; // Number of intersections (vertices)
    list<pair<int, int>>* adj; // Adjacency list (intersection, travel time)
public:
    RoadNetwork(int V) {
        this->V = V;
        adj = new list<pair<int, int>>[V];
    }
    void addRoad(int u, int v, int travelTime) {
        adj[u].push_back(make_pair(v, travelTime));
        adj[v].push_back(make_pair(u, travelTime)); // Assuming undirected graph
    }
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, src));
        dist[src] = 0;
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = (*i).first;
                int weight = (*i).second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;
    }
    void findBottlenecks() {
        for (int i = 0; i < V; ++i) {
            vector<int> dist = dijkstra(i);
            for (int j = 0; j < V; ++j) {
                if (dist[j] == INT_MAX) {
                    cout << "Bottleneck detected between intersections " << i << " and " << j << endl;
                }
            }
        }
    }
    void suggestTrafficLightTimings() {
        for (int i = 0; i < V; ++i) {
            vector<int> dist = dijkstra(i);
            for (int j = 0; j < V; ++j) {
                if (dist[j] != INT_MAX) {
                    cout << "Optimal traffic light timing between intersections " << i << " and " << j << " is " << dist[j] << " seconds" << endl;
                }
            }
        }
    }
    void suggestAlternativeRoutes(int src, int dest) {
        vector<int> dist = dijkstra(src);
        if (dist[dest] == INT_MAX) {
            cout << "No route available from intersection " << src << " to intersection " << dest << endl;
        }
        else {
            cout << "Shortest route from intersection " << src << " to intersection " << dest << " is " << dist[dest] << " seconds" << endl;
        }
    }
};

// Build a recommendation system for an e-commerce platform using collaborative filtering based on user-item interaction graphs to suggest products to users.
class UserItemGraph {
private:
    int numUsers;
    int numItems;
    vector<unordered_set<int>> userItems; // User-item interactions

public:
    UserItemGraph(int numUsers, int numItems) {
        this->numUsers = numUsers;
        this->numItems = numItems;
        userItems.resize(numUsers);
    }

    void addUserItemInteraction(int user, int item) {
        userItems[user].insert(item);
    }

    // Calculate Pearson correlation between two users
    double pearsonCorrelation(int user1, int user2) {
        unordered_set<int> commonItems;
        for (int item : userItems[user1]) {
            if (userItems[user2].count(item) > 0) {
                commonItems.insert(item);
            }
        }

        if (commonItems.size() == 0) {
            return 0.0; // No common items
        }

        double sum1 = 0.0, sum2 = 0.0;
        for (int item : commonItems) {
            sum1 += item;
        }
        double avg1 = sum1 / commonItems.size();

        sum2 = 0.0;
        for (int item : commonItems) {
            sum2 += item;
        }
        double avg2 = sum2 / commonItems.size();

        double numerator = 0.0, denominator1 = 0.0, denominator2 = 0.0;
        for (int item : commonItems) {
            numerator += (item - avg1) * (item - avg2);
            denominator1 += pow(item - avg1, 2);
            denominator2 += pow(item - avg2, 2);
        }

        if (denominator1 == 0 || denominator2 == 0) {
            return 0.0; // Avoid division by zero
        }

        return numerator / (sqrt(denominator1) * sqrt(denominator2));
    }

    // Predict rating for a user-item pair based on user similarities
    double predictRating(int user, int item) {
        double numerator = 0.0, denominator = 0.0;
        for (int otherUser = 0; otherUser < numUsers; ++otherUser) {
            if (otherUser != user && userItems[otherUser].count(item) > 0) {
                double similarity = pearsonCorrelation(user, otherUser);
                numerator += similarity * userItems[otherUser].count(item);
                denominator += abs(similarity);
            }
        }

        if (denominator == 0) {
            return 0.0; // No similar users found
        }

        return numerator / denominator;
    }

    // Recommend items to a user
    vector<int> recommendItems(int user, int numRecommendations) {
        vector<pair<double, int>> predictedRatings;
        for (int item = 0; item < numItems; ++item) {
            if (userItems[user].count(item) == 0) { // Only recommend items not already interacted with
                predictedRatings.push_back({ predictRating(user, item), item });
            }
        }

        sort(predictedRatings.begin(), predictedRatings.end(), greater<pair<double, int>>());

        vector<int> recommendations;
        for (int i = 0; i < numRecommendations; ++i) {
            recommendations.push_back(predictedRatings[i].second);
        }

        return recommendations;
    }
};


class Graph {
private:
    int V; // Number of vertices (devices)
    vector<vector<pair<int, int>>> adjList; // Adjacency list: (neighbor, weight)

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back({ dest, weight });
        adjList[dest].push_back({ src, weight }); // Undirected graph (assuming bidirectional connections)
    }

    // Dijkstra's algorithm to find shortest paths
    vector<int> Dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        set<pair<int, int>> pq; // Priority queue (distance, vertex)
        dist[src] = 0;
        pq.insert({ 0, src });

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());

            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    pq.erase({ dist[v], v }); // Remove old entry if it exists
                    dist[v] = dist[u] + weight;
                    pq.insert({ dist[v], v });
                }
            }
        }

        return dist;
    }

    // Find minimum spanning tree using Prim's algorithm
    vector<pair<int, int>> primMST() {
        vector<bool> inMST(V, false);
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        key[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap
        pq.push({ 0, 0 });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true;

            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({ key[v], v });
                }
            }
        }

        vector<pair<int, int>> mst;
        for (int i = 1; i < V; ++i) {
            mst.push_back({ parent[i], i });
        }

        return mst;
    }

    // Find critical nodes (nodes whose removal increases network diameter significantly)
    vector<int> findCriticalNodes() {
        vector<int> criticalNodes;
        int originalDiameter = 0;

        // Calculate original network diameter
        for (int i = 0; i < V; ++i) {
            vector<int> distances = Dijkstra(i);
            int maxDistance = *max_element(distances.begin(), distances.end());
            originalDiameter = max(originalDiameter, maxDistance);
        }

        for (int i = 0; i < V; ++i) {
            // Create a temporary graph without node 'i'
            Graph tempGraph(V);
            for (int j = 0; j < V; ++j) {
                for (auto neighbor : adjList[j]) {
                    if (j != i && neighbor.first != i) {
                        tempGraph.addEdge(j, neighbor.first, neighbor.second);
                    }
                }
            }

            // Calculate network diameter in the temporary graph
            int newDiameter = 0;
            for (int j = 0; j < V; ++j) {
                if (j != i) { // Exclude the removed node
                    vector<int> distances = tempGraph.Dijkstra(j);
                    int maxDistance = *max_element(distances.begin(), distances.end());
                    newDiameter = max(newDiameter, maxDistance);
                }
            }

            // Check if diameter increased significantly
            if (newDiameter > originalDiameter * 1.5) { // Example threshold
                criticalNodes.push_back(i);
            }
        }

        return criticalNodes;
    }

    // Find bridges (edges whose removal disconnects the graph)
    vector<pair<int, int>> findBridges() {
        vector<pair<int, int>> bridges;
        vector<bool> visited(V, false);
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        int time = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfsBridge(i, -1, visited, disc, low, time, bridges);
            }
        }

        return bridges;
    }

    void dfsBridge(int u, int parent, vector<bool>& visited, vector<int>& disc, vector<int>& low, int& time, vector<pair<int, int>>& bridges) {
        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (auto neighbor : adjList[u]) {
            int v = neighbor.first;
            if (!visited[v]) {
                dfsBridge(v, u, visited, disc, low, time, bridges);
                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    bridges.push_back({ u, v });
                }
            }
            else if (v != parent) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};
//

struct Node {
    int x, y;
    float g, h;
    Node* parent;

    Node(int x, int y, float g, float h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    float f() const {
        return g + h;
    }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

struct NodeHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

vector<pair<int, int>> get_neighbors(const pair<int, int>& pos, const vector<vector<int>>& grid) {
    vector<pair<int, int>> neighbors;
    int x = pos.first, y = pos.second;
    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& dir : directions) {
        int nx = x + dir.first, ny = y + dir.second;
        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == 0) {
            neighbors.emplace_back(nx, ny);
        }
    }

    return neighbors;
}

float heuristic(const pair<int, int>& a, const pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pair<int, int>> reconstruct_path(Node* node) {
    vector<pair<int, int>> path;
    while (node) {
        path.emplace_back(node->x, node->y);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> a_star(const vector<vector<int>>& grid, const pair<int, int>& start, const pair<int, int>& goal) {
    priority_queue<Node, vector<Node>, greater<Node>> open_list;
    unordered_map<pair<int, int>, Node*, NodeHash> all_nodes;

    Node* start_node = new Node(start.first, start.second, 0, heuristic(start, goal));
    open_list.push(*start_node);
    all_nodes[start] = start_node;

    while (!open_list.empty()) {
        Node current = open_list.top();
        open_list.pop();

        if (current.x == goal.first && current.y == goal.second) {
            return reconstruct_path(&current);
        }

        for (const auto& neighbor_pos : get_neighbors({ current.x, current.y }, grid)) {
            float tentative_g = current.g + 1;
            if (all_nodes.find(neighbor_pos) == all_nodes.end() || tentative_g < all_nodes[neighbor_pos]->g) {
                Node* neighbor_node = new Node(neighbor_pos.first, neighbor_pos.second, tentative_g, heuristic(neighbor_pos, goal), all_nodes[{current.x, current.y}]);
                open_list.push(*neighbor_node);
                all_nodes[neighbor_pos] = neighbor_node;
            }
        }
    }

    return {};
}
//
int main() {
    int n;
    cout << "--Exercise 1--\n";
    // Create a graph with 5 vertices
    GraphAL g(5);

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Print the graph
    g.printGraph();

    // Get the adjacency list
    list<int>* adjList = g.getAdj();

    // Accessing adjacency list of vertex 0
    cout << "\nAdjacency list of vertex 0:";
    for (auto x : adjList[0]) {
        cout << " -> " << x;
    }
    cout << endl;

    // Get the number of vertices
    int numVertices = g.getV();
    cout << "\nNumber of vertices: " << numVertices << endl;

    cout << "Graph using adjacency matrix:\n";
    // Create a graph with 5 vertices
    GraphAM G(5);

    // Add edges to the graph

    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 4);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(1, 4);
    G.addEdge(2, 3);
    G.addEdge(3, 4);

    // Print the graph
    G.printGraph();

    // Get the adjacency matrix
    int** adjMatrix = G.getAdj();

    // Accessing element in adjacency matrix
    cout << "\nElement at (1, 2): " << adjMatrix[1][2] << endl;

    // Get the number of vertices
    int numVertices0 = G.getV();
    cout << "\nNumber of vertices: " << numVertices0 << endl;

    cout << "\n--Exercise 2--\nDFS - Recursive:\nDepth First Search (Recursive) starting from vertex 0: ";
    vector<bool> visited_recursive(g.getV(), false);
    DFS_Recursive(g, 0, visited_recursive);
    cout << endl;
    cout << "DFS - Iterative:\nDepth First Search (Iterative) starting from vertex 0: ";
    DFS_Iterative(g, 0);

    cout << "\n\n--Exercise 3--\n";
    // Perform BFS starting from vertex 0
    vector<int> bfsOrder = BFS(g, 0);

    // Print the BFS order
    cout << "BFS Order: ";
    for (int i = 0; i < bfsOrder.size(); ++i) {
        cout << bfsOrder[i] << " ";
    }

    cout << "\n\n--Exercise 4--\nDetect cycles in a directed graph using DFS:\n";
    if (isCyclicDirected(g))
        cout << "Graph contains cycle\n";
    else
        cout << "Graph does not contain cycle\n";
    cout << "Detect cycles in ab undirected graph using DFS:\n";
    // Check for cycle
    if (isCyclicUndirected(g))
        cout << "Graph contains cycle\n";
    else
        cout << "Graph does not contain cycle\n";

    cout << "\n--Exercise 5--\n";
    int source = 0; // Source vertex

    // Find shortest paths from source to all other vertices
    vector<int> shortestPaths = Dijkstra(G, source);

    // Print the shortest paths
    cout << "Shortest paths from source vertex " << source << ":\n";
    for (int i = 0; i < g.getV(); ++i) {
        cout << "To vertex " << i << ": " << shortestPaths[i] << endl;
    }

    cout << "\n--Exercise 6--\n";
    // Find connected components
    vector<vector<int>> components = findConnectedComponents(g);

    // Print connected components
    cout << "Connected Components:\n";
    for (const auto& component : components) {
        cout << "{ ";
        for (int vertex : component) {
            cout << vertex << " ";
        }
        cout << "}\n";
    }

    cout << "\n--Exercise 7--\n";
    vector<pair<int, int>> bridges;
    findBridgesUtil(g, bridges);

    // Print the bridges
    cout << "Bridges:\n";
    for (auto& bridge : bridges) {
        cout << bridge.first << " - " << bridge.second << endl;
    }

    cout << "\n--Exercise 8--\n";
    // Find communities
    vector<int> communities = louvain(g);

    // Print communities
    cout << "Communities:" << endl;
    for (int i = 0; i < g.getV(); ++i) {
        cout << "Node " << i << " belongs to community " << communities[i] << endl;
    }

    cout << "\n--Exercise 9--\n";
    // Calculate PageRank 
    int numIterations = 100;
    vector<double> pageRanks = PageRank(g, numIterations);

    // Print PageRank values
    cout << "PageRank values:\n";
    for (int i = 0; i < g.getV(); ++i) {
        cout << "Page " << i << ": " << pageRanks[i] << endl;
    }

    cout << "\n--Exercise 10--\n";
    // Source vertex
    int src = 0;

    // Find shortest distances using Dijkstra's algorithm
    vector<int> distances = Dijkstra_PQ(G, src);

    // Print the calculated distances
    cout << "Shortest distances from source vertex " << src << ":\n";

    for (int i = 0; i < G.getV(); ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Vertex " << i << ": INF (unreachable)\n";
        }
        else {
            cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }

    cout << "\n--Exercise 11--\n";

    // Example delivery points (replace with actual delivery points)
    vector<int> deliveryPoints = { 0, 2, 4 };

    // Find optimal delivery route
    vector<int> optimalRoute = findOptimalDeliveryRoute(G, deliveryPoints);

    // Print the optimal route
    cout << "Optimal Delivery Route: ";
    for (int i = 0; i < optimalRoute.size(); ++i) {
        cout << optimalRoute[i] << " ";
    }
    cout << endl;

    cout << "\n--Exercise 12--\n";
    // Create a sample social network (undirected graph)
    SocialNetwork network(5);
    network.addFriendship(0, 1);
    network.addFriendship(0, 2);
    network.addFriendship(1, 2);
    network.addFriendship(3, 4);

    // Find degree centrality
    vector<int> degrees = network.degreeCentrality();
    cout << "Degree Centrality: ";
    for (int i = 0; i < network.getV(); ++i) {
        cout << degrees[i] << " ";
    }
    cout << endl;

    // Find betweenness centrality
    vector<double> betweenness = network.betweennessCentrality();
    cout << "Betweenness Centrality: ";
    for (int i = 0; i < network.getV(); ++i) {
        cout << betweenness[i] << " ";
    }
    cout << endl;

    // Find communities (Louvain)
    vector<int> communities0 = network.louvain();
    cout << "Communities: ";
    for (int i = 0; i < network.getV(); ++i) {
        cout << communities0[i] << " ";
    }
    cout << endl;

    cout << "\n--Exercise 13--\n";
    RoadNetwork rn(5);
    rn.addRoad(0, 1, 10);
    rn.addRoad(0, 4, 20);
    rn.addRoad(1, 2, 30);
    rn.addRoad(1, 3, 40);
    rn.addRoad(2, 3, 50);
    rn.addRoad(3, 4, 60);

    cout << "Identifying traffic bottlenecks:" << endl;
    rn.findBottlenecks();

    cout << "\nSuggesting optimal traffic light timings:" << endl;
    rn.suggestTrafficLightTimings();

    cout << "\nSuggesting alternative routes:" << endl;
    rn.suggestAlternativeRoutes(0, 3);

    cout << "\n--Exercise 14--\n";
    int numUsers = 5;
    int numItems = 10;
    UserItemGraph graph(numUsers, numItems);

    // Add user-item interactions (replace with actual data)
    graph.addUserItemInteraction(0, 1);
    graph.addUserItemInteraction(0, 2);
    graph.addUserItemInteraction(1, 2);
    graph.addUserItemInteraction(1, 3);
    graph.addUserItemInteraction(2, 1);
    graph.addUserItemInteraction(2, 4);
    graph.addUserItemInteraction(3, 3);
    graph.addUserItemInteraction(3, 4);
    graph.addUserItemInteraction(4, 1);
    graph.addUserItemInteraction(4, 5);

    // Recommend items for user 0
    int user = 0;
    int numRecommendations = 3;
    vector<int> recommendedItems = graph.recommendItems(user, numRecommendations);

    cout << "Recommended items for user " << user << ": ";
    for (int item : recommendedItems) {
        cout << item << " ";
    }

    cout << "\n\n--Exercise 15--\n";
    int V = 5;
    Graph Snetwork(V);
    Snetwork.addEdge(0, 1, 2);
    Snetwork.addEdge(0, 3, 6);
    Snetwork.addEdge(1, 2, 3);
    Snetwork.addEdge(1, 3, 8);
    Snetwork.addEdge(1, 4, 5);
    Snetwork.addEdge(2, 3, 7);
    Snetwork.addEdge(3, 4, 9);

    // Find shortest paths from node 0
    vector<int> Sdistances = Snetwork.Dijkstra(0);
    cout << "Shortest distances from node 0: ";
    for (int i = 0; i < V; ++i) {
        cout << Sdistances[i] << " ";
    }
    cout << endl;

    // Find minimum spanning tree
    vector<pair<int, int>> mst = Snetwork.primMST();
    cout << "Minimum Spanning Tree Edges:" << endl;
    for (auto edge : mst) {
        cout << edge.first << " - " << edge.second << endl;
    }

    // Find critical nodes
    vector<int> criticalNodes = Snetwork.findCriticalNodes();
    cout << "Critical Nodes: ";
    for (int node : criticalNodes) {
        cout << node << " ";
    }
    cout << "\n\n--Exercise 16--\n";
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };
    pair<int, int> start = { 0, 0 };
    pair<int, int> goal = { 4, 4 };

    vector<pair<int, int>> path = a_star(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
    else {
        cout << "No path found." << endl;
    }
}