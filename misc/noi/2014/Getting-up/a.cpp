#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<string,int>> v;

int get(int i, int b) {
    for (auto p: v) {
        //cout << b << ' ';
        if (p.first == "AND") {
            b &= 1&(p.second>>i);
        }
        else if (p.first == "OR") {
            b |= 1&(p.second>>i);
        }
        else {
            b ^= 1&(p.second>>i);
        }
        /*
        cout << p.first << ' ' << p.second << ": " << b;
        cout << '\n';
        */
    }
    return b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        int x; cin >> s >> x;
        v.push_back({s,x});
    }
    int ans = 0;
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        int l1 = get(i,0);
        int l2 = get(i,1);
        //cout << i << ": " << l1 << ' ' << l2 << '\n';
        if (l2 > l1 && (ans|(1<<i)) <= m) {
            ans |= (1<<i);
            res |= l2<<i;
        }
        else res |= l1<<i;
    }
    cout << res << '\n';
}

