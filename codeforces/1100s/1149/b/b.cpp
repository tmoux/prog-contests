#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
string s;
string rel[3];

bool check() {
    int pt[3] = {0,0,0};
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < 3; j++) {
            if (pt[j] < rel[j].size() && s[i] == rel[j][pt[j]]) {
                pt[j]++;
                break;
            }
        }
    }
    //cout << "pts: " << pt[0] << ' ' << pt[1] << ' ' << pt[2] << '\n';
    return pt[0] == rel[0].size() && pt[1] == rel[1].size() && pt[2] == rel[2].size();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q >> s;
    while (q--) {
        char c; cin >> c;
        if (c == '+') {
            int i; char c; cin >> i >> c;
            i--;
            rel[i] += c;            
        }
        else {
            int i; cin >> i;
            i--;
            assert(!rel[i].empty());
            rel[i].pop_back();
        }
        cout << q << ":\n";
        for (int i = 0; i < 3; i++) {
            cout << rel[i] << '\n';
        }
        bool poss = check();
        cout << (poss?"YES":"NO") << '\n';
    }
}
