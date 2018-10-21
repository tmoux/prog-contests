/*
ID: silxikys
PROG: cowxor
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

struct Node 
{	
	Node* arr[2];
	//only for leaf nodes
	int val;
};

Node* newNode()
{
	Node* ret = new Node;
	ret->arr[0] = ret->arr[1] = NULL;
	return ret;
}

//globals
int N;
const int triesize = 21;
const int maxn = 100005;
int nums[maxn];
int ans = -999999;
int ansstart, ansend;
map<int,int> valtoi;

void insert(Node* root, int value) {
	Node* temp = root;
	for (int i = triesize - 1; i >= 0; i--) {
		bool currbit = value & (1<<i);

		if (temp->arr[currbit] == NULL) {
			temp->arr[currbit] = newNode();
		}
		temp = temp->arr[currbit];
	}
	//now at the leaf node
	temp->val = value;
	//cout << temp->val << ' ' << temp->end << '\n';
}

int findMax(Node* root, int prexor) {
	Node* temp = root;
	for (int i = triesize - 1; i >= 0; i--) {
		bool currbit = prexor & (1<<i);

		if (temp->arr[1-currbit] != NULL) {
			temp = temp->arr[1-currbit];
		}
		else if (temp->arr[currbit] != NULL) {
			temp = temp->arr[currbit];
		}
	}
	return prexor^temp->val;
}

int main() {
	t1 = gettime();
	ofstream fout("cowxor.out");
	ifstream fin("cowxor.in");

	//input
	fin >> N;
	for (int i = 1; i <= N; i++) {
		fin >> nums[i];
	}

	//create empty Trie, insert 0
	Node* root = newNode();
	int prexor = 0;
	insert(root,prexor);
	valtoi[prexor] = 0;
	//traverse thru nums and find maximum 
	
	for (int i = 1; i <= N; i++) {
		prexor = prexor ^ nums[i];
		//cout << prexor << '\n';
		insert(root,prexor);
		valtoi[prexor] = i;
		
		int cmax = findMax(root, prexor);
		//cout << cmax.first << ' ' << cmax.second << '\n';
		if (cmax > ans) {
			ans = cmax;			
			ansend = i;
			int start = valtoi[cmax ^ prexor];
			if (start == i) {
				ansstart = start;
			}
			else {
				ansstart = start + 1;
			}
		}
		
	}
	

	cout << ans << ' ' << ansstart << ' ' << ansend << '\n';
	fout << ans << ' ' << ansstart << ' ' << ansend << '\n';
	

	
	endProgram(t1);
	return 0;
}