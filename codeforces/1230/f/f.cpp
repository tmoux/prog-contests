#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, q;
vector<int> dislike[maxn];
ll in[maxn], out[maxn];
int queries[maxn];

ll res[maxn];
int s[maxn];

vector<int> update[maxn];
vector<int> bigAdj[maxn];
bool isBig[maxn];

void change(int j, ll& ans) {
    ans -= 1LL*in[j]*out[j];
    out[j]--;
    in[j]++;
    ans += 1LL*in[j]*out[j];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        s[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        dislike[a].push_back(b);
        dislike[b].push_back(a);
        if (a > b) swap(a,b);
        in[a]++;
        out[b]++;
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> queries[i];
    }
    const int big = 400;
    vector<int> bigs;
    for (int i = 1; i <= n; i++) {
        if (in[i] + out[i] >= big) {
            bigs.push_back(i);
            isBig[i] = true;
        }
    }
    for (int i: bigs) {
        for (int j: dislike[i]) {
            if (j > i && !isBig[j]) {
                update[i].push_back(j);
            }
            else if (isBig[j]) {
                bigAdj[i].push_back(j);
            }
        }
    }
    
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1LL*in[i]*out[i];
    }
    res[0] = ans;
    for (int i = 1; i <= q; i++) {
        int v = queries[i];
        if (!isBig[v]) {
            for (int j: dislike[v]) {
                if (s[v] > s[j]) continue;
                change(j,ans);
                if (isBig[j]) update[j].push_back(v);
            }
        }
        else {
            for (int j: update[v]) {
                change(j,ans);
            }
            update[v].clear();
            for (int j: bigAdj[v]) {
                if (s[v] > s[j]) continue;
                change(j,ans);
            }
        }
        ans -= 1LL*in[v]*out[v];
        in[v] = 0;
        out[v] = dislike[v].size();
        res[i] = ans;
        s[v] = n + i;
        /*
        for (int j = 1; j <= n; j++) {
            cout << j << ": " << in[j] << ' ' << out[j] << '\n';
        }
        cout << '\n';
        */
    }
    //output
    for (int i = 0; i <= q; i++) {
        cout << res[i] << '\n';
    }
}
