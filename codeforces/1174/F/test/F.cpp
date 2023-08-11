#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];

vector<int> vfill;
void fill(int i, int p, int d, int target) {
    if (d == target) {
        vfill.push_back(i);
        return;
    }
    else {
        for (int j: adj[i]) {
            if (j == p) continue;
            fill(j,i,d+1,target);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,n);
    set<int> poss;
    for (int i = 1; i <= n; i++) poss.insert(i);
    for (int i = 0; i < 36; i++) {
        int r = dist(gen);
        cout << 'd' << ' ' << r << endl;
        int d; cin >> d;
        vfill.clear();
        fill(r,r,0,d);
        set<int> ns;
        for (int i: vfill) {
            if (poss.count(i)) ns.insert(i);
        }
        poss = ns;
        if (poss.size() == 1) break;
    }
    if (poss.size() > 1) {
        cout << "we failed" << endl;
    }
    else {
        cout << "! " << *poss.begin() << endl;
    }
}

