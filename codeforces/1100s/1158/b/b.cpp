#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool unique(string s, int k) {
    map<string,int> mp;
    for (int i = 0; i+k <= s.size(); i++) {
        mp[s.substr(i,k)]++;
    }
    int c1 = 0;
    for (auto p: mp) {
        if (p.second == 1) c1++;
    }
    return c1 == 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int k; cin >> k; 
    if (k == 1) {
        cout << 1;
        for (int i = 0; i < n-1; i++) {
            cout << 0;
        }
        cout << '\n';
        return 0;
    }
    int space = (n-k)/2;
    string s;
    for (int i = 0; i < n; i++) {
        if (i % (space+1) == 0) s += '1';
        else s += '0';
    }
    /*
    bool poss = true;
    for (int i = 1; i < k; i++) {
        if (unique(s,i)) {
            poss = false;
            break;
        }
    }
    */
    cout << s << endl;
    //assert(poss&&unique(s,k));
}

