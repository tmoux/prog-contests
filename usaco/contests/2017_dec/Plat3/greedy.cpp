#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, a[maxn];

int num[maxn];
bool unhappy(int x) {
    for (int i = 1; i <= n; i++) num[i] = 0;
    for (int i = 0; i < x-1; i++) num[a[i]]++;
    int r = 0;
    for (int i = 1; i <= n; i++) {
        r += num[i];
        if (r >= i) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("greedy.in","r",stdin); freopen("greedy.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int d; cin >> d;
        a[i] = n-d;
    }
    int lo = 1, hi = n+1; 
    while (lo+1<hi) {
        int m = (lo+hi)>>1;
        if (unhappy(m)) {
            lo = m;        
        }
        else {
            hi = m;
        }
    }
    cout << (n-lo) << '\n';

    return 0;
}
