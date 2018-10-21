#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

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

void get(vector<int>& vec, vector<pair<int,int>>& mp, int curr, int i) {
    if (i == mp.size()) {
        vec.push_back(curr);
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
    map<int,int> mpa, mpb, mpc;
    factor(A,mpa);
    factor(B,mpb);
    factor(C,mpc);
    vector<pair<int,int>> ps[3];
    for (auto p: mpa) ps[0].push_back(p);
    for (auto p: mpb) ps[1].push_back(p);
    for (auto p: mpc) ps[2].push_back(p);
    vector<int> facs[3];
    get(facs[0],ps[0],1,0);
    get(facs[1],ps[1],1,0);
    get(facs[2],ps[2],1,0);

    for (int i = 0; i < 3; i++) {
        sort(facs[i].begin(),facs[i].end());
    }
    int ans = 0;
    int sec = 0, thir = 0;
    for (int i: facs[0]) {
        while (facs[1][sec] < i) {
            sec++;
        }
        thir = 0;
        for (int j = sec; j < facs[1].size(); j++) {
            while (facs[2][thir] < facs[1][j]) {
                thir++;
            }   
            ans += (facs[2].size() - thir);
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
	

