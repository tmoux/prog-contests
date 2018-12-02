#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void pv(const vector<int>& v) {
    cout << v.size() << '\n';
    for (int i: v) cout << i << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ll sum = 1LL*n*(n+1)/2;
    if (sum % 2 == 1) {
        cout << "NO\n";
        return 0;
    }
    ll halfsum = sum/2;
    vector<int> a, b;
    for (int i = n; i >= 1; i--) {
        if (i <= halfsum) {
            a.push_back(i);
            halfsum -= i;
        }
        else {
            b.push_back(i);
        }
    }
    cout << "YES" << '\n';
    pv(a);
    pv(b);

    return 0;
}

