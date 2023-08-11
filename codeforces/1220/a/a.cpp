#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    map<char,int> mp;
    for (char c: s) {
        mp[c]++;
    }
    string ans;
    while (mp['o'] > 0 && mp['n'] > 0 && mp['e'] > 0) {
        ans += '1';
        mp['o']--;
        mp['n']--;
        mp['e']--;
    }
    while (mp['z'] > 0 && mp['e'] > 0 && mp['r'] > 0 && mp['o'] > 0) {
        ans += '0';
        mp['z']--;
        mp['e']--;
        mp['r']--;
        mp['o']--;
    }
    for (char c: ans) {
        cout << c << ' ';
    }
    cout << '\n';
}

