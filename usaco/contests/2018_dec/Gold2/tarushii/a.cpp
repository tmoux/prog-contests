#include <bits/stdc++.h>
using namespace std;
struct subset {
    int s[5];
    subset () {
        for (int i = 0; i < 5; i++) s[i] = 0;
    }
    bool operator<(const subset& a) const{
        for (int i = 0; i < 5; i++){
            if (s[i] < a.s[i]) return true;
            if (s[i] > a.s[i]) return false;
        }
        return false;
    }
};
int N;
const int MXN = 5e4+10;
vector<int> fav[MXN];
map<subset, int> c;

int main(){
    ifstream cin("cowpatibility.in");
    ofstream cout("cowpatibility.out");
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 5; j++){
            int x; cin >> x;
            fav[i].push_back(x);
        }
        sort(fav[i].begin(), fav[i].end());
    }
    long long compat = 0;

    ///////////////////////
    //Helper function to get a subset
    auto getSub = [](const vector<int>& arr, int mask) {
      subset ret = subset();
      int idx = 0;
      for (int i = 0; i < 5; i++) {
        if (mask & (1<<i)) ret.s[idx++] = arr[i];
      }
      return ret;
    };

    //precompute whether subsets are even or odd (~300ms speedup on slowest case)
    vector<int> pc(1<<5);
    for (int i = 0; i < (1<<5); i++)
      pc[i] = __builtin_popcount(i);

    for (int i = 0; i < N; i++) {
      //iterate over the subsets 00001 --> 11111
      for (int mask = 1; mask < (1<<5); mask++) {
        subset sub = getSub(fav[i],mask);
        compat += c[sub]*((pc[mask]&1)?1:-1);
        c[sub]++;
      }
    }
    //////////////////////
    /*
    for (int i = 0; i < N; i++){
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        
        for (int j = 0; j < 5; j++){
            subset v = subset();
            v.s[0] = fav[i][j];
            c1+=c[v];
            c[v]++;
            for (int k = j+1; k < 5; k++){
                subset v = subset();
                v.s[0] = fav[i][j]; v.s[1] = fav[i][k]; v.s[2] = 0;
                c2+=c[v];
                c[v]++;
                int x = 0;
                for (int l = 0; l < 5; l++){
                    if (l!=j && l!=k){
                        v.s[x++] = fav[i][l];
                    }
                }
                c3+=c[v];
                c[v]++;
            }
        }
        int c4 = 0;
        for (int j =0 ; j < 5; j++){
            subset v = subset();
            int x = 0;
            for (int k = 0; k < 5; k++){
                if (k!=j) v.s[x++] = fav[i][k];
            }
            c4+=c[v];
            c[v]++;
        }
        subset v = subset();
        for (int j = 0; j < 5; j++) v.s[j] = fav[i][j];
        int c5= c[v];
        c[v]++;
        compat= compat+ (c1-c2+c3-c4+c5);
        //cout << compat << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4 << ' ' << c5 <<  endl;
    }
    */
    long long ans = ((long long)N*(N-1))/2 - compat;
    cout << ans << '\n';
}
