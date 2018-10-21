#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s, t;
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> s >> t;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '*') {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        if (s == t) {
            cout << "YES" << '\n';
        }
        else cout << "NO" << '\n';
        return 0;
    }
    //found pos of *
    string sub1 = s.substr(0,pos);
    string sub2 = t.substr(0,pos);
    if (sub1 != sub2) {
        cout << "NO" << '\n';
        return 0;
    }
    string ends = s.substr(pos+1);
    if (m-(n-pos)+1 < 0) {
        cout << "NO" << '\n';
        return 0;
    }
    string endt = t.substr(m-(n-pos)+1);
    if (m-(n-pos)+1 < pos || ends != endt) {
        cout << "NO" << '\n';
        return 0;
    }
    cout << "YES" << '\n';

    return 0;
}
	

