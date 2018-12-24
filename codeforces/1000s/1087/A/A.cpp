#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int i = (s.size() % 2 == 0 ? s.size()/2-1 : s.size()/2);
    int l = i, r = i;
    cout << s[i];
    for (int i = 0; i < s.size()-1; i++) {
        if (i % 2 == 0) {
            r++;
            cout << s[r];
        }
        else {
            l--;
            cout << s[l];
        }
    }

    return 0;
}

