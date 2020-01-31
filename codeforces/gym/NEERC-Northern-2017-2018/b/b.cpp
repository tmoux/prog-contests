#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("boolean.in","r",stdin); freopen("boolean.out","w",stdout);
    string s; cin >> s;
    vector<string> v;
    stringstream check1(s);
    set<char> a, b, c;
    string t;
    while (getline(check1,t,'|')) {
        if (t.size() == 1) {
            a.insert(t[0]);
            c.insert(t[0]);
        }
        else {
            b.insert(t[1]);
            c.insert(t[1]);
        }
    }
    for (char cc: a) {
        if (b.count(cc)) {
            //duplicate
            cout << (1LL<<c.size()) << '\n';
            return 0;
        }
    }
    cout << ((1LL<<c.size())-1) << endl;
}

