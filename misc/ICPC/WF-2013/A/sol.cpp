//Randomness stuff, ckmin, ckmax are optional--depends on time
#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


const int MX = 2 * 26;
vector<int> adj[2*MX];

int cv(char c, char o) {
    return 2 * (c - 'A') + (o == '+' ? 1 : 0);
}

bool has_cycle = false;

bool vis[2*MX], onstack[2*MX];

void dfs(int i) {
    if (!vis[i]) {
        vis[i] = 1;
        onstack[i] = 1;
        for (int j: adj[i]) {
            if (onstack[j]) {
                has_cycle = true;
            }
            else dfs(j);
        }
        onstack[i] = 0;
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    F0R(qq, N) {
        string s; cin >> s;
        vector<int> v;
        for (int j = 0; j < sz(s); j += 2) {
            if (s[j] != '0') {
                int x = cv(s[j], s[j+1]);
                v.push_back(x);
            }
        }

        F0R(i, sz(v)) {
            F0R(j, sz(v)) {
                if (i == j) continue;
                adj[v[i] + MX].push_back(v[j]);
            }
        }
    }

    F0R(i, MX) {
        adj[i].push_back((i ^ 1) + MX);
    }

    F0R(i, MX) {
        if (!vis[i]) dfs(i);
    }

    if (has_cycle) {
        cout << "unbounded" << '\n';
    }
    else {
        cout << "bounded" << '\n';
    }

	return 0;
}
