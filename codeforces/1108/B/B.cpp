#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    multiset<int> ms;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        ms.insert(ai);                    
    }
    int mx = *ms.rbegin();
    for (int i = 1; i*i <= mx; i++) {
        if (mx % i == 0) {
            auto it = ms.find(i);
            assert(it != ms.end());
            ms.erase(it);
            if (i*i != mx) {
                auto it2 = ms.find(mx/i);
                assert(it2 != ms.end());
                ms.erase(it2);
            }
        }
    }
    int mx2 = *ms.rbegin();
    cout << mx << ' ' << mx2 << '\n';

    return 0;
}

