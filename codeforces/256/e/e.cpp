#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 80000, M = 777777777;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int n, m;
int a[4][4];
int dp[4][4][maxn];
//SQRT
int value[maxn];
int block_size = sqrt(maxn);
int bucket[maxn];

int len[maxn];
struct Chain
{
    int idx, start_val;
    bool operator<(const Chain& rhs) const {
        return idx < rhs.idx;
    }
};
set<Chain> S;
int chain_length(Chain c) {
    return len[c.idx];
}

struct Block
{
    set<Chain> v;    
    int fac;
    void rebuild() {
        fac = 1;
        if (v.empty()) return;
        for (auto it = v.begin(); next(it) != v.end(); ++it) {
            int len = chain_length(*it);
            int add = 0;
            int j = next(it)->start_val;
            for (int i = 1; i <= 3; i++) {
                madd(add,mult(a[i][j],dp[it->start_val][i][len])); 
            }
            fac = mult(fac,add);
        }
    }
} blocks[maxn];

int calc() {
    int res = 1;
    int j = -1;
    for (int i = bucket[n-1]; i >= 0; i--) {
        Block& b = blocks[i];
        if (b.v.empty()) continue;
        if (j == -1) {
            j = b.v.begin()->start_val;
            int add = 0;
            Chain c = *b.v.rbegin();
            int len = chain_length(c);
            for (int i = 1; i <= 3; i++) {
                madd(add,dp[c.start_val][i][len]);
            }
            res = mult(b.fac,add);
        }
        else {
            int add = 0;
            Chain c = *b.v.rbegin();
            int len = chain_length(c);
            for (int i = 1; i <= 3; i++) {
                madd(add,mult(a[i][j],dp[c.start_val][i][len]));
            }
            add = mult(add,b.fac);
            res = mult(res,add);

            j = b.v.begin()->start_val;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    block_size = sqrt(n);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> a[i][j];
        }
    }
    //precompute dp's
    dp[0][1][1] = dp[0][2][1] = dp[0][3][1] = 1;
    dp[1][1][1] = dp[2][2][1] = dp[3][3][1] = 1;
    for (int s = 0; s <= 3; s++) {
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= 3; j++) {
                for (int k = 1; k <= 3; k++) {
                    madd(dp[s][j][i],mult(a[k][j],dp[s][k][i-1]));
                }
            }
        }
    }
    //sqrt
    for (int i = 0; i < n; i++) {
        bucket[i] = i/block_size;
    }
    S.insert({0,0});
    blocks[0].v.insert({0,0});
    blocks[0].rebuild();
    len[0] = n;

    for (int i = 0; i < m; i++) {
        int idx, t; cin >> idx >> t;
        idx--;
        if (t == 0 && idx != 0) { //removing
            auto it = S.find({idx,t});
            if (it != S.end()) {
                if (it != S.begin()) {
                    len[prev(it)->idx] += len[idx];
                }
                len[idx] = 0;

                S.erase(it);
                blocks[bucket[idx]].v.erase({idx,t});
                blocks[bucket[idx]].rebuild();
            }
        }
        else { //adding/replacing
            auto it = S.lower_bound({idx,0});
            if (it != S.end() && it->idx == idx) {
                blocks[bucket[idx]].v.erase(*it);
                S.erase(it);
            }
            else {
                --it;
                len[idx] = len[it->idx] - (idx-it->idx);
                len[it->idx] -= len[idx];
            }
            S.insert({idx,t});
            blocks[bucket[idx]].v.insert({idx,t});
            blocks[bucket[idx]].rebuild();
        }
        cout << calc() << '\n';
    }
}
