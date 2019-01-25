#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    string ret;
    int ans = 0;
    for (char c: s) {
        ret += c;
        while (ret.size() > 1 && ret[ret.size()-1] == ret[ret.size()-2]) {
            ret.pop_back();
            ret.pop_back();
            ans++;
        }
    }
    cout << (ans % 2 == 0 ? "No" : "Yes") << '\n';

    return 0;
}

