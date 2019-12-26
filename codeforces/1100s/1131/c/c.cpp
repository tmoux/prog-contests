#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    deque<int> d;
    for (int i = 0; i < n; i++) {
        if (i&1) d.push_back(a[i]);
        else d.push_front(a[i]);
    }
    for (int i: d) {
        cout << i << ' ';
    }
    cout << '\n';
}

