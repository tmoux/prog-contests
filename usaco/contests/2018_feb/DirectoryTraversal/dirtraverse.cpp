#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll maxn = 1e5+5;
ll N, wt[maxn], parent[maxn], subtree[maxn], total[maxn], cnt[maxn];
vector<ll> child[maxn];
ll ans = 1e18;

void dfs(ll i) {
    for (ll j: child[i]) {
        dfs(j);
        subtree[i] += wt[j]*cnt[j] + subtree[j];
        cnt[i] += cnt[j];
    }
    if (child[i].size() == 0) cnt[i]++;
}

void dfs2(ll i, ll par) {
    if (child[i].size() == 0) return;
    ll res;
    if (par == -1) {
        res = subtree[i];    
    }
    else {
        res = total[par] - (wt[i])*cnt[i] + 3*(cnt[1]-cnt[i]);    
        /*
        if (i == 2) {
            cout << total[par] << ' ' << wt[i]*cnt[i] << ' ' << (3*(cnt[1]-cnt[i])) << '\n';
        }
        */
    }
    total[i] = res;
    ans = min(ans,1LL*res);
    for (ll j: child[i]) {
        dfs2(j,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("dirtraverse.in","r",stdin);
    //freopen("dirtraverse.out","w",stdout);
    cin >> N;
    for (ll i = 1; i <= N; i++) {
        string s; ll t; cin >> s >> t;
        wt[i] = s.size() + 1;
        while (t--) {
            ll c; cin >> c;
            child[i].push_back(c);
            parent[c] = i;
        }
    }

    dfs(1); //get subtree sizes
    dfs2(1,-1); //get total for each
    cout << (ans-cnt[1]) << '\n';

    /*
    for (ll i = 1; i <= N; i++) {
        cout << i << ' ' << total[i] << '\n';
    }
    */

    return 0;
}
	

