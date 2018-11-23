#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    for (int r = 1; r <= 5; r++) {
        int c = n/r;
        if (c+(n%r!=0) > 20) continue;
        int rem = n % r;
        cout << r << ' ' << (c+(n%r!=0)) << '\n';
        for (int i = 0; i < n;) {
            int len = c;
            bool is = n%r==0 ? true : false;
            if (rem) {
                rem--;
                len++;
                is = true;
            }
            string q = s.substr(i,len);
            cout << q;
            if (!is) cout << '*';
            cout << '\n';
            i += len;
        }
        return 0;
    }

    return 0;
}

