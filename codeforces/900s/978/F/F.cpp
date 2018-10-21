#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
vector<int> skills;
int n, k;
int R[maxn];
int lowerButQuarrel[maxn];


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> R[i];
        skills.push_back(R[i]);
    }
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        if (R[x] > R[y]) {
            lowerButQuarrel[x]++;
        }
        else if (R[y] > R[x]) {
            lowerButQuarrel[y]++;
        }
    }
    sort(skills.begin(),skills.end());
    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(skills.begin(),skills.end(),R[i]);
        int numLower = distance(skills.begin(),it);
        numLower -= lowerButQuarrel[i];

        cout << numLower << ' ';
    }


    return 0;
}
	

