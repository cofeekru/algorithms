#define FLOW

#ifdef PAIR

#include <iostream>
#include <vector>

std::vector <std::vector <int>> g; // g[i] - вершины из второй доли инцидентные с вершиной i из первой доли
std::vector <int> used; //пометки при обходе dfs-ом
std::vector <int> pair; //паросочетание

bool dfs(int v) {
    used[v] = 1;
    for(int x: g[v]) {
        if (pair[x] == -1 || (used[pair[x]] == 0 && dfs(pair[x]))) {
            pair [x] = v;
            return true;
        }
    }
    return false;
}
int main() {
    
    int n, m; // число вершин в 1-ой и 2-ой доле соответственно
    std::cin >> n >> m; 
    used.assign(n, 0);
    pair.assign(std::max(m,n), -1);
    g.resize(n);
    int v;
    for (size_t i = 0; i < n; i++) //инициализация графа
    {
        while (true)
        {
           std::cin >> v;    
            if (v - 1 != -1) {
                g[i].push_back(v - 1); 
            } else {
                break;
            }
        }
    }

    for (size_t i = 0; i < n; i++) //непостредственно алгоритм
    {
        if (dfs(i)) {
            used.assign(n, 0);
        }  
    }
    
    int count_pair = 0;
    for (size_t i = 0; i < pair.size(); i++)
    {
        if (pair[i] != -1) {
            count_pair++;
        }
    }
    std::cout << count_pair << std::endl;
    for (size_t i = 0; i < pair.size(); i++)
    {
        if (pair[i] != -1) {
            std::cout << pair[i]+1 << " " << i+1 << std::endl;
        }
    }
    return 0;
}
#endif // PAIR

#ifdef FLOW // для улиток



#include <iostream>
#include <vector>
#include <stack>
struct Edge {
    int from, to, flow, cpct; // собственно ребро
};

std::vector <Edge> edges;
int s, t; // исток и сток
int n, m; //вершины и рёбры

std::vector <int> used;
std::vector <std::vector <int>> g; // g[i] - номера рёбер исходящих из i
std::stack <int> route;
bool dfs(int v) {
    used[v] = 1;
    for (int edge_index : g[v])
    {
        Edge& edge = edges[edge_index];
        if (edge.flow < edge.cpct && !used[edge.to] && (edge.to == t-1 || dfs(edge.to)))
        {
            edge.flow++;
            edges[edge_index ^ 1].flow--;
            return true;
        }
    }
    return false;
}


void add_edge(int from, int to, int capacity = 1) {
    edges.push_back({from, to, 0, capacity});
    edges.push_back({to, from, 0, 0});
}

bool search_route(int v) {
    used[v] = 1;
    for (int edge_index : g[v])
    {
        Edge& edge = edges[edge_index];
        if (edge.flow == 1 && !used[edge.to] && (edge.to == t-1 || search_route(edge.to)))
        {
            route.push(edge.from+1);
            edge.flow--;
            edges[edge_index ^ 1].flow++;
            return true;
        }
    }
    return false; 
}

void print_route() {
    while (!route.empty())
    {
        std::cout << route.top() << " ";
        route.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> s >> t;
    g.resize(n);
    used.resize(n, 0);

    int from, to;

    for (size_t i = 0; i < 2*m; i += 2) {
        std::cin >> from >> to;
        add_edge(from-1, to-1);
        g[from-1].push_back(i);
        g[to-1].push_back(i+1);
    } // инициализация графа
    
    while (dfs(s-1)) {
        used.assign(n, 0);
        continue;
    } // поиск максимального потока

    int max_flow = 0;

    for(Edge edge : edges) {
        if (edge.to == t-1) {
            max_flow += edge.flow;
        }
    }

    if (max_flow >= 2) {
        std::cout << "YES" << std::endl;
        used.assign(n, 0);
        size_t j = 0;
        route.push(t);
        while (search_route(s-1)) {
            used.assign(n, 0);
            print_route();
            j++;
            if (j == 2) {
                break;
            }
            route.push(t);
        }
    } else {
        std::cout << "NO" << std::endl;
    }
    
    return 0;
}
#endif // FLOW для улиток

#ifdef STR

#include <iostream>
#include <vector>

inline int64_t binpow (int64_t a, int n) {
	int64_t res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

int64_t m = 18446744073709551557;
int p = 53;
std::vector <int64_t> h;
std::vector <int64_t> pows;




inline void initialize (int n, std::string &s) 
{ 
    h[0] = 0; 
    for (int i = 0; i < n; ++i) {
        h[i + 1] = (((h[i] % m) * (p % m)) % m + ((s[i] - 'a' + 1)) % m) % m; 
    }
}

inline int64_t getHash (int l, int r) 
{ 
    pows[r-l] = binpow(p, r - l) % m;
    int64_t res = (h[r] % m - ((h[l] % m) * (pows[r-l]) % m) % m) % m;
    return res < 0 ? res + m : res ; 
}


int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    std::string str;
    std::cin >> str;

    int n;
    std::cin >> n;
    h.assign(str.size()+2, 0);
    initialize(str.size()+1, str);
    pows.assign(str.size()+2, 1);    
    for (size_t i = 0; i < n; ++i)
    {
        int s1, f1, s2, f2;
        std::cin >> s1 >> f1 >> s2 >> f2; 
        if (f1 - s1 != f2 - s2)
        {
            std::cout << "No";
            std::cout << "\n";
        } else if (f1 == f2 && s1 == s2) {
            std::cout << "Yes";
            std::cout << "\n";
        } else {
            int64_t hash_first = getHash(s1-1, f1);
            int64_t hash_second = getHash(s2-1, f2);
            
            if (hash_first - hash_second == 0) 
            {
                std::cout << "Yes";
                std::cout << "\n";
            } else {
                std::cout << "No";
                std::cout << "\n";
            }
        }
    }
    std::cout << std::endl;
    return 0;
}

#endif //STR

#ifdef BOR
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;
string word, text;
int m;
typedef struct TrieNode {
    int children[ALPHABET_SIZE];
} TrieNode;

vector <TrieNode> bor;


inline void insert(string &key) {
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        bor.push_back({});
    }
    pCrawl->isEndOfWord = true;
}

