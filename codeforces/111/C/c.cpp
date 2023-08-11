#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 44;
int n, m;

int dp[maxn][1<<12]; //# filled, want to minimize this
int pow5[7];

int add[1<<12][1<<12];

vector<int> top2[3], bot2[3]; //0 = top, 1 = middle, 2 = bottom
int pc(int x) {
    return __builtin_popcount(x);
}
void amin(int& a, int b) {
    a = min(a,b);
}

int f(int i, int mask) {
    int& res = dp[i][mask];
    if (res != -1) return res;
    if (i == n) return 0;
    int t = i == 0 ? 0 : i == n-1 ? 2 : 1;
    vector<int>& tops = top2[t];
    vector<int>& bots = bot2[t];
    res = maxn*maxn;
    for (int j = 0; j < tops.size(); j++) {
        int top = tops[j];
        int bot = bots[j];
        amin(res,add[mask][top]+f(i+1,bot));
    }
    //printf("[%d][%d]: %d\n",i,mask,res);
    return res;
}

string msk(int x) {
    string s;
    for (int i = 0; i < 6; i++)
        s += x&(1<<i) ? '1' : '0'; 
    s += '\n';
    for (int i = 6; i < 12; i++)
        s += x&(1<<i) ? '1' : '0'; 
    return s;
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    if (m > n) swap(n,m);
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    pow5[0] = 1;
    for (int i = 1; i < 7; i++) pow5[i] = pow5[i-1] * 5;
    //m <= 6
    for (int m1 = 0; m1 < (1<<12); m1++) {
        for (int m2 = 0; m2 < (1<<12); m2++) {
            int t1 = m1 & ((1<<6)-1);
            int t2 = m2 & ((1<<6)-1);
            int b1 = m1 & (((1<<6)-1)<<6);
            int b2 = m2 & (((1<<6)-1)<<6);
            add[m1][m2] = pc(t1|t2)-pc(t1)+pc(b1|b2);
            /*
            cout << msk(m1) << "\n";
            cout << t1 << ' ' << (b1>>6) << "\n\n";
            cout << msk(m2) << '\n';
            cout << t2 << ' ' << (b2>>6) << '\n';
            cout << ": " << add[m1][m2] << '\n';
            */
        }
    }
    for (int i = 0; i < pow5[m]; i++) {
        //0 = stay
        //1 = left
        //2 = right
        //3 = up
        //4 = down
        int top = 0, bot = 0;
        bool valid = true;
        bool hasUp = false, hasDown = false;
        int cp = i;
        for (int j = 0; j < m; j++) {
            int t = cp % 5;
            cp /= 5;
            if (j == 0 && t == 1) {
                valid = false;
                break;
            }
            if (j == m-1 && t == 2) {
                valid = false;
                break;
            }
            if (t == 3) hasUp = true;
            if (t == 4) hasDown = true;

            if (t == 0) {
                top |= (1<<(j+6));
                bot |= (1<<j);
            }
            else if (t == 1) {
                top |= (1<<(j-1+6));
                bot |= (1<<(j-1));
            }
            else if (t == 2) {
                top |= (1<<(j+1+6));
                bot |= (1<<(j+1));
            }
            else if (t == 3) {
                top |= (1<<j);
            }
            else if (t == 4) {
                bot |= (1<<(j+6));
            }
        }
        if (!valid) continue;
        assert(top < (1<<12));
        assert(bot < (1<<12));
        if (!hasUp) {
            top2[0].push_back(top);
            bot2[0].push_back(bot);
        }
        top2[1].push_back(top);
        bot2[1].push_back(bot);
        if (!hasDown) {
            top2[2].push_back(top);
            bot2[2].push_back(bot);
        }
    }
    memset(dp,-1,sizeof dp);
    int ans = f(0,0);
    cout << (n*m-ans) << '\n';
}
