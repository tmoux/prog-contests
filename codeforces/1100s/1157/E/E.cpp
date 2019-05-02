#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn], b[maxn], c[maxn];
multiset<int> ms;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        ms.insert(b[i]);
    }
    for (int i = 1; i <= n; i++) {
        int w = n - a[i];
        if (ms.lower_bound(w) != ms.end()) {
            auto it = ms.lower_bound(w);
            cout << (a[i]+*it)%n;
            ms.erase(it);
        }
        else {
            auto it = ms.begin();
            cout << (a[i]+*it)%n;
            ms.erase(it);
        }
        cout << ' ';
    }

    return 0;
}

