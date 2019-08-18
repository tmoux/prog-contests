#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    map<char,int> mp;
    for (char c: s) {
        mp[c]++;
    }
    if (mp.size() != 2) {
        cout << "No\n";
    }
    else {
        if (mp.begin()->second != 2 || mp.rbegin()->second != 2) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
        }
    }
}

