#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<int> v(m);
    vector<int> ans(m);
    ll sum = 0;
    int mx = 0;
    for (int i = 0; i < m; i++) {
        cin >> v[i];
        sum += v[i];
        if (i+v[i] > n) {
            cout << -1 << '\n';
            return 0;
        }
        mx = max(mx,i+v[i]);
    }
    if (sum < n) {
        cout << -1 << '\n';
        return 0;
    }
    int move = max(0,n-mx);
    ans[0] = 0;
    //cout << "move = " << move << endl;
    for (int i = 1; i < m; i++) {
        int shift = min(move,v[i-1]-1);
        shift = min(shift,(n-v[i])-(ans[i-1]+1));
        move -= shift;
        ans[i] = ans[i-1] + 1 + shift;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i]+1 << ' ';
    }
    cout << '\n';
}
