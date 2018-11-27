#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<bool> s(101,true);
    while (n--) {
        int r; cin >> r;
        vector<bool> d(101,false);
        while (r--) {
            int a; cin >> a;
            d[a] = true;
        }
        for (int i = 1; i <= 100; i++) {
            s[i] = s[i] & d[i];
        }
    }
    for (int i = 1; i <= 100; i++) {
        if (s[i]) cout << i << ' ';
    }

    return 0;
}

