#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) x.begin(),x.end()

const int maxn = 1e5+5;
int n, k, a[maxn], b[maxn];
bool taken[maxn];
vector<int> times[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];    
        taken[a[i]] = true;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        times[a[i]].push_back(b[i]);
    }
    multiset<int> extras;
    for (int i = 1; i <= k; i++) {
        sort(all(times[i]),greater<int>());
        for (int j = 1; j < times[i].size(); j++) {
            extras.insert(times[i][j]);
        }
    }
    ll ans = 0;
    for (int i = 1; i <= k; i++) {
        if (!taken[i]) {
            ans += *extras.begin();
            extras.erase(extras.begin());
        }
    }
    cout << ans << '\n';
    

    return 0;
}

