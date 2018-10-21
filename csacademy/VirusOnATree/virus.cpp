#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
template<class T> inline void amin(T &x, const T &y) { if (y<x) x=y; }
template<class T> inline void amax(T &x, const T &y) { if (x<y) x=y; }

const int maxn = 100005;
int N, K;
int numNodes[maxn];
vector<pair<int,int>> vnodes;
set<int> adjs[maxn];
set<int> direc[maxn];
bool canBreak[maxn];
map<pair<int,int>,bool> ok;

void setDirec(int n, int prev) {
    if (n != 1) {
        canBreak[n] = ok[{prev,n}];
    }
	for (int i: adjs[n]) {
		if (i != prev) {
			direc[n].insert(i);
			setDirec(i,n);
		}
	}
}
int countNodes(int n, int prev) {
	numNodes[n] = 1;
	for (int i: direc[n]) {
		numNodes[n] += countNodes(i,n);
	}
	return numNodes[n];
}

void turnOff(int n) {
    for (int i: direc[n]) {
        canBreak[i] = false;
        turnOff(i);
    }
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	scanf("%d %d",&N,&K);
	for (int i = 1; i <= N; i++) {
	    int a, b, c;
	    scanf("%d %d %d",&a,&b,&c);
	    adjs[a].insert(b);
	    adjs[b].insert(a);
	    ok[{a,b}] = c;
	    ok[{b,a}] = c;
	}
	setDirec(1,-1);
	countNodes(1,-1);
	for (int i = 2; i <= N; i++) {
	    vnodes.push_back({numNodes[i],i});
	}
	sort(vnodes.begin(),vnodes.end());
	int numActive = N;
	int numEdges = 0;
	for (auto it = vnodes.rbegin(); it != vnodes.rend(); it++) {
	    if (numActive > K && canBreak[it->second]) {
	        numActive -= it->first;
	        turnOff(it->second);
	        numEdges++;
	    }
	}
	   
	//output
	
	printf("%d\n",(numActive > K) ? -1 : numEdges);
	return 0;
}