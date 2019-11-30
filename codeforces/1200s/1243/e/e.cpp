#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxk = 16;
int k;
vector<ll> a[maxk];
ll s[maxk];

map<int,int> which; //maps number to box

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k;
    ll sum = 0;
    for (int i = 0; i < k; i++) {
        int ni; cin >> ni;
        while (ni--) {
            ll ai; cin >> ai;
            a[i].push_back(ai);
            sum += ai;
            s[i] += ai;
            which[ai] = i;
        }
    }
    if (sum % k != 0) {
        cout << "No\n";
        return 0;
    }
    ll target = sum/k;
    for (ll i: a[0]) {
        //cout << "trying " << i << '\n';
        vector<pair<int,int>> ans;
        for (int j = 0; j < k; j++) {
            if (s[j] == target) {
                ans.push_back({a[j][0],j});
            }
        }

        vector<bool> use(k);
        use[0] = true;
        int curr = 0;
        ll need = target-(s[0]-i);
        bool poss = true;

        if (ans.size() == k) {
            goto check;
        }
        
        while (true) {
            if (!which.count(need)) {
                poss = false;
                break;
            }
            else {
                //printf("going from %d, need %d\n",curr,need);
                int next = which[need];
                if (use[next]) {
                    poss = false;
                    break;
                }
                use[next] = true;
                ans.push_back({need,curr});
                //calc new need
                curr = next;
                need = target-(s[curr]-need);
            }

            if (need == i) {
                //we've wrapped around to the beginning
                ans.push_back({need,curr});
                break;
            }
        }
        check:
        if (poss && ans.size() == k) {
            cout << "Yes\n";
            vector<pair<int,int>> res(k);
            for (auto p: ans) {
                res[which[p.first]] = p;
            }
            for (auto p: res) {
                cout << p.first << ' ' << p.second+1 << '\n';
            }
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}

