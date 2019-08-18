#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5+5;
const int M = 998244353;
int n;
string s;

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> s;
    int r = 0, g = 0, b = 0, rg = 0, rb = 0, gb = 0;
    ll ans = 1;
    for (int i = 0; i < 3*n; i++) {
        if (s[i] == 'R') {
            if (gb > 0) {
                ans = mult(ans,gb);
                gb--;
            }
            else if (g > 0) {
                ans = mult(ans,g);
                g--;
                rg++;
            }
            else if (b > 0) {
                ans = mult(ans,b);
                b--;
                rb++;
            }
            else {
                r++;
            }
        }
        else if (s[i] == 'G') {
            if (rb > 0) {
                ans = mult(ans,rb);
                rb--;
            }
            else if (r > 0) {
                ans = mult(ans,r);
                r--;
                rg++;
            }
            else if (b > 0) {
                ans = mult(ans,b);
                b--;
                gb++;
            }
            else {
                g++;
            }            
        }
        else if (s[i] == 'B') {
            if (rg > 0) {
                ans = mult(ans,rg);
                rg--;
            }
            else if (r > 0) {
                ans = mult(ans,r);
                r--;
                rb++;
            }
            else if (g > 0) {
                ans = mult(ans,g);
                g--;
                gb++;
            }
            else {
                b++;
            }
        }
    }
    for (int i = 2; i <= n; i++) ans = mult(ans,i);
    cout << ans << '\n';
}

