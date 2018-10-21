#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n;
const int maxn = 100005;
int deg[maxn];
vector<int> leaves;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int ai, bi; cin >> ai >> bi;
        deg[ai]++;
        deg[bi]++;
    }
    int numIntersect = 0;
    int lastFound = 1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] >= 3) {
            numIntersect++;
            lastFound = i;
        }
        else if (deg[i] == 1) {
            leaves.push_back(i);
        }
    }
    if (numIntersect > 1) {
        //not possible
        cout << "No\n";
        return 0;
    }
    else {

        int m = 0;
        vector<pair<int,int>> out;
        for (int i: leaves) {
            if (i != lastFound) {
                out.push_back({i,lastFound});
                m++;
            }
        }
        //output
        cout << "Yes\n";
        cout << m << '\n';
        for (auto p: out) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }


    return 0;
}
	

