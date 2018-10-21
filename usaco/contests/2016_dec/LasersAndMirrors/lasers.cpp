/*
ID: silxikys
PROG: lasers
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

ofstream fout("lasers.out");
ifstream fin("lasers.in");

int N;
int source[2];
int sink[2];
map<int,vector<int>> xs;
map<int,vector<int>> ys;

struct Line {
	int val;
	bool isx;
	int dist;
};

int main() 
{
	//input
	fin >> N;
	int x, y;
	for (int i = 0; i < 2; i++) {
		fin >> x >> y;
		xs[x].push_back(y);
		ys[y].push_back(x);
		source[0] = x; source[1] = y;
	}
	for (int i = 0; i < 2; i++) {
		fin >> x >> y;
		xs[x].push_back(y);
		ys[y].push_back(x);
		sink[0] = x; sink[1] = y;
	}
	for (int i = 0; i < N; i++) {
		fin >> x >> y;
		xs[x].push_back(y);
		ys[y].push_back(x);
	}
	
	for (pair<int,vector<int>> p: ys) {
		sort(p.second.begin(),p.second.end());
		cout << p.first << ": ";
		for (int i: p.second) {
			cout << i << ' ';
		} cout << '\n';
	}
	/*
	for (pair<int,vector<int>> p: xs) {
		sort(p.second.begin(),p.second.end());
	}
	*/
	
	deque<Line> deq;
	//0 is x coordinate, 1 is y coordinate
	int ans = -1;
	deq.push_back({source[0],0,0});
	deq.push_back({source[1],1,0});
	while (deq.size() != 0) {
		Line l = deq.front();
		cout << l.val << ' ' << l.isx << ' ' << l.dist << '\n';
		if ((l.isx && l.val == sink[0] || !l.isx && l.val == sink[1])) {
			ans = l.dist;
			break;
		}
		map<int,vector<int>> usin = l.isx ? xs : ys;
		for (int dest: usin[l.val]) {
			Line nextLine = {dest, !l.isx, l.dist+1};
			deq.push_back(nextLine);
		}
		deq.pop_front();
	}

	cout << ans << '\n';
	fout << ans << '\n';

	return 0;
}