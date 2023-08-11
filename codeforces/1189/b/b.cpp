#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];

bool check(deque<int> d) {
    /*
    for (int i: d) {
        cout << i << ' ';
    }
    cout << '\n';
    */
    for (int i = 0; i < n; i++) {
        if (d[i] >= d[(i-1+n)%n] + d[(i+1)%n]) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    deque<int> d;
    sort(a+1,a+1+n);
    for (int i = n; i >= 1; i--) {
        if (i&1) {
            d.push_back(a[i]);
        }
        else d.push_front(a[i]);
    }
    if (check(d)) {
        cout << "YES" << '\n';
        for (int i: d) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }
}

