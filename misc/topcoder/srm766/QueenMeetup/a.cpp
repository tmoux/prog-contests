#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char grid[50][50];
class QueenMeetup
{
public:
    void add(vector<int>& ans, int id, int nr, int nc) {
        ans.push_back(id);
        ans.push_back(nr);
        ans.push_back(nc);
    }
    vector<int> move(int d, vector<int> r, vector<int> c) {
        vector<pair<pair<int,int>,int>> ps;
        for (int i = 0; i < r.size(); i++) {
            ps.push_back({make_pair(r[i],c[i]),i});
        }
        sort(ps.begin(),ps.end());
        //try to move up and to the left as much as possible
        vector<int> ans;
        map<int,int> rr, cc;

        for (int i = 0; i <= 5; i++) {
            for (int j = 0; j <= 5; j++) {
                grid[i][j] = '.';
            }
        }
        for (int i = 0; i < ps.size(); i++) {
            int row = ps[i].first.first;
            int col = ps[i].first.second;
            int id = ps[i].second;

            int nr = rr.count(col) ? rr[col] + 1 : 0;
            if (nr != row) add(ans,id,nr,col);

            //cout << id << ": " << nr << ' ' << col << '\n';

            int nc = cc.count(nr) ? cc[nr] + 1 : 0;
            if (nc != col) add(ans,id,nr,nc);

            rr[nc] = nr;
            cc[nr] = nc;

            grid[nr][nc] = id+'0';

            /*
            for (int i = 0; i <= 5; i++) {
                for (int j = 0; j <= 5; j++) {
                    cout << grid[i][j];
                }
                cout << '\n';
            }
            cout << '\n';
            */
        }
        
        return ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    QueenMeetup t;
    auto p = t.move(6,{0,1,3},{0,1,3});
    for (auto q: p) {
        cout << q << ' ';
    }
    cout << '\n';
}

