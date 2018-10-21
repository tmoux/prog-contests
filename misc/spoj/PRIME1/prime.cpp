#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime(int x) {
    if (x == 1) return false;
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

void solve() {
    int m, n; scanf("%d %d",&m,&n);
    for (int i = m; i <= n; i++) {
        if (isPrime(i)) {
            printf("%d\n",i);
        }
    }
    printf("\n");
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; scanf("%d",&t);
    while (t--) solve();
    return 0;
}
	

