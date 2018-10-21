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
	int end;
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

void insert(Node* root, int value, int endi) {
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
	temp->end = endi;
	//cout << temp->val << ' ' << temp->end << '\n';
}

pair<int,int> findMax(Node* root, int prexor) {
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
	return make_pair(prexor^temp->val,temp->end);
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
	insert(root,prexor,0);
	//traverse thru nums and find maximum 
	
	for (int i = 1; i <= N; i++) {
		prexor = prexor ^ nums[i];
		//cout << prexor << '\n';
		insert(root,prexor,i);
		
		pair<int,int> cmax = findMax(root, prexor);
		//cout << cmax.first << ' ' << cmax.second << '\n';
		if (cmax.first > ans) {
			ans = cmax.first;
			if (cmax.second == i) {
				ansstart = cmax.second;
			}
			else {
				ansstart = cmax.second + 1;
			}
			
			ansend = i;
		}
		
	}
	

	cout << ans << ' ' << ansstart << ' ' << ansend << '\n';
	fout << ans << ' ' << ansstart << ' ' << ansend << '\n';
	

	
	endProgram(t1);
	return 0;
}