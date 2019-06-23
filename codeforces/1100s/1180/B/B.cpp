#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] >= 0) a[i] = -a[i] - 1;
    }
    if (n&1) {
        int minpos = min_element(a.begin(),a.end())-a.begin();
        a[minpos] = -a[minpos] - 1;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

