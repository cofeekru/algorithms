
#ifdef BOR
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct TreeNode {
    map<char, TreeNode> children;
    bool endOfWord = false;
};

vector<string> answer;

void insert(const string& word, TreeNode& root) {
    TreeNode* node = &root;
    for (char ch : word) {
        if (!node->children.count(ch)) {
            node->children[ch] = TreeNode();
        }
        node = &node->children[ch];
    }
    node->endOfWord = true;
}
int k;
void findKthWord(TreeNode& node, const string& word) {
    if (node.endOfWord) {
        answer.push_back(word);
    }
    for (auto& kv : node.children) {
        char c = kv.first;
        findKthWord(kv.second, word + c);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    TreeNode bor;
    int n;
    cin >> n;
    string word;
    bool insertMode = true;

    for (int i = 0; i < n; ++i) {
        cin >> word;

        if (word[0] >= 'a' && word[0] <= 'z') {
            insertMode = false;
            insert(word, bor);
        } else {
            k = stoi(word) - 1;
            if (!insertMode) {
                answer.clear();
                findKthWord(bor, "");
                insertMode = true;
            }
            cout << answer[k] << '\n';
        }
    }

    return 0;
}

#endif

#ifdef LINEAR
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

double gauss(vector<vector<double>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; ++i) {
        int mainElem = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(matrix[j][i]) > abs(matrix[mainElem][i])) {
                mainElem = j;
            }
        }
        swap(matrix[i], matrix[mainElem]);

        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = matrix[j][i] / matrix[i][i];
                for (int k = i; k < m; k++) {
                    matrix[j][k] -= factor * matrix[i][k];
                }

            }
        }
    }
}


int main() {
    vector<vector<double>> matrix;
    int n;
    while (cin >> n && n >= 1 && n <= 5) {
        
        matrix.assign(n, vector<double>(n));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (cin >> matrix[i][j] && matrix[i][j] >= 0 && matrix[i][j] <= 2) {
                    continue;
                } else {
                    return 0;
                }
            }
        }
        cout << gauss(matrix) << endl;; 
    }
    
    return 0;
}
#endif

#ifdef minCostMaxFlow
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int64_t to, capacity, cost;
    Edge* rev;

    Edge(int t, int c, int co, Edge* r) : to(t), capacity(c), cost(co), rev(r) {}
};

const int INF = INT_MAX;

int n, m;
vector<vector<Edge*>> adj;

int64_t minCostMaxFlow() {
    int64_t source = 1, sink = n;
    
    int64_t minCost = 0;
    while (true) {
        vector<int64_t> dist(n + 1, INF), parent(n + 1, -1);
        vector<Edge*> path(n + 1, nullptr);

        dist[source] = 0;

        bool updated = true;

        while (updated) {
            updated = false;
            for (int u = 1; u <= n; ++u) {
                if (dist[u] == INF) continue;
                for (Edge* edge : adj[u]) {
                    if (edge->capacity > 0 && dist[edge->to] > dist[u] + edge->cost) {
                        dist[edge->to] = dist[u] + edge->cost;
                        parent[edge->to] = u;
                        path[edge->to] = edge;
                        updated = true;
                    }
                }
            }
        }

        if (dist[sink] == INF) break;

        int64_t flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            flow = min(flow, path[v]->capacity);
        }

        for (int v = sink; v != source; v = parent[v]) {
            path[v]->capacity -= flow;
            path[v]->rev->capacity += flow;
            minCost += flow * path[v]->cost;
        }
    }

    return minCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    
    adj.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int from, to, capacity, cost;
        cin >> from >> to >> capacity >> cost;

        Edge* forward = new Edge(to, capacity, cost, nullptr);
        Edge* backward = new Edge(from, 0, -cost, forward);
        forward->rev = backward;

        adj[from].push_back(forward);
        adj[to].push_back(backward);
    }

    int64_t minCost = minCostMaxFlow();
    cout << minCost << '\n';

    return 0;
}
#endif
