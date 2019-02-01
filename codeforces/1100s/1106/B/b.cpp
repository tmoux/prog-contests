#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int rem[maxn], cost[maxn];
int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> rem[i+1];
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i+1];
    }
    vector<int> order;
    for (int i = 1; i <= n; i++) order.push_back(i);
    sort(order.begin(),order.end(),[](int a, int b) {return cost[a] < cost[b];});
    /*
    for (int i = 0; i < n; i++) {
        cout << order[i] << ' ';
    }
    cout << '\n';
    */
    bool done = false;
    int start = 0;
    while (m--) {
        int t, d; cin >> t >> d;
        if (done) {
            cout << 0 << '\n';
            continue;
        }
        ll total = 0;
        int take = min(d,rem[t]);
        d -= take;
        rem[t] -= take;
        total += 1LL*take*cost[t];
        for (int i = start; i < n && d > 0; i++) {
            int j = order[i];
            int take = min(d,rem[j]);
            d -= take;
            rem[j] -= take;
            if (!rem[j]) start = i + 1;
            total += 1LL*take*cost[j];
        }
        if (d > 0) {
            done = true;
            cout << 0 << '\n';
            continue;
        }
        cout << total << '\n';
    }
}

