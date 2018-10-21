#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, maxm = 1e6+6;
int N, M, A, B, freq[maxn];
ll ans = 0;
vector<int> child[maxn];

struct Node
{
    priority_queue<int>* s;
    inline int sz() { return s->size(); }
    Node() {
        s = new priority_queue<int>;
    }
    
    void addSelf(int id) {
        s->push(id);
        int size = sz();
        for (int i = 0; i < min(size,freq[id]); i++) {
            ans += s->top();
            s->pop();
        }
    }
};

void merge(Node& a, Node& b) {
    if (a.sz() < b.sz()) swap(a,b);
    while (!(b.s->empty())) {
        a.s->push(b.s->top());
        b.s->pop();
    }
}

Node* dfs(int i, int par) {
    Node* ni = new Node();
    for (int j: child[i]) {
        if (j == par) continue;
        Node* nj = dfs(j,i);
        merge(*ni,*nj);
        delete nj->s;
        delete nj;
    }
    ni->addSelf(i);
    return ni;
}

void solve(int t) {
    cin >> N >> M >> A >> B;
    memset(freq,0,sizeof(freq));
    for (int i = 0; i < N; i++) child[i].clear();
    for (int i = 1; i < N; i++) {
        int pi; cin >> pi;
        child[pi].push_back(i);
    }
    for (int i = 0; i < M; i++) { 
        int ci = (1LL * A * i + B) % N;
        freq[ci]++;
    }
    ans = 0;
    dfs(0,0);
    cout << "Case #" << t << ": " << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) solve(i);
    return 0;
}
	

