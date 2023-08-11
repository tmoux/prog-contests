#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
using namespace std;
typedef long long ll;
const int maxn = 300005;
const int maxsz = 30;
ll A[maxn];
int N;

struct Node
{
	Node* child[2];
	int num;
	ll leafVal;
};

Node* newNode() {
	Node* ret = new Node();
	for (int i = 0; i < 2; i++) {
		ret->child[i] = NULL;
	}
	ret->num = 0;
	ret->leafVal = 0;
	return ret;
}

void addToTrie(Node* root, ll n) {
	Node* curr = root;
	for (int i = maxsz-1; i >= 0; i--) {
		curr->num++;
		bool nxt = n & (1<<i);
		if (curr->child[nxt] == NULL) {
			curr->child[nxt] = newNode();
		}
		curr = curr->child[nxt];
	}
	//now curr is pointing to leaf node
	curr->num++;
	curr->leafVal = n;
	//cout << curr->leafVal << '\n';
}

ll findMatch(Node* root, ll ai) {
	Node* curr = root;
	for (int i = maxsz-1; i >= 0; i--,ans<<=1) {
		bool nxt = ai&(1<<i);
		if (curr->child[nxt] != NULL && curr->child[nxt]->num) {
			curr = curr->child[nxt];
		}
		else {
			curr = curr->child[!nxt];
		}
		curr->num--;
	}
	//now at leaf node
	return curr->leafVal;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	Node* root = newNode();
	for (int i = 0; i < N; i++) {
		ll pi; cin >> pi;
		addToTrie(root,pi);
	}
	//greedily find the lexicographically smallest string by
	//traversing the trie, matching whenever possible, then remove it
	for (int i = 0; i < N; i++) {
		ll ai = A[i];
		ll closestMatch = findMatch(root, ai);
		//output/formatting
		cout << (ai ^ closestMatch);
		if (i != N-1) cout << ' ';
	}
	cout << '\n';	
	return 0;
}