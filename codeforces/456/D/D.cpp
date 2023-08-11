#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <assert.h>
using namespace std;
typedef long long ll;
const int alsz = 26;

enum Result
{
    Loss = 0, Win = 1, Choice = 2, Null = 3, None = 4
};

Result inverse(Result res) {
    switch (res) {
        case (Choice): return Null;
        case (Null): return Choice;
        default: return None; //should never happen
    }
}

Result operator+(Result a, Result b) {
    if (b == Choice || b == Null) {
        b = inverse(b);
    }
    switch (a) {
        case Loss:
            switch (b) {
                case Loss: return Loss;
                case Win: return Choice;
                case Choice: return Choice;
                case Null: return Loss;
            }
        case Win:
            switch (b) {
                case Loss: return Choice;
                case Win: return Win;
                case Choice: return Choice;
                case Null: return Win;
            }
        case Choice:
            return Choice; 
        case Null:
            return b;   
        case None:
            return b; 
    }
}

int ctoi(char c) {
    return c - 'a';
}

struct Node
{
    Node* childs[alsz];
    Result res;
    Node() {
        for (int i = 0; i < alsz; i++) childs[i] = NULL;
        res = None;
    }
};

void addString(Node* curr, string s) {
    for (int i = 0; i < s.size(); i++) {
        if (!curr->childs[ctoi(s[i])]) {
           curr->childs[ctoi(s[i])] = new Node();
        }
        curr = curr->childs[ctoi(s[i])];
    }
    curr->res = (s.size() % 2 == 0 ? Loss : Win);
}

void dfs(Node* curr) {
    for (int i = 0; i < alsz; i++) {
        if (curr->childs[i]) {
            dfs(curr->childs[i]);
        }
    }
    for (int i = 0; i < alsz; i++) {
        if (curr->childs[i]) {
            curr->res = (curr->res + curr->childs[i]->res);
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    Node* root = new Node();
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        addString(root,s);
    }
    dfs(root);
    //output
    if (root->res == Choice) {
        cout << "First\n";
        return 0;
    }
    if (root->res == Null) {
        cout << "Second\n";
        return 0;
    }
    else {
        cout << ((k & 1) & root->res ? "First" : "Second") << '\n';
        //uses fact that k must be odd and res must be 1 (win) to be "First"
    }
    return 0;
}
	

