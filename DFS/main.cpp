#include <iostream>
#include <stack>
#include <vector>
std::vector<std::vector<int>> adj;
std::vector<bool> visited;
// 재귀 버전
// void dfs(const int& value) {
//     std::cout << value << " ";
//     visited[value] = true;
//     for (auto next : adj[value]) {
//         if (!visited[next]) {
//             dfs(next);
//         }
//     }
// }

// stack 버전
void dfs(int start) {
    std::stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int curr = st.top();
        st.pop();
        if (visited[curr]) continue;
        visited[curr] = true;
        std::cout << curr << " ";
        for (auto it = adj[curr].rbegin(); it != adj[curr].rend(); ++it) {
            if (!visited[*it]) st.push(*it);
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

    adj.assign(7 + 1, {});

    visited.assign(7 + 1, false);

    auto addNodeValue = [&](int node, int value) {
        adj[node].push_back(value);
    };

    // auto dfs = [&](auto&& self, int node) -> void {
    //     visited[node] = true;
    //     std::cout << node << " ";
    //     for (int next : adj[node]) {
    //         if (!visited[next]) {
    //             self(self, next);
    //         }
    //     }
    // };

    addNodeValue(1, 2);
    addNodeValue(1, 3);

    addNodeValue(2, 4);
    addNodeValue(2, 5);

    addNodeValue(3, 6);
    addNodeValue(3, 7);

    dfs(1);

    // for (auto& temp : adj) {
    //     std::cout << "data: [ ";
    //     for (auto temp2 : temp)
    //         std::cout << temp2 << " ";
    //     std::cout << "]" << std::endl;
    // }
    return 1;
}