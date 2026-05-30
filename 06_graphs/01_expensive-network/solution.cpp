#include <iostream>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

using Vertex = int;
using Graph = std::vector<std::vector<std::pair<Vertex, int>>>;

std::optional<int> GetMaxSpanningTreeWeight(const Graph& g) {
    const int n = static_cast<int>(g.size());
    std::vector<bool> visited(n, false);

    Vertex start = 0;
    std::priority_queue<std::pair<int, Vertex>> pq;

    for (const auto& [neighbor, weight] : g[start]) {
        pq.push({weight, neighbor});
    }

    visited[start] = true;
    int visited_count = 1;
    int sum = 0;

    while (!pq.empty() && visited_count < n) {
        auto [weight, current] = pq.top();
        pq.pop();

        if (visited[current]) {
            continue;
        }

        visited[current] = true;
        ++visited_count;
        sum += weight;

        for (const auto& [neighbor, weight] : g[current]) {
            if (!visited[neighbor]) {
                pq.push({weight, neighbor});
            }
        }
    }

    if (visited_count != n) {
        return std::nullopt;
    }

    return sum;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        Vertex u, v;
        int w;
        std::cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    if (auto weight = GetMaxSpanningTreeWeight(g)) {
        std::cout << *weight << '\n';
    } else {
        std::cout << "Oops! I did it again" << '\n';
    }
}
