#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    if (n % 2 == 0) {
        cout << (1LL<<(n/2)) << '\n';
    }
    else {
        cout << 0 << '\n';    
    }

}

