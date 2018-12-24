#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int maxn = 5e4+5;
const ll M = 1e9+7;
int N;

struct vhash {
    inline int operator()(const vector<int>& v) const {
        int s = 0;
        int mult = 1;
        for (int i: v) {
            s = (s + i*mult) % M;
            mult = (mult*1000000) % M;
        }
        return s;
    }
};

int pop[1<<5];
inline int popcount(int i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}

int a[maxn][5];
gp_hash_table<vector<int>,int,vhash> mp;
vector<int> masks[1<<5][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("cowpatibility.in","r",stdin); freopen("cowpatibility.out","w",stdout);
    cin >> N;
    for (int i = 0; i < (1 << 5); i++) pop[i] = popcount(i);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> a[i][j];
        }
        sort(a[i],a[i]+5);
        for (int mask = 1; mask < (1 << 5); mask++) {
            vector<int>& v = masks[mask][i];
            v.reserve(100);
            int idx = 0;
            for (int j = 0; j < 5; j++) {
                if (mask & (1<<j)) {
                    v.push_back(a[i][j]);   
                }
            }
            mp[v]++;
        }
    }
    
    ll cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int mask = 1; mask < (1 << 5); mask++) {
            int p = pop[mask];
            int c = mp[masks[mask][i]] - 1;
            cnt += (p&1?c:-c);
        }
    }
    cnt /= 2;
    ll ans = 1LL*N*(N-1)/2 - cnt;
    cout << ans << '\n';

    return 0;
}

