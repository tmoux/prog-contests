#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;

vector<pair<int,int>> lines;

bool tr(int k) {
    vector<pair<int,int>> res;
    //cout << "trying " << k << '\n';
    for (auto p: lines) {
        pair<int,int> r = {(p.first+k)%n,(p.second+k)%n};
        if (r.first > r.second) swap(r.first,r.second);
        res.push_back(r);
    }
    sort(res.begin(),res.end());
    return lines == res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        if (a > b) swap(a,b);
        lines.push_back({a,b});
    }
    sort(lines.begin(),lines.end());
    for (int k = 1; k*k <= n; k++) {
        if (n % k == 0) {
            if (tr(k) || (n/k < n && tr(n/k))) {
                //cout << k << '\n';
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";
    return 0;
}

