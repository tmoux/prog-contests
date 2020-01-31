#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5, M = 998244353;
string s;
int off = 1001;
int n;

pair<int,int> dp[maxn][2*maxn];

void merge(pair<int,int>& a, pair<int,int> b) {
    if (b.first < a.first) {
        a = b;
    }
    else if (b.first == a.first) {
        a.second = (a.second+b.second) % M;
    }
}

pair<int,int> f(int i, int bal) {
    auto& res = dp[i][bal];    
    if (res.first != -1) return res;
    if (bal < off) return {maxn,0};
    if (i == n) {
        //printf("[%d][%d]\n",i,bal-off);
        if (bal == off) return res = {0,1};
        else return res = {maxn,0};
    }
    res = {maxn,0};
    merge(res,f(i+1,bal+(s[i]=='('?1:-1)));
    auto p = f(i+1,bal);
    merge(res,{p.first+1,p.second});
    //printf("[%d][%d]: (%d, %d)\n",i,bal-off,res.first,res.second);
    return res;
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    for (char& c: s) {
        c = c == 'm' ? '(' : ')';
    }
    n = s.size();
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2*maxn; j++) {
            dp[i][j] = {-1,-1};
        }
    }
    auto ans = f(0,off);
    //cout << "min op = " << ans.first << '\n';
    cout << ans.second << '\n';
}

