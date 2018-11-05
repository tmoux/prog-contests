#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, a[maxn];

bool check(int x) {
    int a1 = 0, b1 = 0;
    for (int i = 0; i < n; i++) {
        a1 += a[i];
        b1 += x-a[i];
    }
    return b1 > a1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];        
        mx = max(mx,a[i]);
    }
    int lo = mx;
    int hi = 1000000;
    for (int i = lo; i < lo + 5; i++) {
        if (check(i)) {
            cout << i << '\n';
            return 0;
        }
    }
    while (lo + 1 < hi) {
        int m = (lo+hi)/2;
        if (check(m)) {
            hi = m;
        }
        else lo = m;
    }
    cout << hi+1 << '\n';


    return 0;
}

