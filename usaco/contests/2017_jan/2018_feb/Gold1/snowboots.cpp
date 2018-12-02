/*
ID: silxikys
PROG: snowboots
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

ofstream fout("snowboots.out");
ifstream fin("snowboots.in");

struct Boot
{
	int maxDepth;
	int maxStep;

	bool operator<(const Boot& rhs) const {
		if (maxDepth != rhs.maxDepth) {
			return maxDepth < rhs.maxDepth;
		}
		return maxStep < rhs.maxStep;
	}
};
map<Boot,int> mapping;

const int maxn = 100005;
int N, B;
int depth[maxn];
Boot boots[maxn];
//dsu with rank compression/union-by-rank
int parent[maxn];
bool canMake[maxn];
int Find(int n) {
	return (parent[n] < 0) ? n : parent[n] = Find(n);
}
void Union(int x, int y) 
{
	//sets parent of X to be parent of Y
	int xParent = Find(x);
	int yParent = Find(y);
	if (xParent == yParent) return;
	parent[yParent] += parent[xParent];
	parent[x] = y;
}

int main() 
{
	memset(parent,-1,sizeof(parent));
	//input and sorting
	fin >> N >> B;
	int endNode = N-1;
	for (int i = 0; i < N; i++) {
		fin >> depth[i];
	}
	
	for (int i = 0; i < B; i++) {
		int si, di;
		fin >> si >> di;
		boots[i] = {si,di};
		mapping[boots[i]] = i;
	}
	sort(boots,boots+B);
	/*
	for (int i = 0; i < B; i++) {
		cout << boots[i].maxDepth << ' ' << boots[i].maxStep << ' ' << '\n';
	}
	cout << '\n';
	*/
	//iterate over boots in sorted order
	//add paths whenever possible
	for (int i = 0; i < B; i++) {
		int curr = 0;
		if (Find(curr) <= boots[i].maxStep) {
			curr = Find(curr);
		}
		while (curr != endNode) {
			int orig = curr;			
			for (int j = min(endNode,curr+boots[i].maxStep); j > curr; j--) {
				if (depth[j] <= boots[i].maxDepth) {
					//Union(curr,j);
					curr = Find(j);
					break;
				}
			}

			if (orig == curr) {
				break;
			}
			//cout << i << ' ' << curr << '\n';
		}

		if (curr == endNode) {
			canMake[mapping[boots[i]]] = true;

		}
		//cout << boots[i].maxDepth << ' ' << boots[i].maxStep << ' ' << mapping[boots[i]] << '\n';
		//cout << canMake[mapping[boots[i]]] << '\n';
	}

	for (int i = 0; i < N; i++) {
		cout << i << ' ' << parent[i] << '\n';
	}
	cout << '\n';

	//output
	for (int i = 0; i < B; i++) {
		cout << canMake[i] << '\n';
	}

	return 0;
}