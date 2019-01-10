#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, M, Q;
vector<int> ancestors[maxn];
int SZ;
vector<pair<int,int>> bests[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> Q;
    for (int i = 0; i < M; i++) {
    	int s, e; cin >> s >> e;
    	ancestors[e].push_back(s);
    }
    SZ = 500;




    return 0;
}