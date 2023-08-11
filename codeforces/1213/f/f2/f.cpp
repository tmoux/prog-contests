#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, p[maxn], q[maxn];
int k;
int ord[maxn];

char ans[maxn];
int mn[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        ord[p[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
        q[i] = p[q[i]];
    }
    int minSeen = q[n];
    set<int> s;
    for (int i = n; i >= 1; i--) {
        minSeen = min(minSeen,q[i]);
        mn[i] = minSeen;
        s.insert(minSeen);
    }
    if (s.size() < k) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    map<int,int> mp;
    int pt = 0;
    for (int i: s) {
        mp[i] = pt++;
    }
    for (int i = 1; i <= n; i++) {
        ans[p[i]] = (char)(min(k,mp[mn[i]])+'a');
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i];
    }
    cout << '\n';
}