inline bool search(struct TrieNode &root, string &key) {
    TrieNode *pCrawl = &root;
    for (int i = 0; i < key.length(); ++i) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != nullptr);
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    
    cin >> text;
    string substr;
    TrieNode* root = getNode();
    for (int i = 0; i < text.size(); ++i) {
        substr = text.substr(text.size() - 1 - i, i+1);
        insert(*root, substr);
    }
    
    for (int i = 0; i < text.size(); ++i) {
        substr = text.substr(0, i+1);
        insert(*root, substr);
    }
    
    cin >> m;

    for (int i = 0; i < m; ++i) {
        cin >> word;
        if (search(*root, word)) {
            cout << "Yes";
            cout << "\n";
        } else {
            cout << "No";
            cout << "\n";
        }
    }
    cout << endl;
    return 0;
}

#endif

#ifdef SUFF
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Suffix {
    int index; 
    vector <int> rank;
};

bool compare(const Suffix &a, const Suffix &b) {
    if (a.rank[0] != b.rank[0]) {
        return a.rank[0] < b.rank[0];
    } else {
        return a.rank[1] < b.rank[1];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string text;
	getline(cin, text);
    text += (char)128;
    int n = text.length();
    
    vector<Suffix> suffixes(n);

    for (int i = 0; i < n; ++i) {
        suffixes[i].index = i;
        suffixes[i].rank.resize(2);
        suffixes[i].rank[0] = text[i];
        suffixes[i].rank[1] = text[(i + 1) % n];
    }
    
    sort(suffixes.begin(), suffixes.end(), compare);
    
    vector<int> ind(n);
    int rank, prev_rank, next_index;
    int k = 4;
    
    while (k < 2 * n){
        rank = 0;
        prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; ++i) {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                rank += 1;
                suffixes[i].rank[0] = rank;
            }
            ind[suffixes[i].index] = i;
        }
        if (rank + 1 == suffixes.size()) {
            break;
        }
        for (int i = 0; i < n; ++i) {
            next_index = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = suffixes[ind[next_index % n]].rank[0];
        }
        sort(suffixes.begin(), suffixes.end(), compare);
        k *= 2;
    }

    for (int i = 1; i < n; ++i) {
        cout << suffixes[i].index + 1 << " ";
    }

    return 0;
}
#endif
#ifdef SUFFIX_ARRAY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
vector<int> suffix_array (string &s) {
    s.push_back(0);  
    int n = s.size(), cnt = 0, cls = 0; 
    vector<int> c(n), p(n);
    
    map <int, vector<int>> t;
    for (int i = 0; i < n; i++)
        t[s[i]].push_back(i);
    
    
    for (auto &x : t) {
        for (int u : x.second)
            c[u] = cls, p[cnt++] = u;
        cls++;
    }
    
   
    for (int l = 1; cls < n; l++) {
        vector< vector<int> > a(cls);  
        vector<int> _c(n); 
        int d = (1<<l)/2;
        int _cls = cnt = 0;
        
        for (int i = 0; i < n; i++) {
            int k = (p[i]-d+n)%n;
            a[c[k]].push_back(k);
        }
        
        for (int i = 0; i < cls; i++) {
            for (size_t j = 0; j < a[i].size(); j++) {
                
                if (j == 0 || c[(a[i][j]+d)%n] != c[(a[i][j-1]+d)%n])
                    _cls++;
                _c[a[i][j]] = _cls-1;
                p[cnt++] = a[i][j];
            }
        }
        
        c = _c;
        cls = _cls;
    }
    return vector<int>(p.begin()+1, p.end());
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string text;
	getline(cin, text);
    vector <int> answer = suffix_array(text);
    for(auto var : answer)
    {
        cout << var + 1 << " ";
    }
    return 0;

}
#endif // SUFFIX_ARRAY

