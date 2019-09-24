#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    cout << (6*(n-1)+5)*k << '\n';
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d\n",k*(6*i+1),k*(6*i+2),k*(6*i+3),k*(6*i+5));
    }
}

