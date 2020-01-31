#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int calc(string s) {
    int res = 0;
    int mult = 1;
    for (int i = s.size()-1; i >= 0; i--) {
        res += (s[i]-'0')*mult;
        mult *= 10;
    }
    return res;
}

class TimeDifference {
public:
    string calculate(string startTime, string endTime) {
        string h1, m1, h2, m2;
        for (int i = 0; i < startTime.size(); i++) {
            if (startTime[i] == ':') {
                h1 = startTime.substr(0,i);
                m1 = startTime.substr(i+1);
            }
        }
        for (int i = 0; i < endTime.size(); i++) {
            if (endTime[i] == ':') {
                h2 = endTime.substr(0,i);
                m2 = endTime.substr(i+1);
            }
        }
        pair<int,int> t1 = {calc(h1),calc(m1)};
        pair<int,int> t2 = {calc(h2),calc(m2)};
        bool swapped = false;
        if (t1.first > t2.first || (t1.first == t2.first && t1.second > t2.second)) {
            swapped = true;
            swap(t1,t2);
        }
        int tot = t2.first*60+t2.second-(t1.first*60+t1.second);
        //cout << "tot = " << tot << '\n';
        pair<int,int> ans = {tot/60,tot%60};
        string ret = "";
        if (swapped) ret += '-';
        ret += to_string(ans.first);
        ret += ':';
        string minute = to_string(ans.second);
        if (minute.size() == 1) minute = '0' + minute;
        ret += minute;
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    TimeDifference t;
    cout << t.calculate("10:47","010:47") << '\n';
}

