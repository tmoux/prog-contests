#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<int,int> mp;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    while (q--) {
        char c; cin >> c;
        int i; cin >> i;
        if (c == 'L') {
            ll res = 0;
            for (auto& p: mp) {
                if (p.first <= i) {
                    res += p.second;
                }
            }
            cout << i+res << '\n';
        }
        else {
            mp[i]++;     
        }
    }

    return 0;
}

