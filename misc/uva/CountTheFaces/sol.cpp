#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

int iscon[130][130];
bool seen[130];

struct Component
{
    int V = 0, E = 0;
    int F() {
        return 2 - V + E;
    }
    bool degen() {
        return V == 0 && E == 0;
    }
};

void dfs(int i, Component& c) {
    if (!seen[i]) {
        seen[i] = true;
        c.V++;
    }
    for (int j = 0; j < 130; j++) {
        if (iscon[i][j]) {
            c.E += iscon[i][j];
            iscon[i][j] = 0;
            iscon[j][i] = 0;
            dfs(j,c);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int v, e;
    while (cin >> v >> e) {
        memset(iscon,0,sizeof(iscon));
        memset(seen,0,sizeof(seen));
        for (int i = 0; i < e; i++) {
            char a, b; cin >> a >> b;
            iscon[a][b]++;
            iscon[b][a]++;
        }
        int ans = 0;
        for (int i = 0; i < 130; i++) {
            Component c;
            dfs(i,c);
            if (!c.degen()) {
                ans += c.F() - 1;
            }
            //cout << (char)i << ": " << c.V << ' ' << c.E << ' ' << c.F() << '\n';
        }
        cout << ++ans << '\n';
    }
    return 0;
}
	

