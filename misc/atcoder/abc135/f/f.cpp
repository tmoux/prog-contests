#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s, t;

vector<int> z_function(const string& s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    auto t_z = z_function(t);
    int n = t.size();
    int m = s.size();
    while (s.size() <= n) {
        s += s;
    }
    int period_len = n;
    for (int i = 1; i < n; i++) {
    	//cout << i << ": " << t_z[i] << '\n';
    	if (t_z[i] == n-i && (n % i) == 0) {
    		period_len = min(period_len,i);
    	}
    }
    int num_periods = n / period_len;
    string p = t.substr(0,period_len);
    //cout << p << endl;
    if (s.size() % p.size() == 0) {
    	string r = p;
    	while (r.size() < s.size()) r += p;
        //check if s is cycle of r    
        auto r_z = z_function(r+'#'+s+s);
        for (int i = r.size()+1; i < r_z.size(); i++) {
            if (r_z[i] == r.size()) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }
    s += s;
    while (p.size() <= s.size()) p += p;
    //cout << (p+'#'+s) << endl;
    auto s_z = z_function(p+'#'+s);
    int ans = 0;
    for (int i = p.size()+1; i < s_z.size(); i++) {
    	int d = s_z[i] / period_len;
    	d /= num_periods;
    	//cout << i << ' ' << s_z[i] << ": " << d << '\n';
    	ans = max(ans,d);
    }
    cout << ans << '\n';
}

