#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int c1, c2, c3, c4; cin >> c1 >> c2 >> c3 >> c4;
    if (c1 == c4 && (c1 > 0 || (c1 == 0 && c3 == 0))) {
        cout << 1 << '\n';    
        return 0;
    }
    cout << 0 << '\n';


    return 0;
}

