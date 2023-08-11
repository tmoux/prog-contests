#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

int n, A;
unordered_map<int,vector<int>> colors;
int freq[1000005];

int getCount(int c, int pos) {
    auto it = upper_bound(colors[c].begin(),colors[c].end(),pos);
    return distance(colors[c].begin(),it);
    //should be O(logn)
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> A;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        colors[c].push_back(i);
        freq[c]++;
    }
    vector<int> gColors;
    for (auto p: colors) {
        if (freq[p.first] >= freq[A] && p.first != A) gColors.push_back(p.first);
    }
    for (int c: gColors) {
        bool poss = true;
        for (int i = 0; i < colors[A].size(); i++) {
            int pos = colors[A][i];
            if (getCount(c,pos) < (i+1)) {
                poss = false;
                break;
            }
        }
        if (poss) {
            cout << c << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
	

