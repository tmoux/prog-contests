#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    const int n = 100000;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int r = (rand() % 1000000) + 14000000;
        cout << r << ' ';
    }

    return 0;
}

