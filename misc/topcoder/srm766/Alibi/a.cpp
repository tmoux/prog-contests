#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Alibi {
public:
    string findMurderer(string murderRoom, int murderTime, vector<int> eventTime, vector<string> eventPerson, vector<string> eventRoom) {
        map<string,set<string>> curr;
        map<string,string> currRoom;
        currRoom["White"] = "Hall";
        currRoom["Green"] = "Hall";
        currRoom["Peacock"] = "Hall";
        currRoom["Plum"] = "Hall";
        currRoom["Scarlett"] = "Hall";
        currRoom["Mustard"] = "Hall";
        curr["Hall"].insert("White");
        curr["Hall"].insert("Green");
        curr["Hall"].insert("Peacock");
        curr["Hall"].insert("Plum");
        curr["Hall"].insert("Scarlett");
        curr["Hall"].insert("Mustard");
        int pt = 0;
        for (int i = 1; i <= murderTime; i++) {
            if (i == murderTime) {
                if (curr[murderRoom].size() == 1) {
                    return *curr[murderRoom].begin();
                }
                else return "";
            }
            else {
                if (pt < eventTime.size() && i == eventTime[pt]) {
                    string person = eventPerson[pt];
                    //cout << eventPerson[pt] << ' ' << eventRoom[pt] << '\n';
                    curr[currRoom[person]].erase(person);
                    currRoom[person] = eventRoom[pt];
                    curr[currRoom[person]].insert(person);
                    pt++;
                }
            }
            /*
            cout << i << ":\n";
            for (auto p: curr) {
                cout << p.first << "\n";
                for (auto q: p.second) {
                    cout << q << ' ';
                }
                cout << '\n';
            }
            */
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Alibi t;
    string murderRoom = "Library";
    int murderTime = 10;
    vector<int> eventTime = {3,7};
    vector<string> eventPerson = {"Plum","Plum"};
    vector<string> eventRoom = {"Library","Library"};
    cout << t.findMurderer(murderRoom,murderTime,eventTime,eventPerson,eventRoom) << '\n';
}

