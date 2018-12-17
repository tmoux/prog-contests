#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;
const ld PI = 4*atan((ld)1);

template<class T> void ckmin(T &a, T b) { a = min(a, b); }
template<class T> void ckmax(T &a, T b) { a = max(a, b); }

int N, M, K;
long long food [50010], dists [50010][2];
bool visited [50010][2];
vector<pair<int, long long>> adjacency [50010];
priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;

int main() {
    // you should actually read the stuff at the bottom
    //freopen("dining.in", "r", stdin); freopen("dining.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0); cout << fixed << setprecision(12);
    cin >> N >> M >> K; memset(food, -1, sizeof(food)); memset(visited, false, sizeof(visited));
    for(int i = 0; i < M; i++){
        int a, b; long long c; cin >> a >> b >> c;
        adjacency[a].pb(mp(b, c)); adjacency[b].pb(mp(a, c));
    }
    for(int i = 0; i < K; i++){
        int a; long long b; cin >> a >> b;
        food[a] = max(food[a], b);
    }
    pq.push(mp(0, mp(N, 1)));
    while(pq.size() > 0){
        pair<long long, pair<int, int>> now = pq.top(); pq.pop();
        if(visited[now.s.f][now.s.s]) continue;
        visited[now.s.f][now.s.s] = true; dists[now.s.f][now.s.s] = now.f;
        if(food[now.s.f] > -1 && now.s.s == 1) pq.push(mp(now.f-food[now.s.f], mp(now.s.f, 0)));
        for(pair<int, long long> edge : adjacency[now.s.f])
            if(!visited[edge.f][now.s.s])
                pq.push(mp(now.f+edge.s, mp(edge.f, now.s.s)));
    }
    for(int i = 1; i <= N-1; i++) cout << (dists[i][0] <= dists[i][1]) << '\n';
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
