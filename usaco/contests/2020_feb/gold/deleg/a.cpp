#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, K;
vector<int> adj[maxn];
int ans[maxn];
bool poss;

int cnt[maxn];

int dfs2(int i, int p) {
    vector<int> v;
    v.reserve(adj[i].size());
    for (int j: adj[i]) {
        if (j == p) continue;
        int len = dfs2(j,i);
        if (len == -1 || len+1 > K) {
            poss = false;
            break;
        }
        if (len+1 == K) continue;
        v.push_back(len+1);
    }
    if (!poss) return -1;
    if (v.size() == 1) return v[0];
    sort(v.begin(),v.end());
    int ret = 0;
    for (auto j: v) ++cnt[j];
    for (auto& len: v) {
        if (cnt[len] == 0) continue;
        --cnt[len];
        if (cnt[K-len] > 0) {
            --cnt[K-len];
        }
        else {
            if (ret != 0 || i == p) {
                poss = false;
            }
            else {
                ret = len;
            }
        }
    }
    for (auto len: v) cnt[len] = 0;
    if (!poss) return -1;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("deleg.in","r",stdin); freopen("deleg.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> good;
    ans[1] = 1;
    for (int k = N-1; k > 1; k--) {
        if ((N-1) % k == 0) {
            for (int i: good) {
                if (i % k == 0) {
                    ans[k] = 1;
                    break;
                }
            }
            if (!ans[k]) {
                poss = true;
                K = k;
                ans[k] = dfs2(1,1) != -1;
                if (ans[k]) good.push_back(k);
            }
        }
    }
    for (int i = 1; i <= N-1; i++) {
        cout << ans[i];
    }
    cout << '\n';
}

