#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 40005;
int n, m, k, t;
vector<int> wastes[maxn];
int pre[maxn];
string ans[] = {"Grapes","Carrots","Kiwis"};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k >> t;
    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        wastes[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        pre[i] = wastes[i].size() + pre[i-1];
        sort(wastes[i].begin(),wastes[i].end());
    }
    while (t--) {
        int i, j; cin >> i >> j;
        int numwaste = pre[i-1];
        int dist;
        auto it = lower_bound(wastes[i].begin(),wastes[i].end(),j);
        if (it == wastes[i].end()) {
            dist = wastes[i].size();
        }
        else if (*it == j) {
            //is waste
            cout << "Waste\n";
            continue;
        }
        else dist = distance(wastes[i].begin(),it);
        numwaste += dist;
        int total = m*(i-1)+j - numwaste;
        //cout << i << ' ' << j << ' ' << total << ' ' << numwaste << '\n';
        cout << ans[total%3] << '\n';
    }


    return 0;
}
	

