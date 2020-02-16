#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Num
{
    string s;
    int cnt = 0;
    void add() {
        for (char c: s) if (c == '?') cnt++;
    }
};

int int_of_string(string s) {
    int res = 0;
    int mult = 1;
    for (int i = s.size()-1; i >= 0; i--) {
        res += (s[i]-'0')*mult;
        mult *= 10;
    }
    return res;
}

string string_of_int(int x) {
    string ret = "";
    while (x > 0) {
        ret += (x%10)+'0';
        x /= 10;
    }
    reverse(ret.begin(),ret.end());
    if (ret.empty()) return "0";
    return ret;
}

bool match(string a, string b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != '?' && a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Num a, b, c;
    string x;
    cin >> a.s >> x >> b.s >> x >> c.s;
    a.add();
    b.add();
    c.add();
    vector<Num> v = {a,b,c};
    sort(v.begin(),v.end(),[](auto a, auto b) {
        return a.cnt < b.cnt;});
    a = v[0];
    b = v[1];
    c = v[2];
    int n = a.cnt + b.cnt;
    int mx = 1;
    for (int i = 0; i < n; i++) {
        mx *= 10;
    }
    int ans = 0;
    for (int mask = 0; mask < mx; mask++) {
        int cp = mask;
        string aa = a.s, bb = b.s, cc = c.s;
        for (int i = 0; i < a.cnt; i++) {
            int j = aa.find_first_of("?",0);
            aa[j] = '0'+(cp%10);
            cp /= 10;
        }
        for (int i = 0; i < b.cnt; i++) {
            int j = bb.find_first_of("?",0);
            bb[j] = '0'+(cp%10);
            cp /= 10;
        }
        //cout << aa << ' ' << bb << ' ' << cc << endl;
        if ((aa.size() == 1 || aa[0] != '0') && (bb.size() == 1 || bb[0] != '0')) {
            int x = int_of_string(aa) ^ int_of_string(bb);
            //cout << aa << ' ' << bb << ": " << x << ' ' << match(c.s,string_of_int(x)) <<  endl;
            if (match(c.s,string_of_int(x))) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}
