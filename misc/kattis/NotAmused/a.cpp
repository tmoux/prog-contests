#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s; cin >> s;
    int day = 1;
    cout << fixed << setprecision(2);
    while (cin >> s) {
        map<string,int> mp;
        map<string,int> ans;
        while (true) {
            cin >> s;
            if (s == "CLOSE") {
                break;
            }
            else if (s == "ENTER") {
                string name; cin >> name;
                int t; cin >> t;
                mp[name] = t;
            }
            else if (s == "EXIT") {
                string name; cin >> name;
                int t; cin >> t;
                ans[name] += t-mp[name];
            }
        }
        cout << "Day " << day++ << '\n';
        for (auto p: ans) {
            cout << p.first << " $";
            cout << (double)p.second/10.0;    
            cout << '\n';
        }
        cout << '\n';
    }
}
