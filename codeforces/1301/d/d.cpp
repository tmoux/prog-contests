#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m, k;

bool flipped = false;
vector<pair<int,string>> v;
bool get() {
    v.clear();
    int kk = k;
    if (n-1 > 0) v.push_back({min(kk,n-1),"D"});
    kk -= min(kk,n-1);
    if (kk == 0) return true;
    if (n-1 > 0) v.push_back({min(kk,n-1),"U"});
    kk -= min(kk,n-1);
    if (kk == 0) return true;
    for (int i = 2; i <= m; i++) {
        v.push_back({1,"R"});
        kk--;
        if (kk == 0) return true;
        int take = 3*(n-1);
        if (kk < take) {
            int quo = kk/3;
            int rem = kk%3;
            if (quo > 0) v.push_back({quo,"DLR"});
            string st = "";
            if (rem != 0) {
                string st;
                if (rem == 1) st = "D";
                else if (rem == 2) st = "DL";
                v.push_back({1,st});
            }
            return true;
        }
        else {
            if (n-1 > 0) v.push_back({n-1,"DLR"});
            kk -= take;
            if (kk == 0) return true;
            if (n-1 > 0) v.push_back({min(kk,n-1),"U"});
            kk -= min(kk,n-1);
            if (kk == 0) return true;
        }
    }
    if (m-1 > 0) v.push_back({min(kk,m-1),"L"});
    kk -= min(kk,m-1);
    if (kk == 0) return true;
    return false;
}

void output() {
    cout << "YES\n";
    cout << v.size() << '\n';
    for (auto p: v) {
        if (flipped) {
            for (char& c: p.second) {
                if (c == 'U') c = 'R';
                else if (c == 'D') c = 'L';
                else if (c == 'R') c = 'D';
                else if (c == 'L') c = 'U';
            }
        }
        cout << p.first << ' ' << p.second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    if (n == 2 && m == 2) {
        if (k > 8) {
            cout << "NO\n";
        }
        else {
            string s = "RDLUDRUL";
            cout << "YES\n";
            cout << k << '\n';
            for (int i = 0; i < k; i++) {
                cout << 1 << " " << s[i] << '\n';
            }
        }
        return 0;
    }
    if (get()) {
        output();
    }
    else {
        flipped = true;
        swap(n,m);
        if (get()) {
            output();
        }
        else {
            cout << "NO\n";
        }
    }
}
