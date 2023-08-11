#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, q, pre[maxn], skip[maxn], back[maxn];
vector<int> child[maxn];

int p = 0;

void dfs(int i) {
    back[p] = i;
    pre[i] = p++;
    for (int j: child[i]) {
        dfs(j);
    }
    skip[i] = p - 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%d %d\n",&n,&q);
    for (int i = 2; i <= n; i++) {
        int pi;
        scanf("%d",&pi);
        child[pi].push_back(i);
    }
    dfs(1);
    while (q--) {
        int ui, ki; scanf("%d %d",&ui,&ki);
        printf("%d\n",(pre[ui]+ki-1>skip[ui]?-1:back[pre[ui]+ki-1]));
        /*
        if (pre[ui] + ki - 1 > skip[ui]) {
            cout << -1 << '\n';
        }
        else {
            cout << back[pre[ui]+ki-1] << '\n';
        }
        */
    }

    return 0;
}
	

