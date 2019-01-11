#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Interval
{
    int l, r, id;        

    bool intersect(Interval a) {
        if (l == 0 && r == 0) {
            return false;
        }
        return !(a.l > r || a.r < l);
    }
};

const int maxn = 1e5+5;
int par[maxn];
void init(int n) {
    for (int i = 0; i < n; i++) {
        par[i] = -1;
    }
}

int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (par[x] > par[y]) swap(x,y);
    par[x] += par[y];
    par[y] = x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        init(n);
        vector<Interval> vs(n);
        for (int i = 0; i < n; i++) {
            int l, r; cin >> l >> r;
            vs[i] = {l,r,i};
        }
        sort(vs.begin(),vs.end(),[](auto a, auto b) { return a.l < b.l; });
        for (int i = 1; i < n; i++) {
            if (vs[i].l <= vs[i-1].r) {
                Union(vs[i].id,vs[i-1].id);
                vs[i].r = max(vs[i].r,vs[i-1].r);
            }
        }
        set<int> s;
        vector<int> ans(n);
        for (int i = 0; i < n; i++) s.insert(Find(i));
        if (s.size() == 1) {
            cout << -1 << '\n';
        }
        else {
            int fi = *s.begin();
            for (int i = 0; i < n; i++) {
                if (Find(i) == fi) {
                    ans[i] = 1;
                }
                else ans[i] = 2;
            }
            for (int i = 0; i < n; i++) {
                cout << ans[i] << ' ';
            }
            cout << '\n';
        }
    }


    return 0;
}

