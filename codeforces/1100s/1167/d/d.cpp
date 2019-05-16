#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//close whenever possible
const int maxn = 2e5+5;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    int c1 = 0, c2 = 0;
    for (char c: s) {
        if (c == '(') {
            //add to smaller one
            if (c1 < c2) {
                c1++;
                cout << 0;
            }
            else {
                c2++;
                cout << 1;
            }
        }
        else {
            if (c1 > c2) {
                c1--;
                assert(c1 >= 0);
                cout << 0;
            }
            else {
                c2--;
                assert(c2 >= 0);
                cout << 1;
            }
        }
    }
    cout << '\n';
}

