#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, m, q;

vector<int>* parent[2*maxn];
vector<int>* find_parent(int f) { return parent[f]; }
bool make_union(int u, int v) {
    vector<int>* up = find_parent(u);
    vector<int>* vp = find_parent(v);
    if (up == vp) return true;
    if (up->size() < vp->size()) swap(up,vp);
    for (int w: (*vp)) {
        parent[w] = up;
        up->push_back(w);
    }
    delete vp;
    return false;
}

void dsuInit() {
    for (int i = 0; i < n + m; i++) {
        parent[i] = new vector<int>;
        parent[i]->push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    dsuInit();
    for (int i = 0; i < q; i++) {
        int r, c; cin >> r >> c;
        r--; c--;
        c += n;
        make_union(r,c);
    }

    set<vector<int>*> s;
    for (int i = 0; i < n + m; i++) {
        s.insert(parent[i]);
    }

    cout << s.size()-1 << '\n';


    return 0;
}
	

