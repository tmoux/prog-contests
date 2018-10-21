#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
bool swi[maxn][maxn];
int n, m;
int numForLamp[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            swi[i][j] = (s[j] == '1');
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            numForLamp[j] += swi[i][j];
        }
    }
    
    bool ans = false;
    for (int i = 0; i < n; i++) {
        bool canWork = true;
        for (int j = 0; j < m; j++) {
            if (swi[i][j]) {
                canWork &= numForLamp[j] > 1;
            }
        }
        ans |= canWork;
    }
    
    //output
    cout << (ans ? "YES" : "NO") << '\n';



    return 0;
}
	

