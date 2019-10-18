#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
string words[105];
string s, sr;

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

vector<int> prefix, suffix;

void amax(int& a, int b) {
    a = max(a,b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    sr = s;
    reverse(begin(sr),end(sr));
    n = s.size();
    prefix.resize(s.size());
    suffix.resize(s.size());
    cin >> m;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> words[i];
        if (words[i].size() == 1) continue;
        //cout << words[i] << ":\n";
        string pmatch = words[i] + "#" + s;
        auto pfx = z_function(pmatch);
        string rev = words[i];
        reverse(begin(rev),end(rev));
        string smatch = rev + "#" + sr;
        auto sfx = z_function(smatch);

        for (int j = 0; j < s.size(); j++) {
            prefix[j] = suffix[j] = 0;
        }
        for (int j = words[i].size()+1, k = 0; j < pfx.size(); j++,k++) {
            if (pfx[j] == 0) continue;
            //cout << k << ": " << (k+pfx[j]-1) << ' ' << pfx[j] << '\n';
            amax(prefix[k+pfx[j]-1],pfx[j]);
        }
        for (int j = sfx.size()-1, k = 0; j >= words[i].size()+1; j--,k++) {
            if (sfx[j] == 0) continue;
            amax(suffix[k-sfx[j]+1],sfx[j]);
        }

        
        for (int j = 1; j < prefix.size(); j++) {
            prefix[j] = max(prefix[j],prefix[j-1]);
        }
        for (int j = suffix.size()-2; j >= 0; j--) {
            suffix[j] = max(suffix[j],suffix[j+1]);
        }

        /*
        for (int j = 0; j < prefix.size(); j++) {
            cout << prefix[j] << ' ';
        }
        cout << '\n';
        for (int j = 0; j < suffix.size(); j++) {
            cout << suffix[j] << ' ';
        }
        cout << '\n';
        */

        bool poss = false;
        for (int j = 0; j < prefix.size(); j++) {
            int s1 = prefix[j] + (j+1<prefix.size() ? suffix[j+1] : 0);
            if (s1 >= words[i].size()) {
                //cout << j << ": " << s1 << '\n';
                poss = true;
                break;
            }
        }
        if (poss) ans++;
    }
    cout << ans << '\n';
}

