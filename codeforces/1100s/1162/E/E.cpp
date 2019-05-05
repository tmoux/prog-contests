#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1,a+n+1);
    int mn = a[1];
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == mn) cnt++;
    }
    cout << (cnt > n/2 ? "Bob" : "Alice") << '\n';
}

