#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[2*maxn], b[2*maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    priority_queue<pair<int,int>> q;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) q.push({b[i],i});
    }
    ll cnt = 0;
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        int i = p.second;

        int s = b[(i-1+n)%n] + b[(i+1+n)%n];
        if (b[i] <= s) continue;
        int k = (b[i]-a[i])/s;
        cnt += k;
        b[i] -= k*s;

        if (b[i] > a[i] && k > 0) q.push({b[i],i});
    }
    bool poss = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) poss = false;
    }
    if (poss) {
        cout << cnt << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

