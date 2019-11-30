#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    if (s == "SUN") cout << 7 << '\n';
    if (s == "MON") cout << 6 << '\n';
    if (s == "TUE") cout << 5 << '\n';
    if (s == "WED") cout << 4 << '\n';
    if (s == "THU") cout << 3 << '\n';
    if (s == "FRI") cout << 2 << '\n';
    if (s == "SAT") cout << 1 << '\n';
}

