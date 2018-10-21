#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

bool is[101];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> idx;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (!is[ai]) {
            is[ai] = true;
            idx.push_back(i+1);
        }
    }
    if (idx.size() >= k) {
        cout << "YES\n";
        for (int i = 0; i < k; i++) {
            cout << idx[i] << ' ';
        }
    }
    else {
        cout << "NO\n";
    }


    return 0;
}
	

