#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<char,string> ToInstruction =
{
    {'3',"Add"},
    {'4',"Subt"},
    {'b',"AddI"},
    {'a',"Clear"},
    {'1',"Load"},
    {'2',"Store"},
    {'5',"Input"},
    {'6',"Output"},
    {'9',"Jump"},
    {'8',"Skipcond"},
    {'0',"JnS"},
    {'c',"JumpI"},
    {'e',"StoreI"}, //storeI, loadI are swapped?
    {'d',"LoadI"},
    {'7',"Halt"}
};

set<string> args = {
    "Add",
    "Subt",
    "AddI",
    "Load",
    "Store",
    "Jump",
    "Skipcond",
    "JnS",
    "JumpI",
    "StoreI",
    "LoadI"
};

char hx(int x) {
    if (x < 10) return '0'+x;
    return (x-10)+'a';
}

int xh(char c) {
    if ('0' <= c && c <= '9') return c-'0';
    return c-'a'+10;
}

int toInt(string s) {
    int res = 0;
    assert(s.size() == 3); 
    int mult = 1;
    for (int i = 2; i >= 0; i--) {
        res += mult*xh(s[i]);
        mult *= 16;
    }
    return res;
}

string toHex(int x) {
    string ret = "";    
    while (x > 0) {
        ret = ret + hx(x%16);
        x /= 16;
    }
    while (ret.size() < 3) {
        ret = '0' + ret;
    }
    return ret;
}

struct Instr {
    string instr;
    int operand;
    int id;
};

const int maxn = 5005;

vector<Instr> v;
vector<int> ans[maxn], rev[maxn];
bool trav[maxn];

void dfs(int i) {
    if (trav[i]) return;
    if (i >= v.size()) return;
    trav[i] = true;
    Instr& in = v[i];
    if (in.instr == "Skipcond") {
        ans[i].push_back(i+1);
        rev[i+1].push_back(i);
        ans[i].push_back(i+2);
        rev[i+2].push_back(i);
        dfs(i+1);
        dfs(i+2);
    }
    else if (in.instr == "Jump") {
        ans[i].push_back(in.operand);
        rev[in.operand].push_back(i);
        dfs(in.operand);
    }
    else if (in.instr == "JnS") {
        assert(false);
    }
    else {
        if (in.instr == "Halt") {
            return;
        }
        else {
            ans[i].push_back(i+1);
            rev[i+1].push_back(i);
            dfs(i+1);
        }
    }
}

bool contiguous(int i) { // check if i and i+1
    return ans[i].size() == 1 && ans[i][0] == i+1 && rev[i+1].size() == 1 && rev[i+1][0] == i;
}

vector<int> adj[maxn];

int main() {
    string s;
    bool done = false;
    int cnt = 0;
    while (cin >> s) {
        string instr = ToInstruction[s[0]];
        int operand = toInt(s.substr(1));
        //cout << instr << ' ' << operand << endl;
        v.push_back({instr,operand,cnt});
        cnt++;
    }
    dfs(0);
    vector<vector<int>> ret;
    vector<int> cur = {};
    for (int i = 0; i < v.size(); i++) {
        if (!trav[i]) continue;
        if (contiguous(i)) {
            cur.push_back(i);
        }
        else {
            cur.push_back(i);
            ret.push_back(cur);
            cur.clear();
        }
    }
    if (!cur.empty()) ret.push_back(cur);
    for (auto vv: ret) {
        for (auto j: vv) {
            printf("%03x",j);
            cout << ": " << v[j].instr;
            if (args.count(v[j].instr)) {
                cout << " ";
                printf("%03x",v[j].operand);
            }
            cout << '\n';
        }
        cout << "Next: ";
        cout << "[";
        int j = vv.back();
        for (int k = 0; k < ans[j].size(); k++) {
            printf("%03x",ans[j][k]);
            if (k < (int)ans[j].size()-1) cout << ", ";
        }
        cout << "]\n";
        if (vv != ret.back()) cout << '\n';
    }
    /*
    for (int i = 0; i < v.size(); i++) {
        if (!trav[i]) continue;
        printf("%03x",i);
        cout << ": " << v[i].instr;
        if (args.count(v[i].instr)) {
            cout << " ";
            printf("%03x",v[i].operand);
        }
        cout << '\n';
        if (ans[i].size() == 1 && ans[i][0] == i+1 && rev[i+1].size() == 1 &&  rev[i+1][0] == i) {
            //part of block
        }
        else {
            cout << "Next: ";
            cout << "[";
            for (int j = 0; j < ans[i].size(); j++) {
                printf("%03x",ans[i][j]);
                if (j < (int)ans[i].size()-1) cout << ", ";
            }
            cout << "]\n\n";
        }
    }
    */
}
