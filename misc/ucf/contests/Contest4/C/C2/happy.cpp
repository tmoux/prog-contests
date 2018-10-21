#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <bitset>
using namespace std;
typedef long long ll;
typedef bitset<40> bits;

bits getMask(const string& s) {
    bits res;
    int cnt = 0;
    for (int i = s.size() - 2; i >= 0; i--) {
        if (s[i] > s[i+1]) {
            res[cnt] = 1;
        }
        cnt++;
    }
    return res;
}

bits get(const string& s) {
    bits res;
    int cnt = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '1') {
            res[cnt] = 1;
        }
        cnt++;
    }
    return res;
}

struct Node
{
    int cnt;
    Node* child[2];
    Node() {
        cnt = 0;
        child[0] = NULL;
        child[1] = NULL;
    }
    void insert(const bits& s, int idx) {
        if (idx == s.size()) {
            cnt++;
            return;
        }
        bool nxt = s[idx];
        if (child[nxt] == NULL) {
            child[nxt] = new Node();
        }
        child[nxt]->insert(s,idx+1);
    }

    void remove(const bits& s, int idx) {
        if (idx == s.size()) {
            cnt = 0;
            return;
        }
        bool nxt = s[idx];
        if (child[nxt] == NULL) return;
        child[nxt]->remove(s,idx+1);
    }

    int query(const bits& s, int idx) {
        if (idx == s.size()) {
            return cnt;
        }
        bool nxt = s[idx];
        if (child[nxt] == NULL) return 0;
        return child[nxt]->query(s,idx+1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    Node* root = new Node();
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            string s; cin >> s;
            bits a = getMask(s);
            root->insert(a,0);
        }
        else if (t == 2) {
            string s; cin >> s;
            bits a = get(s);
            root->remove(a,0);
        }
        else if (t == 3) {
            string s; cin >> s;
            bits a = get(s);
            cout << root->query(a,0) << '\n';
        }
    }

    return 0;
}
	

