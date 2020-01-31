#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<vector<int>> g;
    for (int i = 0; i < m; i++) {
        g.push_back(vector<int>(n));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[j][i];
            --g[j][i];
        }
    }
    int ans = 0;
    for (int j = 0; j < m; j++) {
        vector<int> mp(n,0);
        for (int i = 0; i < n; i++) {
            if ((g[j][i]-j) % m == 0 && (g[j][i]-j)/m-j <= m*(n-1)) {
                int target = (g[j][i]-j)/m;
                int turns = target <= i ? i-target : n-(target-i);
                mp[turns]++;
                //cout << i << ", " << turns << endl;
            }
        }
        int add = n;
        for (int i = 0; i < n; i++) {
            add = min(add,i+(n-mp[i]));
            //cout << "turn " << i << ": " << (n-mp[i]) << endl;
        }
        ans += add;
        //cout << j << ": " << add << endl;
    }
    cout << ans << '\n';
}
