#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        s += s;
        vector<int> v(n);
        for (int i = 0; i < n; i++) v[i] = i;
        sort(v.begin(),v.end(),[&s,n](int a, int b) { return s.substr(a,n) < s.substr(b,n); });
        cout << v.front() << '\n';
    }

    return 0;
}

