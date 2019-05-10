#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node
{
    map<char,Node*> child;
    Node() {}
};

void add(Node *curr, const string& s) {
    for (char c: s) {
        if (!curr->child.count(c)) curr->child[c] = new Node();
        curr = curr->child[c];
    }
}

string cur = "";
string ans = "";
bool done = false;

map<char,char> beats = {{'R','P'},{'P','S'},{'S','R'}};

char better(char a, char b) {
    return a < b ? a : b;
}

void DFS(Node *curr) {
    if (done) return;
    int sz = curr->child.size();
    if (sz == 3) {
        return;
    }
    else if (sz == 2) {
        char p = curr->child.begin()->first;
        char q = next(curr->child.begin())->first;
        char choose = better(p,q);
        cur += choose;
        DFS(curr->child[choose]);
        cur.pop_back();
    }
    else if (sz == 1) {
        char c = curr->child.begin()->first;
        cur += beats[c];
        ans = cur;
        done = true;
    }
    else {
        ans = cur;    
        done = true;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int qq = 1; qq <= T; qq++) {
        cout << "Case #" << qq << ": ";
        int A; cin >> A;
        Node *root = new Node();
        while (A--) {
            string s; cin >> s;
            while (s.size() < 500) s += s;
            add(root,s);
        }
        done = false;
        cur = "";
        ans = "";
        DFS(root);
        if (ans == "") {
            cout << "IMPOSSIBLE\n";
        }
        else {
            cout << ans << '\n';
        }
    }

}

