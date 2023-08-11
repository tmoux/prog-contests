#include <bits/stdc++.h>
using namespace std;

int ans[1005];
int main()
{
    string s; cin >> s;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == 'a') {
            ans[i-1] ^= 1;
            ans[i] = 1;
        }
    }
    for (int i = 0; i < s.size(); i++) 
        cout << ans[i] << ' ';


    return 0;
}

