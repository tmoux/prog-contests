#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;

bool seen[26], curr[26];
bool check(int x) {
    for (int i = 0; i < 26; i++) {
        seen[i] = true;
        curr[i] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    int lo = 0, hi = s.size();
    while (lo + 1 < hi) {
        int m = (lo+hi)>>1;
        (check(m) ? hi : lo) = m;    
    }
    cout << hi << '\n';

    return 0;
}

