#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a, b;
string s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        // a > b
        cin >> s;
        n = s.size();
        vector<int> sz(n,0);
        vector<int> segs;
        for (int i = 0; i < n; i++) {
            if (s[i] != '.') continue;
            sz[i] = i == 0 ? 1 : sz[i-1] + 1;
            if (i == n-1 || s[i+1] != '.') 
                segs.push_back(sz[i]);
        }
        int numSmall = 0;
        int numBig = 0;
        for (int i: segs) {
            if (b <= i && i < a) numSmall++;
            else if (i >= 2*b) numBig++;
        }
        //cout << numSmall << ' ' << numBig << '\n';
        if (numSmall > 0) {
            cout << "NO\n";
        }
        else {
            if (numBig >= 2) {
                cout << "NO\n";
            }
            else if (numBig == 0) {
                //ok count how many segs >= a
                //if a > 2*b, then count is 0
                //else we can assume a <= 2*b
                //and each length is < 2*b
                //odd -> yes, even -> no
                //yuck casework
                int cnt = 0;
                for (int i: segs) {
                    if (i >= a) cnt++;
                }
                cout << (cnt&1 ? "YES" : "NO") << '\n';
            }
            else if (numBig == 1) {
                int mxSize = 0;
                for (int i: segs) {
                    mxSize = max(mxSize,i);
                }
                int cnt = 0;
                for (int i: segs) {
                    if (i == mxSize) continue;
                    if (i >= a) cnt++;
                }    
                if (a > mxSize) {
                    //can't fit
                    cout << "NO\n";
                    return 0;
                }
                int s1 = 0, s2 = mxSize-a;
                bool canWin = false;
                for (; s2 >= 0; s1++, s2--) {
                    //cout << s1 << ' ' << s2 << '\n';
                    if ((b <= s1 && s1 < a) ||
                        (b <= s2 && s2 < a)) continue;
                    if (s1 >= 2*b || s2 >= 2*b) continue;
                    int c = cnt;
                    if (s1 >= a) c++;
                    if (s2 >= a) c++;
                    if (c % 2 == 0) {
                        canWin = true;
                        break;
                    }
                }
                cout << (canWin ? "YES" : "NO") << '\n';
            }
        }
    }
}

