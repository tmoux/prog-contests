#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string t; cin >> t;
    int step = 1;
    for (int i = 0; i < n; i += step++) {
        cout << t[i];    
    }
    cout << '\n';

    return 0;
}

