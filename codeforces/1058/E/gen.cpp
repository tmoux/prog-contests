#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << (rand() % 1000000000) << ' ';
    }

    return 0;
}

