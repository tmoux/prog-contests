#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int n, q;
struct Node
{
	Node* child[26];
	int weight;
	bool isLeaf;
};

Node* newNode() {
	Node* node = new Node;
	for (int i = 0; i < 26; i++) {
		node->child[i] = NULL;
	}
	node->weight = -1;
	node->isLeaf = false;
	return node;
}

void addString(Node* root, const string& s, int w) {
	Node* curr = root;
	for (int i = 0; i < s.size(); i++) {
		curr->weight = max(curr->weight,w);
		int nxt = s[i]-'a';
		if (curr->child[nxt] == NULL) {
			curr->child[nxt] = newNode();
		}
		curr = curr->child[nxt];
	}
	//now curr is pointing to leaf
	curr->weight = w;
}

int findBestMatch(Node* root, const string& s) {
	Node* curr = root;
	for (int i = 0; i < s.size(); i++) {
		int nxt = s[i]-'a';
		if (curr->child[nxt] == NULL) {
			return -1;
		}
		curr = curr->child[nxt];
	}
	return curr->weight;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> n >> q;
	Node* root = newNode();
	for (int i = 0; i < n; i++) {
		string s; int w; cin >> s >> w;
		addString(root,s,w);
	}
	for (int i = 0; i < q; i++) {
		string s; cin >> s;
		cout << findBestMatch(root,s) << '\n';
	}
	
	return 0;
}