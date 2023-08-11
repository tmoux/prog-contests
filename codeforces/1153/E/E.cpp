#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int query(int x1, int y1, int x2, int y2) {
    printf("? %d %d %d %d\n",x1,y1,x2,y2);
    fflush(stdout);
    int ans; cin >> ans;
    if (ans == -1) exit(0);
    return ans;
}

void answer(int x1, int y1, int x2, int y2) {
    printf("! %d %d %d %d\n",x1,y1,x2,y2);
    fflush(stdout);
    exit(0);
}

int main()
{
    int n; cin >> n;
    //check rows first;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        int q = query(i,1,i,n);
        if (q&1) {
            int lo = 1, hi = n;
            while (lo < hi) {
                int m = (lo+hi)/2;
                int w = query(i,lo,i,m);
                if (w&1) hi = m;
                else lo = m+1;
            }
            assert(lo==hi);
            ans.push_back(i);
            ans.push_back(lo);
        }
    }
    if (ans.size() == 0) {
        for (int i = 1; i <= n; i++) {
            int q = query(1,i,n,i);
            if (q&1) {
                if (ans.size() == 2) {
                    ans.push_back(ans[0]);
                    ans.push_back(i);
                }
                else {
                    int lo = 1, hi = n;
                    while (lo < hi) {
                        int m = (lo+hi)/2;
                        int w = query(lo,i,m,i);
                        if (w&1) hi = m;
                        else lo = m+1;
                    }
                    assert(lo==hi);
                    ans.push_back(lo);
                    ans.push_back(i);    
                }
            }
        }
    }
    answer(ans[0],ans[1],ans[2],ans[3]);
}

