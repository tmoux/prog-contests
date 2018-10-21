#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

int n, m;
const int maxn = 300005;
const int maxm = 105;
int A[maxn];
int to[maxm][maxn]; //index of ith cow of breed k
int pre[maxm][maxn]; //number of cows of breed k up to i
vector<pair<int,int>> ans;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        pre[A[i]][i]
        for (int j = 1; j < maxm; j++) {
            pre[j][i]         
        }
    }
    //try every possible k
    

    //output
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
	

