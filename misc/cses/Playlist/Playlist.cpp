#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int maxn = 200005;
int songs[maxn];
int N;
int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	scanf("%d\n",&N);
	for (int i = 0; i < N; i++) {
		scanf("%d",songs+i);
	}
	int maxl = -1;
	set<int> s;
	int rp = 0;
	for (int i = 0; i < N; i++) {
		if (i > 0) {
			s.erase(songs[i-1]);
		}
		while (rp < N && !(s.count(songs[rp]))) {
			//if *rptr is not in the set
			s.insert(songs[rp]);
			rp++;
		}
		/*
		for (int i: s) {
			cout << i << ' ';
		}
		cout << '\n';
		*/
		maxl = max(maxl,(int)s.size());
	}
	printf("%d\n",maxl);
	return 0;
}

