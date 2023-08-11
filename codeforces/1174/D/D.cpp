#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 19;
int n, x;
bool used[1<<maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> x;
    vector<int> ans;
    used[x] = true;
    for (int i = 1; i < (1<<n); i++) {
        if (!used[i]) {
            ans.push_back(i);
            used[i] = true;
            used[i^x] = true;
        }
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        if (i == 0) cout << ans[i] << ' ';
        else {
            cout << (ans[i]^ans[i-1]) << ' ';
        }
    }
    cout << '\n';
}

