#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    cout << n << '\n';
    for (int i = 0; i < n - 1; i++) {
        int r = rand() % i+1;    
        cout << i << ' ' << r << '\n';
    }

    return 0;
}

