#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;

//so there's only 2^9 = 512 diff. pizzas and preferences
//Let's iterate over all pairs of bitmasks, and for each pair,
//we can calculate how many people we will get by using
//by iterating over the people and seeing if their mask ANDed with (i|j) is equal to their mask.
//O(512^3) ~= 100 million.

int people[1<<9]; //# of people with mask of preference
int mb[maxn]; //mask of pizza i
int u[1<<9]; //u function as described above
vector<pair<int,int>> cost[1<<9]; //min cost of this mask

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int fi; cin >> fi;
        int mask = 0;
        while (fi--) {
            int b; cin >> b;
            mask |= 1<<(b-1);
        }
        people[mask]++;
        //cout << "added " << mask << '\n';
    }

    for (int i = 0; i < m; i++) {
        int c; cin >> c;
        int fi; cin >> fi;
        while (fi--) {
            int b; cin >> b;
            mb[i] |= 1<<(b-1);
        }      
        cost[mb[i]].push_back({c,i});
    }
    for (int i = 0; i < (1<<9); i++) {
        sort(cost[i].begin(),cost[i].end());
    }

    pair<int,int> ans = {-1,-1};
    int maxFriends = -1;
    int minCost = -1;
    for (int i = 0; i < (1<<9); i++) {
        for (int j = 0; j < (1<<9); j++) {
            if (cost[i].empty() || cost[j].empty()) continue;
            if (i == j && cost[i].size() < 2) continue;
            int ci, cj;
            int idxI, idxJ;
            if (i == j) {
                ci = cost[i][0].first;
                idxI = cost[i][0].second;
                cj = cost[j][1].first;
                idxJ = cost[j][1].second;
            }
            else {
                ci = cost[i][0].first;
                idxI = cost[i][0].second;
                cj = cost[j][0].first;
                idxJ = cost[j][0].second;
            }
            int numFriends = 0;
            for (int k = 0; k < (1<<9); k++) {
                if (people[k] == 0) continue;
                if ((k&(i|j)) == k) {
                    numFriends += people[k];
                }
            }
            if (numFriends > maxFriends) {
                ans = {idxI,idxJ};
                maxFriends = numFriends;
                minCost = ci + cj;
            }
            else if (numFriends == maxFriends && ci + cj < minCost) {
                minCost = ci + cj;
                ans = {idxI,idxJ};
            }
        }
    }
    cout << (ans.first+1) << ' ' << (ans.second+1) << '\n';
}

