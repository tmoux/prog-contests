#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int G, P; cin >> G >> P;
    set<int> gates;
    for (int i = 1; i <= G; i++) gates.insert(i);
    int ans = 0;
    while (P--) {
        int gi; cin >> gi;
        auto it = gates.upper_bound(gi);
        if (it == gates.begin()) break;
        --it;
        gates.erase(it);
        ans++;
    }
    cout << ans << '\n';

    return 0;
}

