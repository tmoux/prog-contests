#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;
int cnt[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    int numDistinct = 0;
    while (m--) {
    	int ai; cin >> ai;
    	if (cnt[ai] == 0) numDistinct++;
    	cnt[ai]++;
    	if (numDistinct == n) {
    		putchar('1');
    		numDistinct = 0;
    		for (int i = 1; i <= n; i++) {
    			cnt[i]--;
    			if (cnt[i] > 0) numDistinct++;
    		}
    	}
    	else putchar('0');
    }

    return 0;
}