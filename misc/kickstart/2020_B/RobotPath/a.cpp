#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll M = 1000000000;
pair<ll,ll> operator+(pair<ll,ll> a, pair<ll,ll> b) {
    return {(a.first+b.first)%M,(a.second+b.second)%M};
}
map<char,pair<ll,ll>> mp = {
    {'S',{0,1}},
    {'N',{0,-1}},
    {'E',{1,0}},
    {'W',{-1,0}}
};
string s;
pair<ll,ll> norm(pair<ll,ll> p) {
    return {(p.first+M)%M,(p.second+M)%M};
}
pair<ll,ll> solve(int l, int r) {
    //cout << l << ' ' << r << endl;
    pair<ll,ll> ret;
    for (int i = l; i <= r; i++) {
        if ('2' <= s[i] && s[i] <= '9') {
            ll mult = s[i]-'0';
            int bal = 1;
            int r = i+2;
            while (bal > 0) {
                r++;
                if (s[r] == '(') bal++;
                else if (s[r] == ')') bal--;
            }
            auto p = solve(i+2,r-1);
            p = make_pair((1LL*mult*p.first)%M,(1LL*mult*p.second)%M);
            ret = ret + p;
            i = r;
        }
        else {
            assert(mp.count(s[i]));
            ret = ret + mp[s[i]];
        }
    }
    return norm(ret);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        cin >> s;
        auto ans = solve(0,s.size()-1);
        cout << (ans.first+1) << ' ' << (ans.second+1) << '\n';
    }
}

