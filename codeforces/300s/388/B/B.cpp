#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int n = 2, k;
int len;
bool adj[maxn][maxn];

string ternary(int x) {
    string ret;
    while (x) {
        ret = (char)((x % 3) + '0') + ret;
        x /= 3;
    }
    len = ret.size() + 1;
    return ret;
}

void addEdge(int a, int b) {
    adj[a][b] = true;
    adj[b][a] = true;
    //cout << a << ": " << b << '\n';
}

void makeChain(int x, int r) { //make chain of length 2^x possibilities of length len
    if (r == 0) return;
    int l = r == 2 ? len-1 : len;
    vector<int> prev = {1};
    if (r == 2) {
        n++;
        addEdge(n,1);
        n++;
        addEdge(n,1);
        prev = {n,n-1};
    }
    for (int i = 0; i < x; i++) {
        vector<int> repl;
        for (int j = 0; j < 3; j++) {
            n++;
            for (int a: prev) {
                addEdge(n,a);
            }
            repl.push_back(n);
        }
        prev = repl;
    }
    /*
    if (x == len) {
        for (int a: prev) {
            addEdge(a,2);
        }
        return;
    }
    */
    for (int i = 0; i < l - x; i++) {
        n++;
        for (int a: prev) {
            addEdge(n,a);
        }
        prev = {n};
    }
    for (int a: prev) {
        addEdge(a,2);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k;
    if (k == 1) {
        cout << "2\nNY\nYN\n";
        return 0;
    }
    string ter = ternary(k);
    //cout << "len=" << len << '\n';
    //cout << ter << '\n';
    for (int s = ter.size()-1; s >= 0; s--) {
        int r = ter[ter.size()-1-s] - '0';
        makeChain(s,r);
        //cout << s << ' ' << r << '\n';
    }
    //output
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << (adj[i][j] ? 'Y' : 'N');
        }
        cout << '\n';
    }
    return 0;
}

