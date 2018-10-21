#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;

const int alsz = 26;
int n, q;
struct Node
{
	Node* child[alsz];
	bool isLeaf;
	set<string> suggestions;
};

Node* newNode() {
	Node* node = new Node;
	for (int i = 0; i < alsz; i++) {
		node->child[i] = NULL;
	}
	node->isLeaf = false;
	return node;
}

void addString(Node* root, const string& s) {
	Node* curr = root;
	for (int i = 0; i < s.size(); i++) {
		int nxt = (tolower(s[i]))-'a';
		if (curr->child[nxt] == NULL) {
			curr->child[nxt] = newNode();
		}
		curr = curr->child[nxt];
		curr->suggestions.insert(s);
	}
	//now curr is pointing to leaf
	curr->isLeaf = true;
}

void printSuggestions(Node* root, const string& s) {
	Node* curr = root;
	bool unique = false;
	for (int i = 0; i < s.size(); i++) {
		int nxt = (tolower(s[i]))-'a';
		if (curr->child[nxt] == NULL) {
			curr->child[nxt] = newNode();
			unique = true;
		}
		curr = curr->child[nxt];
	}
	if (unique) {
		cout << "No suggestions\n";
		addString(root,s);
		return;
	}
	for (const string& s: curr->suggestions) {
		cout << s << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> n;
	Node* root = newNode();
	while (n--) {
		string s; cin >> s;
		addString(root,s);
	}
	cin >> q;
	while (q--) {
		string s; cin >> s;
		printSuggestions(root,s);
	}
	
	return 0;
}