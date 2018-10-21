#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, M = 1e9+7;
int N, A[maxn];
int parent[1000001];

ll modexp(ll x, int n) {
    if (n == 0) return 1LL;
    if (n == 1) return x % M;
    if (n % 2 == 0) return modexp((x*x)%M,n/2);
    return (x * modexp((x*x)%M,n/2)) % M;
}

int find_parent(int i) {
    return (parent[i] < 0 ? i : parent[i] = find_parent(parent[i]));
}
void make_union(int u, int v) {
    u = find_parent(u);
    v = find_parent(v);
    if (u == v) return;
    if (parent[u] > parent[v]) {
        //storing the negative size
        swap(u,v);
    }
    parent[u] += parent[v];
    parent[v] = u;
}

void factorize(int i, vector<int>& ps) {
    if (i == 1) return;
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            while (i % j == 0) {
                i /= j;
            }
            ps.push_back(j);
            factorize(i,ps);
            return;
        }
    }
    ps.push_back(i);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        memset(parent,-1,sizeof(parent));
        int N; cin >> N;
        set<int> primes;
        int ones = 0;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            vector<int> ps;
            if (A[i] == 1) ones++;
            else {
                factorize(A[i],ps);
                for (int j: ps) {
                    primes.insert(j);
                }
                for (int j = 0; j < ps.size()-1; j++) {
                    make_union(ps[j],ps[j+1]);
                }
            }
        }
        set<int> comps;
        for (int i: primes) {
            comps.insert(find_parent(i));
        }
        ll ans = (modexp(2,comps.size() + ones) + M - 2) % M;
        cout << ans << '\n';
    }

    return 0;
}
	

