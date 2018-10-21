#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n, m;
bool grid[maxn][maxn];
int clen[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] == '1';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            if (!grid[i][j]) clen[i][j] = 0;
            else clen[i][j] = clen[i][j+1] + grid[i][j];
        }
    }

    int maxans = 0;
    for (int j = 0; j < m; j++) {
        vector<int> len(n);
        for (int i = 0; i < n; i++) {
            len[i] = clen[i][j];
        }
        sort(len.begin(),len.end(),greater<int>());
        for (int h = 1; h <= n; h++) {
            maxans = max(maxans,h*len[h-1]);    
        }
    }
    cout << maxans << '\n';

    return 0;
}
	

