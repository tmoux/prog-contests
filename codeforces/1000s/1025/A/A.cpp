#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<char,int> freq;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    for (char c: s) freq[c]++;
    bool poss = false;
    if (freq.size() == 1) {
        cout << "Yes" << '\n';
        return 0;
    }
    for (auto p: freq) {
        if (p.second >= 2) poss = true;
    }
    cout << (poss ? "Yes" : "No") << '\n';

    return 0;
}
	

