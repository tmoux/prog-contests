#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}

void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}

int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int solve(const vector<int>& v) {
    int res = 0;
    for (int i = v.size()-1; i >= 0; i--) {
        madd(res,v.size()-i);
        if (v[i] > 1) madd(res,v[i]);
    }
    return res;
}

int ans = 0;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int ca = 0, cb = 0;
    int add = 0;
    string ns;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == 'a' || c == 'b') {
            ns += c;
        }
    }
    vector<int> v;
    int curr = 0;
    for (int i = 0; i < ns.size(); i++) {
        if (ns[i] == 'a') {
            curr++;
            if (i == ns.size()-1 || ns[i] != ns[i+1]) {
                v.push_back(curr);
                curr = 0;
            }
        }
        else {
            curr = 0;
        }
    }
    int res = 1;
    for (int i: v) {
        res = mult(res,i+1);
    }
    cout << (res+M-1)%M << '\n';
}
