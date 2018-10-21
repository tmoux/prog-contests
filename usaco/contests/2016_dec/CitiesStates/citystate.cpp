/*
ID: silxikys
PROG: citystate
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int N;
map<string,vector<string>> states;

bool binarysearch(const vector<string>& v, string s, int l, int r) {
	if (r >= l) {
		int mid = (l + r)/2;
		if (v[mid] == s) {
			return true;
		}
		if (v[mid] > s) {
			return binarysearch(v,s,l,mid-1);
		}
		return binarysearch(v,s,mid+1,r);
	}
	return false;
}

int main() {
	ofstream fout("citystate.out");
	ifstream fin("citystate.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		string city, state;
		fin >> city >> state;
		city = city.substr(0,2);
		states[state].push_back(city);
	}
	//sorts the vectors
	vector<pair<string,vector<string>>> keys;
	for(map<string,vector<string>>::iterator iter = states.begin(); iter != states.end(); ++iter) {
		sort(iter->second.begin(),iter->second.end());
		keys.push_back(make_pair(iter->first,iter->second));
	}

	//for each city in each state vector,
	//finds if there is another city with flipped (state,city)
	int total = 0;
	for (int i = 0; i < keys.size(); i++) {
		pair<string,vector<string>> p = keys[i];
		for (string s: p.second) {
			if (s != p.first) {
				for (int j = i + 1; j < keys.size(); j++) {
					if (keys[j].first == s) {
						for (string te: keys[j].second) {
							if (te == p.first) {
								total++;
							}
						}
						break;
					}

				}
			}
		}
		
		/*
		for (string s: p.second) {
			if (states.count(s) > 0 && s != p.first){
				if (find(states[s].begin(),states[s].end(),p.first) != states[s].end()) {
					//cout << p.first << ' ' << s << '\n';
					total++;
				}
			}
		}
		*/
		/*
		cout << p.first << ": ";
		for (string s: p.second) {
			cout << s << ' ';
		} cout << '\n';
		*/
	}

	

	cout << total << '\n';
	fout << total << '\n';

	
	return 0;
}