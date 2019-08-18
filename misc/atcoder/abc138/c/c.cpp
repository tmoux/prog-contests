#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<ld> a(n);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a[i] = (ld)ai;
    }
    sort(a.begin(),a.end());
    for (int i = 1; i < n; i++) {
        a[i] = (a[i]+a[i-1])/2;
    }
    cout << fixed << setprecision(10) << (a[n-1]) << '\n';

}

