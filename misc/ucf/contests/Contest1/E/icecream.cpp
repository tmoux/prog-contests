#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, q;
int maxforDepth[maxn];
set<int> children[maxn];
int capacity[maxn];

void getDepth(int i) {
    for (int j: children[i]) {
        getDepth(j);
    }
    for (int j: children[i]) {
        capacity[i] = max(capacity[i],capacity[j]);
    }
}

int p = 1;
map<int,int> preorder;
void getPreorder(int i) {
    preorder[p++] = capacity[i];
    for (int j: children[i]) {
        getPreorder(j);
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> capacity[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        int ai; cin >> ai;
        children[ai].insert(i+1);
    }

    getDepth(1);
    getPreorder(1);
    while (q--) {
        int i, K; cin >> i >> K;
        if (preorder[i] >= K) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}
	

