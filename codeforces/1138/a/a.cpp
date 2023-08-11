#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a;
    int cur = -1, len = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai == cur) len++;
        else {
            if (cur != -1) a.push_back(len);
            len = 1;
            cur = ai;
        }
    }
    a.push_back(len);
    int ans = 0;
    for (int i = 0; i < a.size() - 1; i++) {
        ans = max(ans,2*min(a[i],a[i+1]));
    }
    cout << ans << '\n';
}

