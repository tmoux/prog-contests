#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int freq[26];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    string s; cin >> s;
    for (char c: s) {
        freq[c-'A']++;
    }
    int res = 0;
    int mini = freq[0];
    for (int i = 0; i < k; i++) {
        mini = min(mini,freq[i]);
    }
    cout << k*mini << '\n';

    return 0;
}

