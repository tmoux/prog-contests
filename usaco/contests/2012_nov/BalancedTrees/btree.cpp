#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e4+4;
int N;
vector<int> adj[maxn];
bool blocked[maxn]; 
int treeSize[maxn], label[maxn];

void amax(int& a, int b) {
    a = max(a,b);
}
void amin(int& a, int b) {
    a = min(a,b);
}

int sizeDFS(int i, int par) {
    treeSize[i] = 1;
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            treeSize[i] += sizeDFS(j,i);
        }
    }
    return treeSize[i];
}

int getCentroid(int i, int par, int compSize) {
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            if (treeSize[j] * 2 > compSize) {
                return getCentroid(j,i,compSize);
            }
        }
    }
    return i;
}

struct State { int mini, maxi, curr, excess, maxExcess; };
pair<State,State> states[maxn];
void subtreeDFS1(int i, int par, map<int,int>& adding) {
    State& pr = states[par].first;
    State& mine = states[i].first;
    states[i].first = {min(pr.mini,pr.curr-label[i]),max(pr.maxi,pr.curr-label[i]),pr.curr-label[i],0,0};
    if (mine.curr <= mine.mini) {
        amax(adding[mine.curr],-mine.curr);
    }
   
    //recurse
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            subtreeDFS1(j,i,adding);
        }
    }
}

void subtreeDFS2(int i, int par, map<int,int>& adding) {
    State& pr = states[par].second;
    State& mine = states[i].second;
    states[i].second = {min(pr.mini,pr.curr+label[i]),max(pr.maxi,pr.curr+label[i]),pr.curr+label[i],0,0};
    mine.excess = pr.excess + label[i];
    amax(mine.excess,0);
    mine.maxExcess = max(pr.maxExcess,mine.excess);
    if (mine.curr <= mine.mini) {
        amax(adding[mine.curr],mine.maxExcess);
    }
    //recurse
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            subtreeDFS2(j,i,adding);
        }
    }
}

int solveTree(int centroid) {
    pair<map<int,int>,map<int,int>> orig;
    if (label[centroid] == 1) {
        orig.first[-1] = 1;
    }
    states[centroid] = {{min(0,-label[centroid]),max(0,-label[centroid]),-label[centroid],0,0},{0,0,0,0,0}};
    int ans = 0;
    for (int j: adj[centroid]) {
        if (!blocked[j]) {
            pair<map<int,int>,map<int,int>> adding;
            //maps offset to max excess
            subtreeDFS1(j,centroid,adding.first);
            subtreeDFS2(j,centroid,adding.second);
            
            /*
            cout << j << '\n';
            for (auto p: adding.first) {
                cout << p.first << ' ' << p.second << '\n';
            }
            cout << '\n';
            for (auto p: adding.second) {
                cout << p.first << ' ' << p.second << '\n';
            }
            cout << '\n';
            */
            for (auto& p: adding.first) {
                if (p.first != 0 && orig.second.count(p.first)) {
                    amax(ans,p.second + orig.second[p.first]);
                }
            }
            for (auto& p: adding.second) {
                if (p.first != 0 && orig.first.count(p.first)) {
                    amax(ans,p.second + orig.first[p.first]);
                }
            }
            //merge
            for (auto& p: adding.first) {
                amax(orig.first[p.first],p.second);
            }
            for (auto& p: adding.second) {
                amax(orig.second[p.first],p.second);
            }
        }
    }
    return ans;
}

int decomp(int i) {
    int compSize = sizeDFS(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    int ans = solveTree(centroid);
    for (int j: adj[centroid]) {
        if (!blocked[j]) {
            ans = max(ans,decomp(j));
        }
    }
    return ans;
}

int main()
{
    //freopen("btree.in","r",stdin);
    //freopen("btree.out","w",stdout);
    cin >> N;
    for (int i = 2; i <= N; i++) {
        int ai; cin >> ai;
        adj[i].push_back(ai);
        adj[ai].push_back(i);
    }
    for (int i = 1; i <= N; i++) {
        char c; cin >> c;
        label[i] = c == '(' ? 1 : -1;
    }
    //get answer
    int ans = decomp(1);
    cout << ans << '\n';
    return 0;
}
