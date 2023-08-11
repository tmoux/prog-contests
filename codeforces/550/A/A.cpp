#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    vector<int> a, b;
    for (int i = 0; i < n-1; i++) {
        if (s[i] == 'A' && s[i+1] == 'B') a.push_back(i);
        if (s[i] == 'B' && s[i+1] == 'A') b.push_back(i);
    }
    if (a.empty() || b.empty()) {
        cout << "NO" << '\n';
        return 0;
    }
    if (a.front() + 1 < b.back() || b.front() + 1 < a.back()) {
        cout << "YES" << '\n';
    }
    else {
        cout << "NO\n" << '\n';
    }

    return 0;
}

