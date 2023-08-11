#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MX = 2e6+6;
int sd[MX];
int pre_sd[MX];
int ans[155][10];

int s(int x) {
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

string ans0[155];
string ans1[155];
string nxt(string s) {
    if (s[0] == '9') {
        return "1" + s;
    }
    else {
        s[0]++;
        return s;
    }
}

string int_to_string(int x) {
    string ret = "";
    while (x) {
        ret += (char)((x%10)+'0');
        x /= 10;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < MX; i++) {
        sd[i] = s(i);
        pre_sd[i] = sd[i];
        if (i > 0) pre_sd[i] += pre_sd[i-1];
    }
    memset(ans,-1,sizeof ans);
    for (int k = 2; k <= 9; k++) {
        for (int i = 0; i+k < MX; i++) {
            int sum = pre_sd[i+k] - (i==0?0:pre_sd[i-1]);
            if (ans[sum][k] == -1) {
                ans[sum][k] = i;
            }
        }
    }
    ans0[0] = "0";
    for (int i = 1; i <= 150; i++) {
        ans0[i] = nxt(ans0[i-1]);
    }

    for (int i = 0; i <= 150; i++) {
        ans1[i] = "-1";
    }
    int mx = 0;
    map<int,int> mp;
    for (int i = 0; i <= 210000; i++) {
        if (!mp.count(s(i)+s(i+1))) {
            mp[s(i)+s(i+1)] = i;
        }
    }
    for (auto p: mp) {
        ans1[p.first] = int_to_string(p.second);
        //if (p.first % 2 == 0) cout << p.first << ": " << p.second << ' ' << p.second+1 << '\n';
    }
    ans1[1] = "0";
    for (int i = 11; i <= 150; i++) {
        if (ans1[i] == "-1" && ans1[i-2] != "-1") {
            ans1[i] = nxt(ans1[i-2]);
        }
    }
    /*
    for (int i = 1; i <= 150; i++) {
        cout << i << ": " << ans1[i] << endl;
    }
    for (auto p: mp) {
        cout << p.first << ": " << p.second << ' ' << ans1[p.first] << endl;
    }
    */
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        //cout << n << ' ' << k << ": ";
        if (k == 0) {
            cout << ans0[n] << '\n';
        }
        else if (k == 1) {
            cout << ans1[n] << '\n';
        }
        else {
            cout << ans[n][k] << '\n';
        }
    }
}
