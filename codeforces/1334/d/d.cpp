#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        ll l, r; cin >> n >> l >> r;
        ll cnt = 1;
        vector<int> ans;
        for (int i = 1, nn = n; i < n; i++, nn--) {
            if (l >= cnt + 2*(nn-1) || cnt > r) {
                cnt += 2*(nn-1);
                continue;
            }
            else {
                for (int j = 0; j < 2*(nn-1); j++) {
                    if (l <= cnt && cnt <= r) {
                        if (j % 2 == 0) {
                            ans.push_back(i);
                        }
                        else {
                            ans.push_back((j+1)/2+i);
                        }
                    }
                    cnt++;
                }
            }
        }
        if (r == 1LL*n*(n-1)+1) ans.push_back(1);
        for (auto i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

