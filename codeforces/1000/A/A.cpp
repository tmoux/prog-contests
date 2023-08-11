#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

vector<string> shirts[4];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        shirts[s.size()-1].push_back(s);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int sz = s.size()-1;
        auto it = find(shirts[sz].begin(),shirts[sz].end(),s);
        if (it == shirts[sz].end()) {
            ans++;
        }
        else {
            shirts[sz].erase(it);
        }
    }
    cout << ans << '\n';


    return 0;
}
	

