/*
ID: silxikys
PROG: stampede
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <deque>
using namespace std;

ofstream fout("stampede.out");
ifstream fin("stampede.in");

struct Event
{
	int time;
	int y;

	bool operator<(const Event& rhs) const {
		return time < rhs.time;
	}
};
const int maxn = 50001;
int N;


int main() 
{
	fin >> N;
	vector<Event> events;
	set<int> actives;
	set<int> cowsSeen;

	for (int i = 0; i < N; i++) {
		int x, y, r;
		fin >> x >> y >> r;
		x *= -r;
		events.push_back({x - r,y});
		events.push_back({x,-1*y});
	}
	sort(events.begin(),events.end());
	for (int i = 0; i < events.size();) {
		int j;
		for (j = i; j < events.size() && events[i].time == events[j].time; j++) {
			Event e = events[j];
			if (e.y > 0) {
				actives.insert(e.y);
			}
			else if (e.y < 0) {
				actives.erase(-1*e.y);
			}
		}

		if (!actives.empty()) {
				cowsSeen.insert(*actives.begin());
		}
		i = j;
	}

	cout << cowsSeen.size() << '\n';
	fout << cowsSeen.size() << '\n';


	return 0;
}