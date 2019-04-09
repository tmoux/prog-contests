#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;

struct Node
{
    Node* child[26];
    Node() {
        for (int i = 0; i < 26; i++) child[i] = NULL;
    }
    void del() {
        for (int i = 0; i < 26; i++)
            if (child[i]) child[i]->del();
        delete this;
    }
};

bool can[26][2005];

void add(Node *root, string s) {
    Node *curr = root;
    for (int i = 0; i < s.size(); i++) {
        int nxt = s[i] - 'A';
        can[nxt][i] = 1;
        if (curr->child[nxt] == NULL)
            curr->child[nxt] = new Node();
        curr = curr->child[nxt];
    }
}

string words[2005];
vector<int> ans;
bool found = false;
int N, L;

void DFS(Node *curr, vector<int>& v) {
    //cout << (char)(v.back()+'A') << '\n';
    if (v.size() == L) return;
    if (found) return;
    for (int i = 0; i < 26; i++) {
        if (can[i][v.size()] && curr->child[i] == NULL) {
            //found one
            found = true;
            v.push_back(i);
            for (int j = v.size(); j < L; j++) {
                v.push_back(words[0][j]-'A');
            }
            ans = v;
            return;
        }
        
    }
    for (int i = 0; i < 26; i++) {
        if (curr->child[i]) {
            v.push_back(i);
            DFS(curr->child[i],v);
            v.pop_back();
        }
    }
}

void solve(int qq) {
    cin >> N >> L;
    memset(can,0,sizeof can);
    found = false;
    Node *root = new Node();
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        words[i] = s;
        add(root,s);
    }
    for (int i = 0; i < 26; i++) {
        if (root->child[i]) {
            vector<int> v = {i};
            DFS(root->child[i],v);
        }
    }
    cout << "Case #" << qq << ": ";
    if (!found) {
        cout << "-\n";
    }
    else {
        for (int i = 0; i < L; i++) {
            cout << (char)(ans[i]+'A');
        }
        cout << '\n';
    }
    root->del();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        solve(qq);
    }
}

