#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <bits/stdc++.h>

class Graph {
public:
    std::unordered_map<int, std::vector<int>> adj_list;

    void addEdge(int u, int v) {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u); // Assuming an undirected graph
    }

    std::vector<int> shortestPathBFS(int start, int end) {
        std::unordered_set<int> visited;
        std::queue<std::vector<int>> q;
        q.push({start});

        while (!q.empty()) {
            std::vector<int> path = q.front();
            q.pop();
            int current = path.back();

            if (current == end) {
                return path;
            }

            if (visited.find(current) == visited.end()) {
                visited.insert(current);

                for (int neighbor : adj_list[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        std::vector<int> new_path = path;
                        new_path.push_back(neighbor);
                        q.push(new_path);
                    }
                }
            }
        }

        std::cout << "No path found between " << start << " and " << end << "." << std::endl;
        return {};
    }
};

int main() {
    Graph graph;
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);
    graph.addEdge(0,5);

    int startNode = 0;
    int endNode = 5;

    std::vector<int> shortestPath = graph.shortestPathBFS(startNode, endNode);

    if (!shortestPath.empty()) {
        std::cout << "Shortest path from " << startNode << " to " << endNode << ": ";
        for (int node : shortestPath) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
