#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <set>
#include <map>
#include <cstring>
using namespace std;

const int maxn = 5001;
map<char,vector<int>> indices;
map<char,int> countChar;
map<char,bool> isValid;
int charcounter[maxn];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	string s; cin >> s;
	int sz = s.size();
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];
		indices[c].push_back(i);
		countChar[c]++;
	}
	s += s;
	set<int> goodIndexes;
	for (auto p: indices) {
		for (int i = 1; i <= sz; i++) {
			map<char,int> charset;
			for (int j: p.second) {
				charset[s[j+i]]++;
			}
			for (int j: p.second) {
				if (charset[s[j+i]] == 1) {
					goodIndexes.insert(j);
				}
			}
		}
	}
	
	int denom = sz;
	int num = goodIndexes.size();
	double ans = (double)num/(double)denom;
	cout << fixed << setprecision(10) << ans << '\n';
	
	return 0;
}

