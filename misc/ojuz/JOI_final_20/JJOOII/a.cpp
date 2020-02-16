#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, maxk = 18;
int n, K;
string s;

int jJ[maxk][maxn], jO[maxk][maxn], jI[maxk][maxn];

int walk(int i, int ar[][maxn]) {
    for (int k = maxk-1; k >= 0; k--) {
        if (K & (1<<k)) {
            i = ar[k][i];
        }
        if (i == -1) return -1;
    }
    return i;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> K >> s;
    memset(jJ,-1,sizeof jJ);
    memset(jO,-1,sizeof jO);
    memset(jI,-1,sizeof jI);
    for (int i = n-1; i >= 0; i--) {
        jJ[0][i] = s[i] == 'J' ? i+1 : jJ[0][i+1];
        for (int k = 1; k < maxk; k++) {
            jJ[k][i] = jJ[k-1][i] == -1 ? -1 : jJ[k-1][jJ[k-1][i]];
        }
    }
    for (int i = n-1; i >= 0; i--) {
        jO[0][i] = s[i] == 'O' ? i+1 : jO[0][i+1];
        for (int k = 1; k < maxk; k++) {
            jO[k][i] = jO[k-1][i] == -1 ? -1 : jO[k-1][jO[k-1][i]];
        }
    }
    for (int i = n-1; i >= 0; i--) {
        jI[0][i] = s[i] == 'I' ? i+1 : jI[0][i+1];
        for (int k = 1; k < maxk; k++) {
            jI[k][i] = jI[k-1][i] == -1 ? -1 : jI[k-1][jI[k-1][i]];
        }
    }

    int ans = 2e9;
    for (int i = 0; i < n; i++) {
        int r = i;
        r = walk(r,jJ);
        if (r == -1) continue;
        r = walk(r,jO);
        if (r == -1) continue;
        r = walk(r,jI);
        if (r == -1) continue;
        int tr = (r-i)-3*K;
        ans = min(ans,tr);
    }
    cout << (ans < 2e9 ? ans : -1) << '\n';
}
