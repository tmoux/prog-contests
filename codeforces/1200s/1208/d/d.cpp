#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
ll s[maxn];

//3 1 5 2 4
//0 0 4 1 6
//

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    s[n+1] = (1LL*n*(n-1))/2;

}

