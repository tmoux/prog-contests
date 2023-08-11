#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<int> a(4);
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    if (a[0] + a[3] == a[1] + a[2]) {
        cout << "YES\n";
    }
    else {
        if (a[3] == a[0] + a[1] + a[2]) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

