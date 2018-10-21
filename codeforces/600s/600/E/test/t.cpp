#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll i = 1;
    for (int j = 0; j < 10; j++) {
        i = (i+1)*i;
    }
    cout << i << '\n';

    return 0;
}

