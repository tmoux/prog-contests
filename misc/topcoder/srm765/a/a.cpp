#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

class MilkConsumption
{
    vector<int> findMaxRegion(vector<int> population, vector<int> totalConsumption) {
        pair<ld,int> best = {0.0,-1};
        for (int i = 0; i < population.size(); i++) {
            ld avg = totalConsumption[i]/(ld)(population[i]);
            best = max(best,{avg,i});
        }
        return {best.second};
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);


}

