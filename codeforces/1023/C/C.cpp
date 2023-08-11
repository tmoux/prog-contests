#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; string s;
    cin >> n >> k >> s;
    string res;
    int net = 0;
    for (int i = 0; i < n; i++) {
        if (k <= 0) break;
        if (s[i] == ')') {
            if (net > 0) {
                res += s[i];
                k--;
                net--;
            }
        }
        else {
            if (net + 1 <= k - 1) {
                res += s[i];
                k--;
                net++;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
	

