#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

map<string,int> mmap;
string s;
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cin >> s;
    for (int i = 0; i < s.size() - 1; i++) {
        string sub = s.substr(i,2);
        mmap[sub]++;
    }

    int maxTimes = 0;
    string ss;
    for (pair<string,int> p: mmap) {
        if (p.second > maxTimes) {
            maxTimes = p.second;
            ss = p.first;
        }
    }
    cout << ss << '\n';


    return 0;
}
	

