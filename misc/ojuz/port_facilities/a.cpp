#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e6+6, M = 1e9+7;
int N;
pair<int,int> invl[maxn];
int color[maxn]; //0 = unset, 1, 2
int at[maxn];
struct Line
{
    int se, en;
} lines[maxn];

int start[4*maxn], endd[4*maxn], val[4*maxn];
void build(int i, int l, int r) {
    start[i] = l;
    endd[i] = r;
    if (l == r) {
        return;    
    }
    int m = (l+r)/2;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
}

int update(int a, int b) {
    if (a == -1 || b == -1) return -1;
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;
    assert((a == 1 && b == 2) || (a == 2 && b == 1));
    /*
    if (!((a == 1 && b == 2) || (a == 2 && b == 1))) {
        cout << a << ' ' << b << endl;
        exit(0);
    }
    */
    return -1;
}

void sset(int i, int idx, int x) {
    if (start[i] == idx && endd[i] == idx) {
        val[i] = x;
        return;
    }
    if (idx <= (start[i]+endd[i])/2)
        sset(i*2,idx,x);
    else 
        sset(i*2+1,idx,x);
    val[i] = update(val[i*2],val[i*2+1]);    
}

int getColor(int i, int l, int r) {
    if (l <= start[i] && endd[i] <= r) {
        return val[i];
    }
    int m = (start[i]+endd[i])/2;
    int res = 0;
    if (l <= m) res = update(res,getColor(i*2,l,r));
    if (r > m) res = update(res,getColor(i*2+1,l,r));
    return res;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int a, b; cin >> a >> b;
        lines[i] = {a,b};
        at[a] = i;
        at[b] = -i;
        //+ means start, - means end
    }
    //Keep an "active" set of lines in a segment tree by their 
    //endpoint. 
    build(1,1,2*N);
    int currCount = 0;
    int components = 0;
    bool fail = false;
    for (int i = 1; i <= 2*N; i++) {
        bool isStart = at[i] > 0;
        int id = abs(at[i]);
        int se = lines[id].se;
        int en = lines[id].en;
        if (isStart) {
            int c = getColor(1,1,en);
            if (c == -1) {
                fail = true;
                break;
            }
            else if (c == 0) {
                ++components;
                sset(1,en,1);
            }
            else {
                assert(c == 1 || c == 2);
                int d = c == 1 ? 2 : 1;
                sset(1,en,d);
            }
        }
        else {
            //remove from set
            sset(1,en,0);                
        }
    }
    if (fail) {
        cout << "0\n";
    }
    else {
        int ans = 1;
        while (components--) {
            ans = (1LL*ans*2) % M;
        }
        cout << ans << '\n';
    }
}