#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <type_traits>
#include <unordered_map>
#include <sstream>
#include <stack>
using namespace std;
using namespace __gnu_pbds;
#define endl '\n'
// #define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
// #define int long long
#define double long double
#define F first
#define S second
#define PE = setprecision(9)
// const int MAXN=5e6+3,INF=1e17,MOD=998244353;
// const double EPS=1e-10, PI=3.141592653589793238462643383279502;
template<class T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update> ;
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-funroll-all-loops,-fpeel-loops,-funswitch-loops")


vector<string> to_list(string s) {
    vector<string> list;
    string temp = "";
    int i = 0;
    while (i < s.length()) {
        if (s[i] != ' ') {
            temp += s[i];
        } else {
            list.push_back(temp);
            temp = "";
        }
        i++;
    }
    list.push_back(temp);
    return list;
}

void do_work(int sub){
    string piecesNum; 
    getline(cin, piecesNum);
    int n = stoi(piecesNum);
    map<string, int> stationToNum;
    map<int, string> numToStation;
    vector<vector<int>> graph(32);

    string piece;
    
    int m = 0;

    for (int i = 0; i < n; i++) {
        getline(cin, piece);
        vector<string> pieceList = to_list(piece);
        string station = pieceList[0];
        if (stationToNum.find(station) == stationToNum.end()) {
            stationToNum[station] = m;
            numToStation[m] = station;
            m++;
        }
        for (int j = 1; j < pieceList.size(); j++) {
            if (stationToNum.find(pieceList[j]) == stationToNum.end()) {
                stationToNum[pieceList[j]] = m;
                numToStation[m] = pieceList[j];

                m++;
            }
            string connection = pieceList[j];
            graph[stationToNum[station]].push_back(stationToNum[connection]);
            graph[stationToNum[connection]].push_back(stationToNum[station]);
        }
    }

    string source, dest; cin >> source >> dest;
    // if (!stationToNum.count(source) || !stationToNum.count(dest)) {
    // if (!stationToNum.count(dest)) {
    if (false) {
      cout << "no route found" << endl;
      return;
    }
    bool found[m];
    for (int i = 0; i < m; i++) {
        found[i] = false;
    }
    int lst[m];

    found[stationToNum[source]] = true;

    queue<int> q; q.push(stationToNum[source]);

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        cout << numToStation[cur] << endl;
        for (auto& nxt : graph[cur]) {
            if (!found[nxt]) {
                found[nxt] = true;
                lst[nxt] = cur;
                q.push(nxt);
            }
        }
    }

    cout << "dest " << stationToNum[dest] << endl;
    cout << found[stationToNum[dest]] << endl;
    if (found[stationToNum[dest]] == 0) {
        cout << "no route found" << endl;
        return;
    } else {
        vector<string> path;
        int cur = stationToNum[dest];
        while (cur != stationToNum[source]) {
            path.push_back(numToStation[cur]);
            cur = lst[cur];
        }
        path.push_back(source);
        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++) {
          cout << path[i] << " \n"[i == path.size() - 1];
        }
    }


}

int32_t main(){
    // fast;
    int test=1;
    // cin>>test;
    for(int ttt=1;ttt<=test;++ttt) {
        do_work(ttt);
    }
    return 0;
}
