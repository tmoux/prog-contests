#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    char minSeen = 'z'+1;
    for (char c: s) {
        if (c <= minSeen) {
            cout << "Mike\n";
        }
        else {
            cout << "Ann\n";
        }
        minSeen = min(minSeen,c);
    }
}

