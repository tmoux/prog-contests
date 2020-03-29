#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 205;
int n, m, k;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    vector<char> ans;
    for (int i = 0; i < n-1; i++) {
        ans.push_back('U');
    }
    for (int i = 0; i < m-1; i++) {
        ans.push_back('L');
    }
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m-1; j++) {
                ans.push_back('R');
            }
        }
        else {
            for (int j = 0; j < m-1; j++) {
                ans.push_back('L');
            }
        }
        if (i+1 != n) ans.push_back('D');
    }
    cout << ans.size() << '\n';
    for (auto c: ans) {
        cout << c;
    }
    cout << '\n';
}

