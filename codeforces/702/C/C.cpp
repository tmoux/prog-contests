#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
const int INF = 2000000000;
int n, m;
int cities[maxn];
vector<int> towers;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> cities[i];
    }
    for (int i = 0; i < m; i++) {
        int bi; cin >> bi;
        towers.push_back(bi);
    }
    int maxR = 0;
    for (int i = 0; i < n; i++) {
        auto ri = lower_bound(towers.begin(),towers.end(),cities[i]);
        int right = (ri == towers.end()) ? INF : abs(*ri-cities[i]);
        int left = INF;
        if (ri != towers.begin()) {
            left = abs(*(--ri)-cities[i]);
        }
        maxR = max(maxR,min(left,right));
    }
    cout << maxR << '\n';

    return 0;
}
	

