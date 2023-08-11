#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int alsz = 26;

string valya, tolya; int n;
vector<pair<char,char>> spells;
int parent[alsz];

int Find(int n) {return parent[n] < 0 ? n : (parent[n] = Find(parent[n]));}
void Union(int x, int y) 
{
	x = Find(x);
	y = Find(y);
	if (x == y) return;
	if (parent[x] > parent[y]) {
		swap(x,y);
	}
	parent[x] += parent[y];
	parent[y] = x;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	memset(parent,-1,sizeof(parent));
	cin >> n >> valya >> tolya;
	//use DSU, to keep track of which letters are in the same components
	for (int i = 0; i < n; i++) {
		int v = valya[i] - 'a', t = tolya[i] - 'a';
		if (Find(v) != Find(t)) {
			Union(v,t);
			spells.push_back(make_pair(valya[i],tolya[i]));
		}
	}
	//output
	cout << spells.size() << '\n';
	for (auto p: spells) {
		cout << p.first << ' ' << p.second << '\n';
	}	
	
	return 0;
}
