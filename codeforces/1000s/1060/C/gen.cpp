#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++) {
        int r = rand() % 2000 + 1;
        cout << r << ' ';
    }
    cout << '\n';
    for (int i = 0; i < m; i++) {
        int r = rand() % 2000 + 1;
        cout << r << ' ';
    }
    cout << '\n';
    int x = rand() % 2000000000 + 1;
    cout << x << '\n';


    return 0;
}

