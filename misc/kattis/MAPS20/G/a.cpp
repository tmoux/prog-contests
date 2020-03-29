#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
int n;
vector<int> st;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    string curr;
    for (int i = 0; i < n; i++) {
        curr += s[i];
        if (curr == "SS") {//push int
            int mult = 1;
            i++;
            if (s[i] == 'T') mult = -1;
            int x = 0;
            while (s[++i] != 'N') {
                x <<= 1;
                if (s[i] == 'T') {
                    x |= 1;
                }
            }
            x *= mult;
            //cout << "pushing " << x << '\n';
            st.push_back(x);
            curr.clear();
        }
        else if (curr == "SNS") {//copy
            //cout << "copying\n";
            if (st.empty()) {
                cout << "Invalid copy operation\n";
            }
            else {
                st.push_back(st.back());
            }
            curr.clear();
        }
        else if (curr == "SNT") {//swap top two
            //cout << "swapping\n";
            if (st.size() < 2) {
                cout << "Invalid swap operation\n";
            }
            else {
                swap(st[st.size()-1],st[st.size()-2]);
            }
            curr.clear();
        }
        else if (curr == "SNN") {//discard
            //cout << "discarding\n";
            if (st.empty()) {
                cout << "Invalid remove operation\n";
            }
            else {
                st.pop_back();
            }
            curr.clear();
        }
        else if (curr == "TSSS") {//add
            //cout << "adding\n";
            if (st.size() < 2) {
                cout << "Invalid addition operation\n";
            }
            else {
                int x = st.back(); st.pop_back();
                int y = st.back(); st.pop_back();
                st.push_back(x+y);
            }
            curr.clear();
        }
        else if (curr == "TSST") {//subtract
            //cout << "subtracting\n";
            if (st.size() < 2) {
                cout << "Invalid subtraction operation\n";
            }
            else {
                int x = st.back(); st.pop_back();
                int y = st.back(); st.pop_back();
                st.push_back(y-x);
            }
            curr.clear();
        }
        else if (curr == "TSSN") {//mult
            //cout << "mult\n";
            if (st.size() < 2) {
                cout << "Invalid multiplication operation\n";
            }
            else {
                int x = st.back(); st.pop_back();
                int y = st.back(); st.pop_back();
                st.push_back(x*y);
            }
            curr.clear();
        }
        else if (curr == "TSTS") {//divide
            //cout << "dividing\n";
            if (st.size() < 2) {
                cout << "Invalid division operation\n";
            }
            else {
                int x = st.back(); st.pop_back();
                int y = st.back(); st.pop_back();
                if (x == 0) {
                    cout << "Division by zero\n";
                    st.push_back(y);
                    st.push_back(x);
                }
                else {
                    st.push_back(y/x);
                }
            }
            curr.clear();
        }
        else if (curr == "TNST") {//print top
            //cout << "printing\n";
            if (st.empty()) {
                cout << "Invalid print operation\n";
            }
            else {
                cout << st.back() << '\n';
                st.pop_back();
            }
            curr.clear();
        }
    }
}
