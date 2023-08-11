#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
#include <unordered_set>
#include <cstring>
using namespace std;
typedef long long ll;

vector<int> facm[100005];

void factor(int i,map<int,int>& mp) {
    if (i == 1) return;
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            while (i % j == 0) {
                mp[j]++;
                i /= j;
            }
            factor(i,mp);
            return;
        }
    }
    //must be prime
    mp[i]++;
}

void get(vector<int>* vec, vector<pair<int,int>>& mp, int curr, int i) {
    if (i == mp.size()) {
        vec->push_back(curr);
        return;
    }
    int mult = 1;
    for (int j = 0; j <= mp[i].second; j++) {
        get(vec,mp,curr*mult,i+1);
        mult *= mp[i].first;
    }
}


void solve(int A, int B, int C) {
    //KLUDGE
    if (B > C) swap(B,C);
    if (A > B) swap(A,B);
    if (A > C) swap(A,C);
    vector<int> nums = {A,B,C};
    vector<int>* facs[3];
    for (int i = 0; i < 3; i++) {
        if (facm[nums[i]].size() != 0) {
            facs[i] = &facm[nums[i]];
        }
        else {
            map<int,int> mpaa;
            factor(nums[i],mpaa);
            vector<pair<int,int>> ps;
            for (auto p: mpaa) ps.push_back(p);
            get(&facm[nums[i]],ps,1,0);
            sort(facm[nums[i]].begin(),facm[nums[i]].end());
            facs[i] = &facm[nums[i]];
        }
    }
    //bottleneck
    unordered_set<int> has[3];
    for (int i = 0; i < 3; i++) {
        for (int j: *facs[i]) {
            has[i].insert(j);
        }
    }
    vector<int> ones(3,0), twos(3,0);
    int threes = 0;
    for (int i = 0; i < 3; i++) {
        for (int j: *facs[i]) {
            if (has[(i+1)%3].count(j) && has[(i+2)%3].count(j)) {
                threes++;
            }
            else if (has[(i+1)%3].count(j)) {
                twos[(2*i+1)%3]++;
            }
            else if (has[(i+2)%3].count(j)) {
                twos[(2*i+2)%3]++;
            }
            else {
                ones[i]++;
            }
        }
    }
    threes /= 3;
    for (int i = 0; i < 3; i++) {
        twos[i] /= 2;
    }
    int ans = threes;
    for (int i = 0; i < 3; i++) {
        ans += (ones[i] * facs[(i+1)%3]->size() * facs[(i+2)%3]->size());
    }
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            ans += twos[i] * facs[2]->size();
        }
        else if (i == 1) {
            ans += twos[i] * facs[0]->size();
        }
        else {
            ans += twos[i] * facs[1]->size();
        }
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int A, B, C;
        cin >> A >> B >> C;
        solve(A,B,C);
    }

    return 0;
}
	

