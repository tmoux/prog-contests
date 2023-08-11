#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1505;
int n, k;
string a[maxn];

char o(char a, char b) {
    if (a != 'S' && b != 'S') return 'S';
    if (a != 'E' && b != 'E') return 'E';
    if (a != 'T' && b != 'T') return 'T';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    set<string> ss;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ss.insert(a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            string s;
            for (int q = 0; q < k; q++) {
                if (a[i][q] == a[j][q]) s += a[i][q];
                else s += o(a[i][q],a[j][q]);
            }
            if (ss.count(s)) ans++;
        }
    }
    cout << ans/3 << '\n';
}

