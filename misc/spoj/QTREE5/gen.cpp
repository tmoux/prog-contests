#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 2; i <= n; i++) {
        int r = (rand() % (i-1)) + 1;    
        cout << i << ' ' << r << '\n';
    }
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int t = rand() % 2;
        int r = (rand() % n) + 1;
        cout << t << ' ' << r << '\n';
    }

    return 0;
}

