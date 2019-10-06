#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    int K;
    cin >> s >> K;
    vector<int> v;
    int curr = 0;
    for (int i = 0; i < s.size(); i++) {
        curr++;
        if (i == s.size()-1 || s[i] != s[i+1]) {
            v.push_back(curr);
            curr = 0;
        }
    }
    if (v.size() == 1) {
        ll ans = (1LL*s.size()*K)/2;
        cout << ans << '\n';
        return 0;
    }
    ll sum = 0;
    for (int i: v) {
        sum += i/2;
    }
    if (s[0] != s.back()) {
        cout << sum*K << '\n';
    }
    else {
        vector<int> u = v;
        u[0] += u.back();
        u.pop_back();
        ll ans = 0;
        for (int i: u) {
            ans += i/2;
        }
        ans *= (K-1);
        ans += sum;
        cout << ans << '\n';
    }
}

