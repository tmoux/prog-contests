#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 155;
int N; 
int ans[maxn];
vector<int> labels[maxn]; //indices of labels

int ask(vector<int>& v) {
    cout << v.size() << ' ';
    for (int i: v) cout << i << ' ';
    cout << endl;
    int res; cin >> res;
    return res;
}

int distinct[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    ans[1] = 1;
    labels[1].push_back(1);
    int last = 1;
    for (int i = 1; i <= N; i++) {
        vector<int> v(i);
        iota(begin(v),end(v),1);
        distinct[i] = ask(v);
    }

    for (int i = 2; i <= N; i++) {
        int r1 = distinct[i-1];
        int r2 = distinct[i];
        if (r2 == r1+1) {
            ans[i] = ++last;
            labels[last].push_back(i);
        }
        else {
            //binary search for which one
            int lo = 1, hi = last;
            while (lo < hi) {
                int mid = (lo+hi)/2;
                vector<int> v;
                for (int j = 1; j <= mid; j++) {
                    v.push_back(labels[j][0]);
                }
                v.push_back(i);
                int r = ask(v);
                if (r == mid) {
                    hi = mid;
                }
                else {
                    lo = mid+1;
                }
            }
            ans[i] = lo;
            /*
            for (int i = 1; i <= last; i++) {
                vector<int> v = {labels[i][0],i};
                if (ask(v) == 1) {
                    ans[i] = i;
                }
            }
            */
        }
    }
    cout << 0 << ' ';
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

