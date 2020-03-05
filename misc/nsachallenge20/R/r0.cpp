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

int main() {
    string s;
    bool done = false;
    int cnt = 0;
    while (cin >> s) {
        cout << toHex(cnt) << ": ";
        if (!done) {
            string instr = ToInstruction[s[0]];
            //check if invalid
            if (s[0] == 'f' || (!args.count(instr) && s.substr(1) != "000")) {
                cout << "ERROR " << s.substr(1) << '\n';
            }
            else {
                cout << instr;
                if (args.count(instr)) {
                    cout << " " << s.substr(1) << '\n';
                }
                else {
                    cout << '\n';
                }

                //check for halt
                if (instr == "Halt") {
                    done = true;
                }
            }
        }
        else {
            cout << "HEX " << s << endl;
        }
        cnt++;
    }
}
