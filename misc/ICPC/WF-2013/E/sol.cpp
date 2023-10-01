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

const int maxn = 2005;
int Index[maxn];
pair<char, int> what[maxn];
int nxt[maxn], jmp[maxn];
int B, S, id = 0;

const int MX = 13;
ll C[MX][MX], total = 0;
using T = pair<pair<array<array<ll, MX>, MX>, ll>, int>;

T G(int i, int r, int mask);
T F(int i, int r, int mask);

T G(int i, int r, int mask) {
    assert(what[i].first == 'R');
    int end = jmp[i];
    i++;

    array<array<ll, MX>, MX> c;
    F0R(a, MX) F0R(b, MX) c[a][b] = 0;
    ll t = 0;
    while (i < end) {
        assert(i != -1);
        if (what[i].first == 'V') {
            t++;
            int x = Index[i];
            if (!(mask & (1 << x))) {
                if (r != -1) c[r][x]++;
                r = x;
            }
            i++;
        }
        else if (what[i].first == 'R') {
            auto [cost2, nr] = F(i, r, mask);
            F0R(a, MX) F0R(b, MX) c[a][b] += cost2.first[a][b];
            t += cost2.second;
            r = nr;
            i = jmp[i] + 1;
        }
        else {
            assert(false);
        }
    }
    return {{c, t}, r};
}

T F(int i, int r, int mask) {
    assert(what[i].first == 'R');
    int n = what[i].second;
    if (n == 1) {
        return G(i, r, mask);
    }
    else {
        auto [c, nr] = G(i, r, mask);
        auto [cost2, nnr] = G(i, nr, mask);
        cost2.second = (cost2.second * (n-1)) + c.second;
        F0R(a, MX) {
            F0R(b, MX) {
                cost2.first[a][b] = cost2.first[a][b] * (n-1) + c.first[a][b];
            }
        }
        return {cost2, nnr};
    }
}

ll cnt = 0;
ll solve(const vector<int>& assign) {
    ll ans = total;
    bool has_gt0 = false;
    F0R(i, sz(assign)) if (assign[i] > 0) has_gt0 = true;
    if (has_gt0) ans++;
    F0R(i, sz(assign)) {
        F0R(j, sz(assign)) {
            ans += C[i][j] * (assign[i] != assign[j]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    memset(nxt, -1, sizeof nxt);
    memset(jmp, -1, sizeof jmp);
    cin >> B >> S;

    vector<string> vs = {"R1"};
    string s;
    while (cin >> s) vs.push_back(s);
    vs.push_back("E");

    stack<int> st;
    vector<int> V;
    for (auto s: vs) {
        if (s[0] == 'E') {
            what[id] = {'E', 0};
            assert(!st.empty());
            jmp[st.top()] = id;
            st.pop();
        }
        else if (s[0] == 'V') {
            int i = stoi(s.substr(1)) - 1;
            Index[id] = i;
            V.push_back(i);
            what[id] = {'V', i};
        }
        else if (s[0] == 'R') {
            int n = stoi(s.substr(1));
            what[id] = {'R', n};
            st.push(id);
        }
        id++;
    }
    sort(all(V)); V.erase(unique(all(V)), V.end());
    map<int, int> compress;
    F0R(i, sz(V)) compress[V[i]] = i;
    F0R(i, id) Index[i] = compress[Index[i]];
    int mx = sz(V);

    ll ans = 1e18;

    int target = min(S, mx);
    for (int mask = 0; mask < (1 << mx); mask++) {
        if (__builtin_popcount(mask) == target) {
            memset(C, 0, sizeof C);
            total = 0;
            auto p = F(0, -1, mask);
            F0R(a, MX) {
                F0R(b, MX) {
                    C[a][b] = p.first.first[a][b];
                }
            }
            total = p.first.second;

            vector<int> assign(mx);
            vector<int> cnt(B);
            for (int i = 0; i < mx; i++) {
                if (mask & (1 << i)) assign[i] = 0;
            }

            function<void(int, int)> rec;
            rec = [&](int i, int num) {
                if (i == mx) {
                    ckmin(ans, solve(assign));
                    return;
                }
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
            };

            rec(0, 1);
        }

    }
    cout << ans << '\n';
    return 0;
}
