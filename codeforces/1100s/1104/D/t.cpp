#include <bits/stdc++.h>
#define rep(i,m,n) for(int i = (m); i < (n); i++)
#define rrep(i,m,n) for(int i = (m); i >= (n); i--)
#define print(x) cout << (x) << endl;
#define print2(x,y) cout << (x) << " " << (y) << endl;
#define printa(x,n) for(int i = 0; i < n; i++){ cout << (x[i]) << " \n"[i == n-1];}
#define printp(x,n) for(int i = 0; i < n; i++){ cout << "(" << x[i].first << ", " << x[i].second << ") "; } cout << endl;
#define INF (1e18)
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
typedef pair<ll, ll> lpair;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    string ss;
    while(1){
        cin >> ss;
        if(ss == "end") break;
        ll pos = -1;
        cout << "? 0 1" << endl;
        char c1;
        cin >> c1;
        if(c1 == 'x'){
            print("! 1");
            continue;
        }
        rep(i,0,31){
            char c;
            cout << "? " << (1<<i) << " " << (1<<(i+1)) << endl;
            cin >> c;
            if(c == 'x'){
                pos = i;
                break;
            }
        }
        ll lv = pow(2,pos);
        ll rv = pow(2,pos+1);
        while(rv - lv > 1){
            char cc;
            ll mid = (rv + lv) / 2;
            cout << "? " << mid << " " << rv << endl;
            cin >> cc;
            if(cc == 'x'){
                lv = mid;
            }else{
                rv = mid;
            }
        }
        cout << "! " << rv << endl;
        //16 17 18 0 1 2 3 4 ... 10 11 12 13

    }

}
