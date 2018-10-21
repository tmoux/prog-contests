#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Request
{
    int size, cost, id;
    bool operator==(const Request& rhs) {
        return size == rhs.size && cost == rhs.cost && id == rhs.id;
    }
};
struct Table
{
    int size, id;
    bool operator<(const Table& rhs) const {
        return size < rhs.size;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<Request> reqs(n);
    for (int i = 0; i < n; i++) {
        cin >> reqs[i].size >> reqs[i].cost;
        reqs[i].id = i+1;
    }
    int k; cin >> k;
    vector<Table> tables(k);
    for (int i = 0; i < k; i++) {
        int ai; cin >> ai;
        tables[i].size = ai;
        tables[i].id = i+1;
    }
    //get answer
    vector<pair<int,int>> ans;
    int tot = 0;
    sort(tables.begin(),tables.end());
    for (int i = 0; i < k; i++) {
        Table t = tables[i];
        Request r;
        r.cost = -1;
        r.size = -1;
        for (int j = 0; j < reqs.size(); j++) {
            if (reqs[j].size <= t.size) {
                if (reqs[j].cost > r.cost) {
                    r = reqs[j];
                }
                else if (reqs[j].cost == r.cost && reqs[j].size < r.size) {
                    r = reqs[j];
                }
            }
        }
        if (r.cost != -1) {
            reqs.erase(remove(reqs.begin(),reqs.end(),r),reqs.end());
            ans.push_back({t.id,r.id});
            tot += r.cost;
            //cout << t.size << ": " << r.size << '\n';
        }
    }

    //output
    cout << ans.size() << ' ' << tot << '\n';
    for (auto p: ans) {
        cout << p.second << ' ' << p.first << '\n';
    }
    

    return 0;
}
	

