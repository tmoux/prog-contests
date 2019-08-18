#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[2*maxn], b[2*maxn];

pair<ll,vector<int>> check(int c[]) {
    ll cnt = 0;
    priority_queue<pair<int,int>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({c[i],i});
    }

    for (int j = 0; j < 30*n; j++) {
        auto p = pq.top(); pq.pop();
        int i = p.second;
        int s = c[(i-1+n)%n] + c[(i+1)%n];
        if (s == 0) continue;
        cnt += c[i]/s;
        c[i] %= s;
        pq.push({c[i],i});
    }
    vector<int> res;
    for (int i = 0; i < n; i++) {
        res.push_back(c[i]);
    }
    return {cnt,res};
}

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
    auto p1 = check(a);
    auto p2 = check(b);
    if (p1.second != p2.second) {
        cout << -1 << '\n';
    }
    else {
        cout << (p2.first - p1.first) << '\n';
    }
    return 0;
    cout << p1.first << '\n';
    for (int i = 0; i < n; i++) {
        cout << p1.second[i] << ' ';
    }
    cout << '\n';

    cout << p2.first << '\n';
    for (int i = 0; i < n; i++) {
        cout << p2.second[i] << ' ';
    }
    cout << '\n';
}

