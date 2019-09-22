#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int pos = 1, neg = 0;
    ll pans = 0, nans = 0;
    int curr = 1;
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) curr *= -1;
        if (curr > 0) {
            pans += pos;
            nans += neg;
            //cout << i << ": " << pos << ' ' << neg << '\n';
        }
        else {
            pans += neg;
            nans += pos;
            //cout << i << ": " << neg << ' ' << pos << '\n';
        }
        if (curr > 0) pos++;
        else neg++;
    }
    cout << nans << ' ' << pans << '\n';
}

