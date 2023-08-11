#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<bool> pts(m+1,false);
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        for (int j = l; j <= r; j++) {
            pts[j] = true;
        }
    }

    vector<int> ans;
    for (int i = 1; i <= m; i++) {
        if (!pts[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << '\n';
    for (int j: ans) {
        cout << j << ' ';
    }

    return 0;
}
	

