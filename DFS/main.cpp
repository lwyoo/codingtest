#include <iostream>
#include <vector>

std::vector<std::vector<int>> adj;
std::vector<bool> visited;
void dfs(int node) {
    visited[node] = true;
    std::cout << node << " ";

    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
}

int main() {
    std::cout << "퉁퉁퉁퉁사후르" << std::endl;

    // 		1
    //    / \
    //   2   3
    //  /|   |\
    // 4 5   6 7

    int cnt = 7;
    visited.assign(cnt + 1, false);
    adj.assign(cnt + 1, {});

    auto aaa = [&](int node_a, int node_b) {
        adj[node_a].push_back(node_b);
        adj[node_b].push_back(node_a);
    };

    aaa(1, 2);
    aaa(1, 3);

    aaa(2, 4);
    aaa(2, 5);

    aaa(3, 6);
    aaa(3, 7);
    // 재귀로 돌면서 탐색 하기
    dfs(1);
    return 1;
}