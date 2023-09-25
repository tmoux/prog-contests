#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }


template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef NEAL_DEBUG
#define dbg(...) cerr << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size. When data[x] >= 0, data[x] is x's parent.
    vector<int> data;
    int components = 0;

    union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }

    void init(int n) {
        data.assign(n + 1, -1);
        components = n;
    }

    int find(int x) {
        return data[x] < 0 ? x : data[x] = find(data[x]);
    }

    int get_size(int x) {
        return -data[find(x)];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y)
            return false;

        if (-data[x] < -data[y])
            swap(x, y);

        data[x] += data[y];
        data[y] = x;
        components--;
        return true;
    }
};

struct SCC {
    int V = 0;
    vector<vector<int>> adj;
    vector<int> tour_index, low_link;
    int tour;

    vector<int> stack;
    vector<bool> in_stack;

    vector<vector<int>> components;
    vector<int> which_component;

    SCC(int v = 0) {
        init(v);
    }

    SCC(const vector<vector<int>> &_adj) {
        init(_adj);
    }

    void init(int v) {
        V = v;
        adj.assign(V, {});
    }

    void init(const vector<vector<int>> &_adj) {
        adj = _adj;
        V = int(adj.size());
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b);
    }

    // Tarjan's algorithm.
    void dfs(int node) {
        tour_index[node] = tour++;
        low_link[node] = tour_index[node];
        stack.push_back(node);
        in_stack[node] = true;

        for (int neighbor : adj[node])
            if (tour_index[neighbor] < 0) {
                // neighbor is part of our subtree.
                dfs(neighbor);
                low_link[node] = min(low_link[node], low_link[neighbor]);
            } else if (in_stack[neighbor]) {
                // neighbor is a candidate for low_link.
                low_link[node] = min(low_link[node], tour_index[neighbor]);
            }

        if (low_link[node] == tour_index[node]) {
            // node is the highest node in an SCC, which includes everything on the stack up to it.
            components.emplace_back();
            vector<int> &component = components.back();
            int x;

            do {
                assert(!stack.empty());
                x = stack.back();
                stack.pop_back();
                in_stack[x] = false;
                which_component[x] = int(components.size()) - 1;
                component.push_back(x);
            } while (x != node);
        }
    }

    void build() {
        tour_index.assign(V, -1);
        low_link.resize(V);
        which_component.assign(V, -1);

        stack.clear();
        stack.reserve(V);
        in_stack.assign(V, false);
        tour = 0;

        // Note that Tarjan's algorithm provides the SCCs in reverse topological order.
        components = {};

        for (int i = 0; i < V; i++)
            if (tour_index[i] < 0)
                dfs(i);
    }
};


const string YES = "Yes", NO = "No";

int main() {
    ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
    cin.tie(nullptr);
#endif

    int N, M;
    cin >> N >> M;
    vector<int> A(M), B(M), C(M), D(M);

    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        A[i]--; C[i]--;
    }

    vector<int> OA = A, OB = B, OC = C, OD = D;
    vector<int> X(N, -1);
    union_find UF(N);

    while (true) {
        SCC scc(N);

        for (int i = 0; i < N; i++)
            if (UF.find(i) != i) {
                scc.add_edge(i, UF.find(i));
                scc.add_edge(UF.find(i), i);
            }

        for (int i = 0; i < M; i++) {
            while (A[i] < B[i] && C[i] < D[i] && UF.find(A[i]) == UF.find(C[i])) {
                A[i]++;
                C[i]++;
            }

            if (C[i] == D[i]) {
                cout << NO << '\n';
                return 0;
            }

            if (A[i] == B[i])
                continue;

            scc.add_edge(A[i], C[i]);
        }

        scc.build();
        bool change = false;

        for (auto &component : scc.components)
            for (int x : component)
                if (UF.unite(x, component.front()))
                    change = true;

        if (!change) {
            int current = 0;

            for (int component_index = int(scc.components.size()) - 1; component_index >= 0; component_index--) {
                for (int x : scc.components[component_index])
                    if (X[x] < 0)
                        X[x] = current;

                current++;
            }

            break;
        }
    }

    // for (int i = 0; i < M; i++)
    //     if (vector<int>(X.begin() + OA[i], X.begin() + OB[i]) >= vector<int>(X.begin() + OC[i], X.begin() + OD[i])) {
    //         cout << NO << '\n';
    //         return 0;
    //     }

    cout << YES << '\n';
}
