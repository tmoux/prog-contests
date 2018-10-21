#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+10;
int most[maxn];
char s[maxn];
int n;

int bit[maxn];
void add(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int range(int l, int r) {
    if (l-1 == 0) return sum(r);
    return sum(r) - sum(l-1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string st; cin >> st;
    for (int i = 0; i < n - 1; i++) {
        s[i+1] = st[i];
    }
    s[0] = 'R';
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') continue;
        for (int j = i + 1; j < n; j++) {
            if (s[j] == 'L') most[i]++;
            else break;
        }
    }
    int curr = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R') {
            curr += 1 + range(curr+1,n) + most[i];
        }
        else curr--;
        add(curr,1);
        cout << curr << '\n';
    }

    return 0;
}