#ifdef LCP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    string text;
    cin >> text;
    text += "#";
    vector <int> suffixes(N+1);
    suffixes[0] = N;
    vector <int> lcp(N);
    vector <int> c(N+1);
    c[N] = 0;
    int indexSuffix;
    for (size_t i = 1; i < N+1; i++) {
        cin >> indexSuffix;
        suffixes[i] = indexSuffix-1;
        c[indexSuffix-1] = i; 
    }
    int k = 0;
    for (size_t i = 0; i < N; i++)
    {
        int position = c[i]; // позиция i-го суффика в суфмассиве
        if (k > 0) 
            k--;
        while (text[suffixes[position] + k] == text[suffixes[position - 1] + k])
        {
            k++;
        }
        lcp[position-1] = k;
    }
    for (size_t i = 1; i <= N-1; i++)
    {
        cout << lcp[i] << ' ';
    }
    
    return 0;
}

#endif

#ifdef AHOKORASIK
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class AhoCorasick {
private:
    struct Node {
        std::unordered_map<char, Node*> children;
        Node* parent;
        Node* suffixLink;
        Node* outputLink;
        std::vector<int> patternIndexes;

        Node(Node* _parent) {
            parent = _parent;
            suffixLink = nullptr;
            outputLink = nullptr;
        }
    };

    Node* root;
    std::vector<std::string> patterns;

    void buildTrie() {
        root = new Node(nullptr);
        for (size_t i = 0; i < patterns.size(); i++) {
            Node* current = root;
            for (char c : patterns[i]) {
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new Node(current);
                }
                current = current->children[c];
            }
            current->patternIndexes.push_back(i);
        }
    }

    void buildSuffixLinks() {
        std::queue<Node*> nodeQueue;
        for (auto& it : root->children) {
            nodeQueue.push(it.second);
            it.second->suffixLink = root;
        }
        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();
            for (auto& it : current->children) {
                char ch = it.first;
                Node* child = it.second;
                nodeQueue.push(child);
                Node* temp = current->suffixLink;
                while (temp != root && temp->children.find(ch) == temp->children.end()) {
                    temp = temp->suffixLink;
                }
                if (temp->children.find(ch) != temp->children.end()) {
                    child->suffixLink = temp->children[ch];
                } else {
                    child->suffixLink = root;
                }
                child->outputLink = (child->suffixLink->patternIndexes.empty()) ? child->suffixLink->outputLink : child->suffixLink;
            }
        }
    }

    void clear(Node* node) {
        for (auto& it : node->children) {
            clear(it.second);
        }
        delete node;
    }

public:
    AhoCorasick(const std::vector<std::string>& _patterns) : patterns(_patterns) {
        buildTrie();
        buildSuffixLinks();
    }

    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> matches;
        Node* current = root;
        for (size_t i = 0; i < text.length(); i++) {
            char c = text[i];
            while (current != root && current->children.find(c) == current->children.end()) {
                current = current->suffixLink;
            }
            if (current->children.find(c) != current->children.end()) {
                current = current->children[c];
            } else {
                current = root;
            }
            Node* temp = current;
            while (temp != root) {
                for (int patternIndex : temp->patternIndexes) {
                    matches.push_back(std::make_pair(i - patterns[patternIndex].length() + 1, patternIndex));
                }
                temp = temp->outputLink;
            }
        }
        return matches;
    }

    ~AhoCorasick() {
        clear(root);
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> patterns;
    for (size_t i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        patterns.push_back(word);
    }
    std::string text;
    
    AhoCorasick ahoCorasick(patterns);
    std::vector<std::pair<int, int>> matches = ahoCorasick.search(text);
    for (auto match : matches) {
        std::cout << "Pattern \"" << patterns[match.second] << "\" found at position " << match.first << std::endl;
    }
    return 0;
}
#endif // DEBUG


#ifdef PRIME_NUMBERS
#include <iostream>
#include <vector>
using namespace std;
vector <bool> mask(100001, true);
vector <int> primes;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    size_t q = 2;
    for (size_t i = 2; i < 100001; ++i) {
        if (mask[i]) {
            primes.push_back(i);
            while (q*i < 100001) {
                mask[q*i] = false;
            }
        }
    }
    int requests, n;
    cin >> requests;
    while (requests--) {
        cin >> n;
        cout << primes[n-1] << "\n";
    }
    return 0;
}
#endif