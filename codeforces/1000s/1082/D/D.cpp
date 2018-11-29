#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<int,int>> edges;
vector<int> ones, twoplus;

int a[505];
void addedge(int x, int b) {
    edges.push_back({x,b});
    a[x]--;
    a[b]--;

}

void printout(int diam) {
    cout << "YES " << (diam) << '\n';
    cout << edges.size() << '\n';
    for (auto& p: edges) {
        cout << p.first << ' ' << p.second << '\n';
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) ones.push_back(i);
        else twoplus.push_back(i);
    }
    if (twoplus.empty()) {
        cout << "NO" << '\n';
        return 0;
    }
    for (int i = 0; i < twoplus.size() - 1; i++) {
        addedge(twoplus[i],twoplus[i+1]);
    }
    
    if (ones.size() == 0) {
        //done
        printout(twoplus.size()-1);
        return 0;
    }
    else if (ones.size() == 1) {
        addedge(ones[0],twoplus[0]);
        printout(twoplus.size());
        return 0;
    }
    else {
        addedge(ones.back(),twoplus[0]);
        ones.pop_back();
        addedge(ones.back(),twoplus.back());
        ones.pop_back();
        int idx = 0;
        for (int i: ones) {
            while (a[twoplus[idx]] == 0) {
                idx++;
                if (idx == twoplus.size()) {
                    //impossible
                    cout << "NO" << '\n';
                    return 0;
                }
            }
            addedge(i,twoplus[idx]);
        }
        printout(twoplus.size()+1);
    }

    return 0;
}

