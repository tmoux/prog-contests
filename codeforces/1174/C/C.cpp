#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n+5);
    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i] != 0) continue;
        cnt++;
        for (int j = i; j <= n; j += i) {
            if (a[j] == 0) a[j] = cnt;
        }
    }
    for (int i = 2; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

