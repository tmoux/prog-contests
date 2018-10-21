#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    multiset<int> a;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.insert(ai);
    }
    int mx = *a.rbegin() + m;
    for (int i = 0; i < m; i++) {
        auto it = a.begin();
        a.insert(*it+1);
        a.erase(it);
    }
    int mn = *a.rbegin();
    cout << mn << ' ' << mx << '\n';

    return 0;
}

