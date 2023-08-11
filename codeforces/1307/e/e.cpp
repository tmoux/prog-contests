#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005, M = 1e9+7;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int n, m;
//iterate over rightmost left cow i
//maintain for each cow if it can be in left, right, none, or both
//calculate max ans
//combo for this ans: if type can be in just one, multiply by # of spaces (count possible cows)
//if type can be in both, count ways you can do that 
//if n >= m, count (n-m)*m+m*(m-1) 
int type[maxn];
vector<int> cows[maxn];
set<int> has[maxn];

int leftVal[maxn], rightVal[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> type[i];
    }
    for (int i = 0; i < m; i++) {
        int fi, hi; cin >> fi >> hi;
        cows[fi].push_back(hi);
        has[fi].insert(hi);
    }
    for (int i = 1; i <= n; i++) {
        sort(cows[i].begin(),cows[i].end());
    }
    vector<int> cnt(n+1,0);
    for (int i = 1; i <= n; i++) {
        leftVal[i] = ++cnt[type[i]];
    }
    cnt = vector<int>(n+1,0);
    vector<int> left(n+1,0);
    for (int i = n; i >= 1; i--) {
        rightVal[i] = ++cnt[type[i]];
    }

    vector<int> ptLeft(n+1,0);
    vector<int> ptRight(n+1,0);
    for (int i = 1; i <= n; i++) {
        int t = type[i];
        while (ptRight[t] < cows[t].size() && 
               cows[t][ptRight[t]] <= rightVal[i]) {
            ++ptRight[t];
        }
    }
    pair<int,int> ans = {-1,0}; //maxans, ways
    for (int i = 0; i <= n; i++) {
        int cand = 0;
        int ways = 1;
        //cout << "i: " << i << endl;
        if (i > 0 && !has[type[i]].count(leftVal[i])) {}
        else {
            for (int t = 1; t <= n; t++) {
                int cl = ptLeft[t], cr = ptRight[t];
                //cout << "t = " << t << endl;
                //cout << "cl = " << cl << ", " << "cr = " << cr << endl;
                if (t != type[i]) {
                    if (cl == 0 && cr == 0) {
                        continue;
                    }
                    else if (cl == 0) {
                        cand++;
                        ways = mult(ways,cr);
                    }
                    else if (cr == 0) {
                        cand++;
                        ways = mult(ways,cl);
                    }
                    else if (cl == 1 && cr == 1) {
                        //have to pick only one
                        cand++;
                        ways = mult(ways,(cl+cr));
                    }
                    else {
                        //must pick 2
                        cand += 2;
                        if (cl < cr) swap(cl,cr);
                        int add = mult(cl-cr,cr);
                        madd(add,mult(cr,cr-1));
                        ways = mult(ways,add);
                    }
                }
                else {
                    assert(cl >= 1);
                    //left is already chosen, now see if right is chosen
                    if (cr >= 2 || (cr == 1 && leftVal[i] != cows[t][cr-1])) {
                        cand += 2;
                        int add = leftVal[i] > cows[t][cr-1] ? cr : cr-1;
                        ways = mult(ways,add);
                    }
                    else {
                        cand++;
                    }
                }
            }

            if (cand > ans.first) {
                ans = {cand,ways};
            }
            else if (cand == ans.first) {
                madd(ans.second,ways);
            }
        }
        //cout << "i = " << i << ", cand = " << cand << endl;
        //update ptLeft, ptRight
        if (i < n) {
            int t = type[i+1];
            while (ptLeft[t] < cows[t].size() && 
                   cows[t][ptLeft[t]] <= leftVal[i+1]) {
                ++ptLeft[t];
            }
            while (ptRight[t]-1 >= 0 && 
                   cows[t][ptRight[t]-1] >= rightVal[i+1]) {
                --ptRight[t];
            }
        }
    }
    cout << ans.first << ' ' << ans.second << endl;
}
