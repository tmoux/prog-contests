#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double PI = 3.14159265358979323846;

int n, r;

double dist(int a, int b) {
    double theta = min(abs(a-b),n-abs(b-a))/(double)(n) * 2 * PI;
    return sqrt(2.0*(1-cos(theta)));
}

double calc(int i, vector<int>& vs) {
    int nn = vs.size();
    double res = 0.0;
    for (int j = i; j < i + nn - 1; j++) {
        int a = j % nn;
        int b = (j+1) % nn;
        res += dist(vs[a],vs[b]);
    }
    return res;
}

double rcalc(int i, vector<int>& vs) {
    int nn = vs.size();
    double res = 0.0;
    for (int j = i; j > i - nn + 1; j--) {
        int a = (j+2*nn) % nn;
        int b = (j+2*nn-1) % nn;
        res += dist(vs[a],vs[b]);
    }
    return res;
}

int main()
{
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        cin >> n >> r;
        string s; cin >> s;
        vector<int> rs, gs, bs;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'R') {
                rs.push_back(i);
            }
            else if (s[i] == 'G') {
                gs.push_back(i);
            }
            else {
                bs.push_back(i);
            }
        }
        if (rs.empty()) rs.push_back(-1);
        if (gs.empty()) gs.push_back(-1);
        if (bs.empty()) bs.push_back(-1);
        double maxans = 1e18;
        for (int i = 0; i < rs.size(); i++) {
            int rr = rs[i]; 
            for (int j = 0; j < gs.size(); j++) {
                int gg = gs[j];
                for (int k = 0; k < bs.size(); k++) {
                    int bb = bs[k];
                    double ans;
                    if (rr != -1 && gg == -1 && bb != -1) {
                        int rprev = rs[(i+rs.size()-1)%rs.size()];
                        int rnext = rr==-1?0:rs[(i+rs.size()+1)%rs.size()];
                        ans = min(calc(i,rs)+dist(rprev,bb),rcalc(i,rs)+dist(rnext,bb)) + min(calc(k,bs),rcalc(k,bs));
                    }
                    else {
                        int rprev = rr==-1?0:rs[(i+rs.size()-1)%rs.size()];
                        int rnext = rr==-1?0:rs[(i+rs.size()+1)%rs.size()];
                        int gprev = gg==-1?0:gs[(j+gs.size()-1)%gs.size()];
                        int gnext = gg==-1?0:gs[(j+gs.size()+1)%gs.size()];
                        if (rr != -1 && gg == -1 && bb == -1) {
                            ans = min(calc(i,rs),rcalc(i,rs));
                        }
                        else if (rr == -1 && gg != -1 && bb == -1) {
                            ans = min(calc(j,gs),rcalc(j,gs));
                        }
                        else if (rr == -1 && gg == -1 && bb != -1) {
                            ans = min(calc(k,bs),rcalc(k,bs));
                        }
                        else if (rr != -1 && gg != -1 && bb == -1) {
                            ans = min(calc(i,rs)+dist(rprev,gg),rcalc(i,rs)+dist(rnext,gg)) + min(calc(j,gs),rcalc(j,gs));
                        }
                        else if (rr == -1 && gg != -1 && bb != -1) {
                            ans = min(calc(j,gs)+dist(gprev,bb),rcalc(i,gs)+dist(gnext,bb)) + min(calc(k,bs),rcalc(k,bs));
                        }
                        else {
                            ans = min(calc(j,gs)+dist(gprev,bb),rcalc(i,gs)+dist(gnext,bb)) + min(calc(k,bs),rcalc(k,bs));
                            ans += min(calc(i,rs)+dist(rprev,gg),rcalc(i,rs)+dist(rnext,gg));
                        }
                        /*
                        ans = 0.0;
                        int rprev = rr==-1?0:rs[(i+rs.size()-1)%rs.size()];
                        int gprev = gg==-1?0:gs[(j+gs.size()-1)%gs.size()];
                        if (rr != -1) ans += calc(i,rs);
                        if (rr != -1 && gg != -1) ans += dist(rprev,gg);
                        if (gg != -1) ans += calc(j,gs);
                        if (gg != -1 && bb != -1) ans += dist(gprev,bb);
                        if (bb != -1) ans += calc(k,bs);
                        */
                    }
                    maxans = min(maxans,ans);
                }
            }
        }
        maxans *= r;
        cout << fixed << setprecision(3) << "Scenario #" << a << ": " << maxans << '\n';
        /*
        cout << calc(3,rs) << '\n';
        cout << dist(0,1) << '\n';
        */
    }

    return 0;
}

