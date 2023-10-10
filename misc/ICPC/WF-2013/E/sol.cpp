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

// Re-implementation time: 25:34

int B, S;
const int maxn = 1005;
pair<char, int> D[maxn];
int End[maxn];
const int MX = 13;

using T = pair<array<array<ll, MX>, MX>, ll>;

pair<T, int> F(int i, int r, int mask);
pair<T, int> G(int i, int r, int mask);

pair<T, int> F(int i, int r, int mask) {
    assert(D[i].first == 'R');
    int n = D[i].second;
    if (n == 1) return G(i, r, mask);
    else {
        auto [dat, nr] = G(i, r, mask);
        auto& [C1, total1] = dat;
        auto [dat2, nnr] = G(i, nr, mask);
        auto& [C2, total2] = dat2;

        ll total = total1 + (n-1) * total2;
        F0R(a, MX) F0R(b, MX) {
            C1[a][b] += (n-1) * C2[a][b];
        }
        return {{C1, total}, nnr};
    }
}

pair<T, int> G(int i, int r, int mask) {
    assert(D[i].first == 'R');
    int E = End[i];

    array<array<ll, MX>, MX> C;
    F0R(a, MX) F0R(b, MX) C[a][b] = 0;
    ll total = 0;
    for (i++; i < E; i++) {
        if (D[i].first == 'V') {
            int x = D[i].second;
            total++;
            if (!(mask & (1 << x))) {
                if (r == -1) total++;
                else if (r != x) C[r][x]++;
                r = x;
            }
        }
        else if (D[i].first == 'R') {
            auto [dat, nr] = F(i, r, mask);
            auto& [C2, total2] = dat;
            F0R(a, MX) F0R(b, MX) C[a][b] += C2[a][b];
            total += total2;
            r = nr;
            i = End[i];
        }
        else assert(0);
    }
    return {{C, total}, r};
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> B >> S;

    vector<string> vs = {"R1"};
    string s;
    while (cin >> s) vs.push_back(s);
    vs.push_back("E");
    stack<int> st;
    int mx = 0;
    F0R(i, sz(vs)) {
        char c = vs[i][0];
        if (c == 'R') {
            int n = stoi(vs[i].substr(1));
            D[i] = {'R', n};
            st.push(i);
        }
        else if (c == 'V') {
            int x = stoi(vs[i].substr(1)) - 1;
            D[i] = {'V', x};
            ckmax(mx, x+1);
        }
        else if (c == 'E') {
            assert(!st.empty());
            End[st.top()] = i;
            st.pop();
        }
        else assert(0);
    }
    assert(st.empty());

    ll ans = 1e18;
    F0R(mask, 1 << mx) {
        if (__builtin_popcount(mask) == min(mx, S)) {
            auto [dat, _] = F(0, -1, mask);
            const auto& [C, total] = dat;
            auto compute = [&](const vector<int>& assign) -> ll {
                ll ans = total;
                F0R(i, sz(assign)) {
                    F0R(j, sz(assign)) {
                        ans += (assign[i] != assign[j]) * C[i][j];
                    }
                }
                return ans;
            };

            vector<int> assign(mx, 0);
            vector<int> cnt(B, 0);
            function<void(int, int)> rec;
            rec = [&](int i, int num) -> void {
                if (i == mx) {
                    ckmin(ans, compute(assign));
                    return;
                }
                else {
                    if (mask & (1 << i)) rec(i+1, num);
                    else {
                        for (int j = 1; j < num; j++) {
                            if (cnt[j] < S) {
                                cnt[j]++;
                                assign[i] = j;
                                rec(i+1, num);
                                cnt[j]--;
                            }
                        }
                        if (num < B) {
                            cnt[num]++;
                            assign[i] = num;
                            rec(i+1, num+1);
                            cnt[num]--;
                        }
                    }
                }
            };
            rec(0, 1);
        }
    }
    cout << ans << '\n';
    return 0;
}
