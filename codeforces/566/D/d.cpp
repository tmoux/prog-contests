#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q;
set<int> s;

random_device device;
mt19937 gen(device());

int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    //if (parent[x] > parent[y]) swap(x,y);
    if (gen()&1) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int cntr = 0;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        s.insert(i);
    }
    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            Union(Find(x),Find(y));
        }
        else if (t == 2) {
            if (x > y) swap(x,y);
            auto it = s.upper_bound(x);
            int par = *prev(it);
            //erase union'd intervals
            for (; it != s.end();) {
                cntr++;
                if (*it <= y) {
                    Union(Find(par),Find(*it));
                    s.erase(it++);
                }
                else {
                    break;
                }
            }
        }
        else if (t == 3) {
            cout << (Find(x)==Find(y)?"YES":"NO") << '\n';
        }
    }
}

