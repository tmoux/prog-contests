#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, r; cin >> n >> m >> r;
    vector<int> buy;
    int mnbuy = 99999;
    for (int i = 0; i < n; i++) {
        int si; cin >> si;
        buy.push_back(si);
        mnbuy = min(mnbuy,si);
    }
    int mxsell = -1;
    vector<int> sell;
    for (int i = 0; i < m; i++) {
        int bi; cin >> bi;
        sell.push_back(bi);
        mxsell = max(mxsell,bi);
    }
    if (mnbuy >= mxsell) {
        cout << r << '\n';
    }
    else {
        int num = r / mnbuy;
        r %= mnbuy;
        r += num*mxsell;
        cout << r << '\n';
    }

    return 0;
}

