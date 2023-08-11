#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << ' ';
    cout << (rand() % n*n) << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c = (rand() % 26) + 'a';
            cout << c;
        }
        cout << '\n';
    }

    return 0;
}

