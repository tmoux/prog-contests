#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

char other(char a, char b) {
    if (a != 'A' && b != 'A') return 'A';
    if (a != 'B' && b != 'B') return 'B';
    return 'C';
}

int N;

int solve(string a, string b, string c) {
    int ans = 20000;
    for (int i = 0; i < N; i++) {
        string tar;
        bool poss = true;
        for (int j = 0; j < N; j++) {
            if (a[j] == b[(i+j)%N]) {
                poss = false;
                break;
            }
            else tar += other(a[j],b[(i+j)%N]);
        }
        if (!poss) continue;
        auto z = z_function(tar+'#'+c+c);
        for (int j = 0; j < N; j++) {
            if (z[j+N+1] == N) {
                ans = min(ans,min(i,N-i)+min(j,N-j));
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a, b, c; cin >> a >> b >> c;
    N = a.size();
    int ans = 20000;
    ans = min(ans,solve(a,b,c));
    ans = min(ans,solve(b,c,a));
    ans = min(ans,solve(c,a,b));
    if (ans < 20000) {
        cout << ans << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

