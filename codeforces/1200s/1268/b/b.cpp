#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a[maxn];
ll c[2];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        c[i&1] += a[i]/2;
        c[(i&1)^1] += (a[i]+1)/2;
    }
    cout << min(c[0],c[1]) << endl; 
}

