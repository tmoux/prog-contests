#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<int,vector<string>> mp = {
    {0,{"xxxxx",
        "x...x",
        "x...x",
        "x...x",
        "x...x",
        "x...x",
        "xxxxx"}},

    {1,{"....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x"}},

    {2,{"xxxxx",
        "....x",
        "....x",
        "xxxxx",
        "x....",
        "x....",
        "xxxxx"}},

    {3,{"xxxxx",
        "....x",
        "....x",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"}},

    {4,{"x...x",
        "x...x",
        "x...x",
        "xxxxx",
        "....x",
        "....x",
        "....x"}},

    {5,{"xxxxx",
        "x....",
        "x....",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"}},

    {6,{"xxxxx",
        "x....",
        "x....",
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx"}},

    {7,{"xxxxx",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x"}},

    {8,{"xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx"}},

    {9,{"xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"}},

    {10,{".....", //plus
         "..x..",
         "..x..",
         "xxxxx",
         "..x..",
         "..x..",
         "....."}},
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s;
    vector<string> v;
    for (int i = 0; i < 7; i++) {
        cin >> s;
        v.push_back(s);
    }
    int n = (v[0].size()+1)/6;
    int a = 0, b = 0;
    bool plus = false;
    for (int i = 0; i < n; i++) {
        vector<string> add;
        for (int j = 0; j < 7; j++) {
            add.push_back(v[j].substr(6*i,5));
        }
        if (mp[10] == add) {
            plus = true;
            continue;
        }
        else if (!plus) {
            int d;
            for (d = 0; d <= 9; d++) {
                if (mp[d] == add) break;
            }
            a = a*10 + d;
        }
        else if (plus) {
            int d;
            for (d = 0; d <= 9; d++) {
                if (mp[d] == add) break;
            }
            b = b*10 + d;
        }
        /*
        for (auto ss: add) {
            cout << ss << '\n';
        }
        cout << '\n';
        */
    }
    int c = a+b;
    vector<int> d;
    while (c > 0) {
        d.push_back(c%10);
        c /= 10;
    }
    reverse(d.begin(),d.end());
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < d.size(); i++) {
            cout << mp[d[i]][j];
            if (i < d.size()-1) cout << '.';
        }
        cout << '\n';
    }
}
