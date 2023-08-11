#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n;
map<char,int> dx = {{'U',0},{'D',0},{'L',-1},{'R',1}};
map<char,int> dy = {{'U',1},{'D',-1},{'L',0},{'R',0}};
int prex[maxn], prey[maxn];
int tx, ty;

bool check(int x) {
    for (int i = 0; i+x <= n; i++) {
        int deltaX = abs(tx - prex[n] - (prex[i+x] - prex[i]));
        int deltaY = abs(ty - prey[n] - (prey[i+x] - prey[i]));
        if (deltaX + deltaY <= x && (deltaX + deltaY) % 2 == x % 2)                return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        prex[i] = prex[i-1] + dx[c];
        prey[i] = prey[i-1] + dy[c];
    }
    cin >> tx >> ty;
    int lo = 0, hi = n;
    //check boundary cases
    if (prex[n] == tx && prey[n] == ty) {
        cout << 0 << '\n';
        return 0;
    }
    if (!check(hi)) {
        cout << -1 << '\n';    
        return 0;
    }
    while (lo + 1 < hi) {
        (check((lo+hi)>>1) ? hi : lo) = (lo+hi)>>1;
    }
    cout << hi << '\n';

    return 0;
}
