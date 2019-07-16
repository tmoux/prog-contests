#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4005;
int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

bool dp[maxn][maxn];
map<int,int> idtoRoot;

void recurse(int i, int sum, set<int>& zeros, vector<int>& comps) {
    if (i == 0) return;
    if (sum == 0) return;
    if (comps[i-1] <= sum && dp[i-1][sum-comps[i-1]]) {
        zeros.insert(idtoRoot[i]);
        recurse(i-1,sum-comps[i-1],zeros,comps);
    }
    else {
        recurse(i-1,sum,zeros,comps);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int qq = 1; qq <= T; qq++) {
        cout << "Case #" << qq << ": ";
        int N, M; cin >> N >> M;
        memset(parent,-1,sizeof parent);
        for (int i = 0; i < M; i++) {
            int l, r; cin >> l >> r;
            for (; l < r; l++, r--) {
                Union(l,r);    
                //cout << "Unioning " << l << ' ' << r << '\n';
            }
        }
        idtoRoot.clear();
        int sz = 1;
        vector<int> comps(N+1);
        int ssum = 0;
        for (int i = 1; i <= N; i++) {
            if (Find(i) == i) {
                idtoRoot[sz] = i;
                comps[sz-1] = -parent[i];
                //cout << "adding comp " << -parent[i] << '\n';
                sz++;
                ssum += -parent[i];
            }
        }
        assert(ssum == N); //sanity check
        sz--;
        //cout << "sz = " << sz << '\n';
        /*
        for (int i = 0; i < sz; i++) {
            cout << comps[i] << '\n';
        }
        */
        memset(dp,0,sizeof dp);
        for (int i = 0; i <= sz; i++) {
            dp[i][0] = true;
        }
        for (int i = 1; i <= sz; i++) {
            for (int j = 1; j <= N; j++) {
                dp[i][j] = dp[i-1][j];
                if (comps[i-1] <= j) {
                    dp[i][j] |= dp[i-1][j-comps[i-1]];
                }
            }
        }
        int diff = N;
        int start = -1;
        for (int j = N/2; j >= 0; j--) {
            if (dp[sz][j] == true) {
                diff = N-2*j;
                start = j;
                break;
            }
        }
        assert(start != -1);
        /*
        cout << "diff = " << diff << '\n';
        cout << "start = " << start << '\n';
        */
        set<int> zeros;
        recurse(sz,start,zeros,comps);
        vector<int> ans(N+1,1);
        /*
        for (int i: zeros) {
            cout << i << '\n';
        }
        */
        for (int i = 1; i <= N; i++) {
            //cout << i << ": " << Find(i) << '\n';
            if (zeros.count(Find(i))) {
                ans[i] = 0;
            }
        }

        //output
        for (int i = 1; i <= N; i++) {
            cout << ans[i];
        }
        cout << '\n';
    }
}

