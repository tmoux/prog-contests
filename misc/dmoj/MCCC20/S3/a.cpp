#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node
{
    int mnIndex;
    Node* nxt[26];
    Node() {
        mnIndex = 1e9;
        for (int i = 0; i < 26; i++) {
            nxt[i] = NULL;
        }
    }
    int answer(const string& si, int i) {
        if (i == si.size()) return mnIndex;
        int nx = si[i]-'a';
        return nxt[nx] ? nxt[nx]->answer(si,i+1) : mnIndex;
    }
    Node* add(const string& si, int i, int pt) {
        if (i == si.size()) return this;
        int nx = si[i]-'a';
        if (!nxt[nx]) nxt[nx] = new Node();
        nxt[nx]->mnIndex = min(nxt[nx]->mnIndex,pt);
        return nxt[nx]->add(si,i+1,pt);
    }
};

string S;
int Q;

Node* nodes[100005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> S >> Q;
    Node *root = new Node();
    int pt = 1;
    nodes[pt] = root->add(S,0,pt);
    pt++;
    while (Q--) {
        char c; cin >> c;
        if (c == 'C') {
            //append
            int x; cin >> x;
            string c; cin >> c;
            nodes[pt] = nodes[x]->add(c,0,pt);
            pt++;
        }
        else if (c == 'Q') {
            string si; cin >> si;
            int ans = root->answer(si,0);
            cout << (ans == 1e9 ? -1 : ans) << '\n';
        }
    }
}

