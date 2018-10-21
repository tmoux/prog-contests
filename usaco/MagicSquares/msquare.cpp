/*
ID: silxikys
PROG: msquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
#include <deque>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

struct msquare{
	int sq[8];
	bool equals(msquare m) {
		for (int i = 0; i < 8; i++) {
			if (m.sq[i] != sq[i]) {
				return false;
			}
		}
		return true;
	}
	void print() {
		for (int i = 0; i < 4; i++) {
			cout << sq[i] << " ";
		}
		cout << endl;
		for (int i = 7; i >= 4; i--) {
			cout << sq[i] << " ";
		}
		cout << endl << endl;
	}
	string toString() {
		string ret = "";
		for (int i = 0; i < 8; i++) {
			ret += sq[i] + '0';
		}
		return ret;
	}
};

msquare A(msquare m) {
		msquare ret = {};
		for (int i = 0; i < 4; i++) {
			ret.sq[i] = m.sq[7-i];
			ret.sq[7-i] = m.sq[i];
		}
		return ret;
	}
msquare B(msquare m) {
	msquare ret = {};
	for (int i = 0; i < 4; i++) {
		ret.sq[i] = m.sq[(i-1+4) % 4];
		ret.sq[i+4] = m.sq[((i+1) % 4) + 4];
	}
	return ret;
}
msquare BB(msquare m) {
	return B(B(m));
}
msquare BBB(msquare m) {
	return B(B(B(m)));
}

msquare C(msquare m) {
	msquare ret = m;
	ret.sq[1] = m.sq[6];
	ret.sq[2] = m.sq[1];
	ret.sq[5] = m.sq[2];
	ret.sq[6] = m.sq[5];
	return ret;
}
msquare CC(msquare m) {
	return C(C(m));
}
msquare CCC(msquare m) {
	return C(C(C(m)));
}


int main() {
	t1 = gettime();
	ofstream fout("msquare.out");
	ifstream fin("msquare.in");

	//input
	msquare final;
	for (int i = 0; i < 8; i++) {
		fin >> final.sq[i];
	}
	msquare initial = {1,2,3,4,5,6,7,8};
	
	//breadth-first search
	map<string,string> arrangements; //"12345678" -> "ABCCCBBA"
	deque<pair<msquare,string>> queue;
	//load first ones into the queue
	//queue.push_back(make_pair(initial,""));
	queue.push_back(make_pair(A(initial),"A"));
	queue.push_back(make_pair(B(initial),"B"));
	queue.push_back(make_pair(BB(initial),"BB"));
	queue.push_back(make_pair(BBB(initial),"BBB"));
	queue.push_back(make_pair(C(initial),"C"));
	queue.push_back(make_pair(CC(initial),"CC"));
	queue.push_back(make_pair(CCC(initial),"CCC"));
	for (pair<msquare,string> p: queue) {
		arrangements[p.first.toString()] = p.second;
	}
	arrangements["12345678"] = "";

	//bfs
	msquare next;
	string nextString;
	while (queue.size() != 0) {
		pair<msquare,string> p = queue.front();
		//char last = p.second.back();
		//add all possible next msquares that are not already in arrangements
		next = A(p.first);
		nextString = p.second+"A";
		if (arrangements.find(next.toString()) == arrangements.end()) {
			arrangements[next.toString()] = nextString;
			queue.push_back(make_pair(next,nextString));
		}
		else if (arrangements[next.toString()].length() == nextString.length() &&  arrangements[next.toString()] > nextString) {
			arrangements[next.toString()] = nextString;
			queue.push_back(make_pair(next,nextString));
		}

		next = B(p.first);
		nextString = p.second+"B";
		if (arrangements.find(next.toString()) == arrangements.end()) {
			arrangements[next.toString()] = nextString;
			queue.push_back(make_pair(next,nextString));
		}
		else if (arrangements[next.toString()].length() == nextString.length() && arrangements[next.toString()] > nextString) {
			arrangements[next.toString()] = nextString;
			queue.push_back(make_pair(next,nextString));
		}

		next = C(p.first);
		nextString = p.second+"C";
		if (arrangements.find(next.toString()) == arrangements.end()) {
			arrangements[next.toString()] = nextString;
			queue.push_back(make_pair(next,nextString));
		}
		else if (arrangements[next.toString()].length() == nextString.length() && arrangements[next.toString()] > nextString) {
			arrangements[next.toString()] = nextString;
			queue.push_back(make_pair(next,nextString));
		}
		queue.pop_front();
	}
	
	//output
	/*
	for (pair<string,string> p : arrangements) {
		cout << p.first << " " << p.second << endl;

	}
	*/

	string ans = arrangements[final.toString()];
	cout << ans.length() << endl << ans << endl;
	fout << ans.length() << endl << ans << endl;
	

	
	endProgram(t1);
	return 0;
}