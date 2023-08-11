#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    string t; cin >> t;
    string out = t;
    int idx = 0;
    k--;
    while (k) {
        idx++;
        if (idx == out.size()) {
            out += t;
            k--;
        }
        else {
            string sub = out.substr(idx);
            if (sub == t.substr(0,sub.size())) {
                out += t.substr(sub.size());
                k--;
            }
        }
    }
    cout << out << '\n';

    return 0;
}
	

