/*
ID: silxikys
PROG: pairup
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <deque>
using namespace std;

ofstream fout("pairup.out");
ifstream fin("10.in");

deque<pair<int,int>> deq;

int main() 
{
	int N; fin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		fin >> a >> b;
		deq.push_back(make_pair(b,a));
	}
	sort(deq.begin(),deq.end());
	int ans = 0;
	
	while (deq.size() > 1) {
		pair<int,int> p1 = deq.front();
		pair<int,int> p2 = deq.back();
		ans = max(ans,p1.first+p2.first);
		if (p1.second < p2.second) {
			deq.pop_front();
			deq[deq.size()-1].second -= p1.second;
		}
		else if (p1.second > p2.second) {
			deq.pop_back();
			deq[0].second -= p2.second;
		}
		else if (p1.second == p2.second) {
			deq.pop_back();
			deq.pop_front();
		}
	}
	if (deq.size() == 1) {
		ans = max(ans, deq[0].first*2);
	}
	cout << ans << '\n';
	fout << ans << '\n';



	return 0;
}