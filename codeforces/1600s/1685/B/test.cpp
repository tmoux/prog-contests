#include <bits/stdc++.h>
#define int long long
using pii=std::pair<int,int>;
using namespace std;

int t, a, b, ab, ba;
string s;
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    for(int cases = 0; cases < t; cases++)
    {
        cin >> a >> b >> ab >> ba >> s;
        vector<string> parts;
        string cur;
        for(auto ch : s)
        {
            if(!cur.empty() && ch == cur.back())
            {
                parts.push_back(cur);
                cur.clear();
            }
            cur += ch;
        }
        assert(!cur.empty());
        parts.push_back(cur);
        int have_ab_or_ba = 0;
        vector<int> ab_sizes, ba_sizes;
        for(auto p : parts)
        {
            assert(!p.empty());
            int sz = p.size();
            if(p.back() == p.front())
            {
                assert(sz & 1);
                if(p.front() == 'A')
                    a--;
                else
                    b--;
                have_ab_or_ba += sz / 2;
            }
            else
            {
                assert(!(sz & 1));
                if(p.front() == 'A')
                {
                    ab -= sz / 2;
                    ab_sizes.push_back(sz / 2);
                }
                else
                {
                    ba -= sz / 2;
                    ba_sizes.push_back(sz / 2);
                }
            }
        }
        sort(ab_sizes.begin(), ab_sizes.end(), greater<>());
        sort(ba_sizes.begin(), ba_sizes.end(), greater<>());
        if(have_ab_or_ba > 0)
        {
            if(ab > 0)
            {
                int rem = min(ab, have_ab_or_ba);
                ab -= rem;
                have_ab_or_ba -= rem;
            }
            if(ba > 0)
            {
                int rem = min(ba, have_ab_or_ba);
                ba -= rem;
                have_ab_or_ba -= rem;
            }
            a -= have_ab_or_ba;
            b -= have_ab_or_ba;
            have_ab_or_ba = 0;
        }
        if(ab < 0 && ba > 0)
            for(auto x : ab_sizes)
            {
                if(ab == 0)
                    break;
                int take = min({-(ab + 1), ba, x - 1});
                assert(take >= 0);
                ab += (take + 1);
                ba -= take;
                a--;
                b--;
            }
        if(ba < 0 && ab > 0)
            for(auto x : ba_sizes)
            {
                if(ba == 0)
                    break;
                int take = min({-(ba + 1), ab, x - 1});
                assert(take >= 0);
                ba += (take + 1);
                ab -= take;
                a--;
                b--;
            }
        if(ab < 0)
        {
            a -= -ab;
            b -= -ab;
            ab = 0;
        }
        if(ba < 0)
        {
            a -= -ba;
            b -= -ba;
            ba = 0;
        }
        if(a == 0 && b == 0 && ab == 0 && ba == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
