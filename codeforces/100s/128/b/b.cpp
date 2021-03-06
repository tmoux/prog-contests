#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
string s;
int k;

void f(vector<int> v) {
    vector<int> w;
    ll p = 0, q = 0;
    char c;
    for (c = 'a'; c <= 'z'; c++) {
        w.clear();
        p = q = 0;
        for (int i: v) {
            if (s[i] == c) {
                w.push_back(i+1);
                p++;
                q += n-i;
            }
        }
        if (k < q) break;
        k -= q;
    }
    cout << c;
    if (k < p) return;
    k -= p;
    f(w);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    cin >> k;
    if (k > (1LL*n*(n+1)/2)) {
        //lol cool problem
        cout << "No such line.\n";
        return 0;
    }
    k--;
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(i);
    f(v);
}

