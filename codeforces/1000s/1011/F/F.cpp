#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
int n;
vector<int> child[maxn];
bool val[maxn];
int type[maxn];

void dfs(int i) {
    if (child[i].size() == 0) return;
    dfs(child[i][0]);
    if (type[i] != 3) dfs(child[i][1]);
    int v1 = val[child[i][0]];
    int v2;
    if (type[i] != 3) v2 = val[child[i][1]];
    if (type[i] == 0) {
        val[i] = v1 & v2; 
    }
    else if (type[i] == 1) {
        val[i] = v1 | v2;
    }
    else if (type[i] == 2) {
        val[i] = v2 ^ v2;
    }
    else if (type[i] == 3) {
        val[i] = !v1;
    }
}

bool nochange[maxn];
void noChange(int i) {
    nochange[i] = true;
    for (int j: child[i]) {
        noChange(j);
    }
}

void dfs2(int i) {
    if (child[i].size() == 2 && type[i] < 2) {
        if (type[i] == 0) {
            //AND
            if (val[child[i][0]] == 0) {
                noChange(child[i][1]);
            }
            else {
                dfs2(child[i][1]);
            }
            if (val[child[i][1]] == 0) {
                noChange(child[i][0]);
            }
            else {
                dfs2(child[i][0]);
            }
        }
        else if (type[i] == 1) {
            //OR
            if (val[child[i][0]] == 1) {
                noChange(child[i][1]);
            }
            else {
                dfs2(child[i][1]);
            }
            if (val[child[i][1]] == 1) {
                noChange(child[i][0]);
            }
            else {
                dfs2(child[i][0]);
            }
        }
    }
    else {
        for (int j: child[i]) {
            dfs2(j);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        if (s == "AND") {
            int a, b; cin >> a >> b;
            child[i].push_back(a);
            child[i].push_back(b);
            type[i] = 0;
        }
        else if (s == "OR") {
            int a, b; cin >> a >> b;
            child[i].push_back(a);
            child[i].push_back(b);
            type[i] = 1;
        }
        else if (s == "XOR") {
            int a, b; cin >> a >> b;
            child[i].push_back(a);
            child[i].push_back(b);
            type[i] = 2;
        }
        else if (s == "NOT") {
            int a; cin >> a;
            child[i].push_back(a);
            type[i] = 3;
        }
        else {
            int a; cin >> a;
            val[i] = a;
        }
    }
    dfs(1);
    dfs2(1);
    //output
    for (int i = 1; i <= n; i++) {
        if (child[i].size() == 0) {
            if (nochange[i]) {
                cout << (val[1]);
            }
            else {
                cout << (!val[1]);
            }
        }
    }
    cout << '\n';

    return 0;
}
	

