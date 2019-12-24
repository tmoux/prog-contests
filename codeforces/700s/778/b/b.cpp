#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
struct Node;
struct Node
{
    bool valid = false;
    bitset<1005> val;
    string op = "#";
    int a, b;
} nodes[maxn];

bool eval(int i) {
    if (nodes[i].valid) return false;
    assert(nodes[i].op != "#");
    if (!nodes[nodes[i].a].valid || !nodes[nodes[i].b].valid) return false;
    if (nodes[i].op == "AND") {
        nodes[i].val = nodes[nodes[i].a].val & nodes[nodes[i].b].val;
    }
    else if (nodes[i].op == "OR") {
        nodes[i].val = nodes[nodes[i].a].val | nodes[nodes[i].b].val;
    }
    else if (nodes[i].op == "XOR") {
        nodes[i].val = nodes[nodes[i].a].val ^ nodes[nodes[i].b].val;
    }
    nodes[i].valid = true;
    return true;
}

map<string,int> mp;
int pt = 1;
int n, m;

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m; 
    mp["?"] = 0;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int idx = mp[s] = pt++;
        cin >> s >> s;
        if (s[0] == '1' || s[0] == '0') {
            //number
            reverse(s.begin(),s.end());    
            nodes[idx].valid = true;
            for (int j = 0; j < s.size(); j++) {
                nodes[idx].val[j] = s[j]-'0';
            }
            cout << i << ": " << nodes[idx].val << '\n';
        }
        else {
            string aa, op, bb;
            aa = s;
            cin >> op >> bb;
            nodes[idx].a = mp[aa];
            nodes[idx].b = mp[bb];
            nodes[idx].op = op;
        }
    }
    vector<int> v;
    v.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (eval(i)) {

        }
    }
}
