#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

ll n;
int m;

int exp10[25];
int mult(int a, int b) {
    return (1LL*a*b) % m;
}

int sz = -1;

const int M = 1e9+7;
const int b = 31;
void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}

//unordered_map<int,ll> dp;
gp_hash_table<int,ll> dp;

int hsh(const pair<vector<int>,pair<int,int>>& p) {
    int mul = 1;
    int ret = 0;
    for (int i = 0; i < 10; i++) {
        madd(ret,(1LL*p.first[i]*mul)%M);       
        mul = (1LL*mul*b) % M;
    }
    madd(ret,(1LL*p.second.first*mul)%M);
    mul = (1LL*mul*b) % M;
    madd(ret,(1LL*p.second.second*mul)%M);
    mul = (1LL*mul*b) % M;
    return ret;
}

ll f(pair<vector<int>,pair<int,int>> p) {
    if (p.second.first == -1) return p.second.second==0?1:0;
    int h = hsh(p);
    if (dp.find(h) != dp.end()) return dp[h];
    vector<int>& v = p.first;
    int pos = p.second.first;
    int mod = p.second.second;
    
    ll res = 0;
    for (int d = 0; d < 10; d++) {
        if (pos == sz && d == 0) continue;
        if (v[d] == 0) continue;
        int nmod = (mod+mult(d,exp10[pos])) % m;
        v[d]--;
        res += f({v,{pos-1,nmod}});
        v[d]++;
    }
    /*
    for (int i = 0; i < 10; i++) {
        cout << v[i] << ' ';
    }
    cout << '\n';
    printf("pos = %d, mod = %d, h = %d: %d\n",pos,mod,h,res);
    */
    return dp[h] = res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    vector<int> cnt(10,0);
    ll x = n;
    while (x > 0) {
        cnt[x%10]++;
        x /= 10;
        sz++;
    }
    exp10[0] = 1;
    for (int i = 1; i < 25; i++) {
        exp10[i] = (exp10[i-1] * 10) % m;
    }
    //cout << "sz = " << sz << '\n';
    ll ans = f({cnt,{sz,0}});
    cout << ans << '\n';
}

