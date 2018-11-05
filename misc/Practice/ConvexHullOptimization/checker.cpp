#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        int m = 987654321;
        for (int j = 0; j < n; j++) {
            m = min(m,v[j].first*x+v[j].second);
        }
        cout << m << '\n';
    }

    return 0;
}

