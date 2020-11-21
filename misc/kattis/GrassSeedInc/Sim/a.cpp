#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(string s) {
    deque<char> ret;
    string prep;
    auto prepend = [&ret,&prep]() {
        if (!prep.empty()) {
            for (int i = (int)(prep.size())-1; i >= 0; i--) {
                ret.push_front(prep[i]);
            }
            prep.clear();
        }
    };
    int mode = 0; //0 = normal, 1 = prepend
    for (char c : s) {
        if (c == '<') {
            if (mode == 0) {
                if (!ret.empty()) ret.pop_back();
                else if (!prep.empty()) prep.pop_back();
            }
            else {
                if (!prep.empty()) prep.pop_back();
            }
        }
        else if (c == '[') {
            if (mode == 0) {
                mode = 1;
                assert(prep.empty());
            }
            else {
                prepend();
            }
        }
        else if (c == ']') {
            if (mode == 1) {
                mode = 0;
                prepend();
            }
        }
        else {
            if (mode == 0) ret.push_back(c);
            else prep += c;
        }
    }
    prepend();
    for (auto c: ret) {
        cout << c;
    }
    cout << '\n';
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    string s; 
    getline(cin,s);
    while (t--) {
        getline(cin,s);
        solve(s);
    }
}
