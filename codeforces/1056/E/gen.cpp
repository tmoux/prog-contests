#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    while (n--) {
        int r = rand() % 2;
        cout << (r == 0 ? '0':'1');
    }
    cout << '\n';
    while (m--) {
        char c = rand() % 26 + 'a';
        cout << c;
    }
    cout << '\n';

    return 0;
}

