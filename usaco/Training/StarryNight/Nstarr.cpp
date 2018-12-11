/*
ID: silxikys
PROG: starry
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
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;


int W, H;
const int maxdim = 100;
bool grid[maxdim][maxdim];
bool visited[maxdim][maxdim];

struct Cluster {
	bool arr[maxdim][maxdim];
	int height, width;

	Cluster rotate() {
		Cluster ret;
		ret.height = width;
		ret.width = height;
		for (int i = 0; i < ret.height; i++) {
			for (int j = 0; j < ret.width; j++) {
				ret.arr[i][j] = false;
			}
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (arr[i][j]) {
					ret.arr[j][height-i-1] = true;
				}
			}
		}
		return ret;
	}
	Cluster flip() {
		Cluster ret;
		ret.width = width;
		ret.height = height;
		for (int i = 0; i < ret.height; i++) {
			for (int j = 0; j < ret.width; j++) {
				ret.arr[i][j] = false;
			}
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (arr[i][j]) {
					ret.arr[height-i-1][j] = true;
				}
			}
		}
		return ret;
	}

	void print() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << arr[i][j];
			} cout << '\n';
		} cout << '\n';
	}
};

struct ClusterType {
	char name;
	int height, width;
	Cluster types[8];
	ClusterType(int c, int h, int w, int minheight, int minwidth, vector<pair<int,int>> stars) {
		name = static_cast<char>(c);
		height = h;
		width = w;
		Cluster ret;
		types[0] = ret;
		types[0].height = h;
		types[0].width = w;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				types[0].arr[i][j] = false;
			}
		}

		for (pair<int,int> p : stars) {
			types[0].arr[p.first-minheight][p.second-minwidth] = true;
		}
		for (int i = 1;  i < 4; i++) {
			types[i] = types[i-1].rotate();
		}
		types[4] = types[0].flip();
		for (int i = 5; i < 8; i++) {
			types[i] = types[i-1].rotate();
		}
	}

	bool clusterInType(Cluster c) {
		if (!(c.height == height && c.width == width || c.height == width && c.width == height)) {
			return false;
		}
		for (int k = 0; k < 8; k++) {
			bool correct = true;
			for (int i = 0;  i < c.height && correct; i++) {
				for (int j = 0; j < c.width; j++) {
					if (c.arr[i][j] != types[k].arr[i][j]) {
						correct = false;
						break;
					}
				}
			}
			if (correct) {
				return true;
			}
		}
		return false;
	}

	void print() {
		for (int i = 0; i < 8; i++) {
			types[i].print();
		}
	}
};

vector<ClusterType> clusters;
char output[maxdim][maxdim];
int currLetter = 97;

void floodfill(vector<pair<int,int>> &stars, int height, int width) {
	//cout << height << ' ' << width << '\n';
	stars.push_back(make_pair(height,width));
	visited[height][width] = true;
	for (int i = height - 1; i <= height + 1; i++) {
		for (int j = width - 1; j <= width + 1; j++) {
			if (i < H && j < W && i >= 0 && j >= 0) {
				if (grid[i][j] && !(visited[i][j])) {
					floodfill(stars,i,j);
				}
			}
		}
	}
}

int main() {
	t1 = gettime();
	ofstream fout("starry.out");
	ifstream fin("starry.in");

	//input
	fin >> W >> H;
	string s;
	getline(fin,s);
	for (int i = 0; i < H; i++) {
		getline(fin,s);
		for (int j = 0; j < W; j++) {
			if (s[j] == '1') {
				grid[i][j] = true;
			}
			else {
				grid[i][j] = false;
			}
			visited[i][j] = false;
			output[i][j] = '0';
			//cout << grid[i][j];
		} //cout << endl;
	}

	//traverse grid
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {

			if (grid[i][j] && !(visited[i][j])) {
				vector<pair<int,int>> stars;
				floodfill(stars,i,j);
				int minh = 999, minw = 999, maxh = 0, maxw = 0;
				for (pair<int,int> p : stars) {
					minh = min(minh,p.first);
					maxh = max(maxh,p.first);
					minw = min(minw,p.second);
					maxw = max(maxw,p.second);
				}
				ClusterType poss = ClusterType(currLetter,(maxh-minh+1),(maxw-minw+1),minh,minw,stars);
				Cluster pos1 = poss.types[0];
				bool newone = true;
				char pname = poss.name;
				for (ClusterType c: clusters) {
					if (c.clusterInType(pos1)) {
						newone = false;
						pname = c.name;
						break;
					}
				}
				if (newone) {
					currLetter++;
					clusters.push_back(poss);
				}

				for (pair<int,int> p: stars) {
					output[p.first][p.second] = pname;
				}
			}
			visited[i][j] = true;
		}
	}
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << output[i][j];
			fout << output[i][j];
		} cout << '\n'; fout << '\n';
	}

	endProgram(t1);
	return 0;
}