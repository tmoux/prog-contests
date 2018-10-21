#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n;
    set<ll> A, B;
    ll a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a += ai;
        A.insert(a);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        b += ai;
        B.insert(b);
    }
    if (a != b) {
        cout << "-1\n";
        return 0;
    }
    int res = 0;
    for (ll i: A) {
        if (B.count(i)) res++;
    }
    cout << res << '\n';
    
    return 0;
}

