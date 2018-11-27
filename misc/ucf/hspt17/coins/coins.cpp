#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        string other = s=="Matthew"?"Bill":"Matthew";
        bool win1 = (n % (k+1) != 0);
        printf("Game #%d: %s\n",i,(win1?s:other).c_str());
    }

    return 0;
}

