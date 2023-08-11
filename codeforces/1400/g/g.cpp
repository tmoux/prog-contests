#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int msub(int a, int b) {
    madd(a,M-b);
    return a;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int fac[maxn], ifac[maxn];
int choose(int n, int r) {
    if (n < r) return 0;
    int ans = fac[n];
    ans = mult(ans,ifac[r]);
    ans = mult(ans,ifac[n-r]);
    return ans;
}
int n, m;
struct Person
{
    int bad, id, l, r;
    bool operator<(const Person& rhs) const {
        return bad > rhs.bad;
    }
};


vector<Person> a;

vector<int> start[maxn], stop[maxn];
const int maxm = 41;

vector<int> edges[maxm];
int mapid[maxn];
bool active[maxn];

int bc = 0;
int badcount[maxm];

vector<pair<int,int>> edgelist;
ll edge_mask[maxm];
void recurse(int total_bad) {
    vector<pair<int,int>> es;
    for (int i = 0; i < edgelist.size(); i++) {
        int u = edgelist[i].first;
        int v = edgelist[i].second;
        if (active[u] && active[v]) {
            es.push_back({u,v});
        }
    }
    int es_size = es.size();
    for (int mask = 0; mask < (1<<es_size); mask++) {
        vector<bool> seen(bc,false);
        int sz = 0;
        for (int i = 0; i < es_size; i++) {
            if (!(mask & (1<<i))) continue;
            int u = es[i].first;
            int v = es[i].second;
            if (!seen[u]) {
                sz++;
                seen[u] = true;
            }
            if (!seen[v]) {
                sz++;
                seen[v] = true;
            }
        }
        bool oddMask = (__builtin_popcount(mask))&1;
        for (int i = 0; i+sz <= total_bad; i++) {
            int add = oddMask?M-choose(total_bad-sz,i):choose(total_bad-sz,i);
            madd(badcount[i+sz],add);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(i,fac[i-1]);
        ifac[i] = inverse(fac[i]);
    }
    cin >> n >> m;
    bool flag = false;
    vector<pair<int,int>> ps;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        ps.push_back({a,b});
    }
    vector<pair<int,int>> ee;
    vector<int> isbad(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        isbad[a] = true;
        isbad[b] = true;
        ee.push_back({a,b});
    }
    for (int i = 0; i < n; i++) {
        a.push_back({isbad[i],i,ps[i].first,ps[i].second});
        if (isbad[i]) bc++;
    }
    sort(a.begin(),a.end());
    for (int i = 0; i < n; i++) {
        start[a[i].l].push_back(i);
        stop[a[i].r].push_back(i);
        mapid[a[i].id] = i;
    }
    for (auto p: ee) {
        edges[mapid[p.first]].push_back(mapid[p.second]);
        edges[mapid[p.second]].push_back(mapid[p.first]);
        edgelist.push_back({mapid[p.first],mapid[p.second]});
    }
    int ans = 0;
    int numgood = 0;
    int numActive = 0;
    int cnt = 0;

    badcount[0] = 1;
    for (int i = 1; i <= n; i++) {
        //handle starts
        for (int id: start[i]) {
            numActive++;
            active[id] = true;
            if (id >= bc) numgood++;
            else cnt++;
        }
        
        if (cnt) { //update graph count
            for (int i = 0; i <= bc; i++) badcount[i] = 0;
            recurse(numActive-numgood);
            cnt = 0;
        }

        for (int j = 0; j <= bc && i-j >= 0; j++) {
            int add = mult(choose(numgood,i-j),badcount[j]);
            madd(ans,add);
        }

        //handle stops
        for (int id: stop[i]) {
            numActive--;
            active[id] = false;
            if (id >= bc) numgood--;
            else cnt++;
        }
    }
    cout << ans << '\n';
}
