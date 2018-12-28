#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    srand(time(NULL));
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int r = rand() % (2*10000000) - 10000000;
        cout << r << ' ';
    }
    cout << '\n';

    return 0;
}

