#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int p[maxn], s[maxn], vtoi[maxn], n;
vector<vector<int>> cycles;
bool seen[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        vtoi[s[i]] = i;
    }
  
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            seen[i] = true;
            vector<int> ret;
            ret.push_back(i);
            int idx = vtoi[p[i]];
            while (idx != i) {
                seen[idx] = true;
                ret.push_back(idx);
                idx = vtoi[p[idx]];
            }
            cycles.push_back(ret);
        }
    }
    //output
    for (vector<int> vec: cycles) {
        for (int i: vec) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    

    return 0;
}
	

