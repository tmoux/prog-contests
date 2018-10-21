#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, m;
const int INF = 2000000;
struct Exam
{
    int canStart;
    int daysLeft;
    int examDate;
} exams[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int si, di, ci;
        cin >> si >> di >> ci;
        exams[i] = {si,ci,di};
    }
    
    vector<int> ans;
    bool pos = true;
    for (int day = 1; day <= n && pos; day++) {
        //look for if there's a test
        int minDate = INF;
        int whichtest;
        bool isTestDay = false;
        for (int i = 0; i < n; i++) {
            Exam& e = exams[i];
            if (day == e.examDate) {
               if (e.daysLeft == 0) {
                   ans.push_back(m+1);
               }    
               else {
                   pos = false;
               }
               isTestDay = true;
               break;
            }
            else {
                //find exam with earliest examDate that has > 0 daysLeft and canStart <= day
                if (e.examDate < minDate && e.daysLeft > 0 && e.canStart <= day) {
                    minDate = e.examDate;
                    whichtest = i+1;
                }
            }
        }
        if (!isTestDay) {
            if (minDate == INF) {
                ans.push_back(0);
            }
            else {
                ans.push_back(whichtest);
                exams[whichtest-1].daysLeft--;
            }
       }
    }

    if (!pos) {
        cout << -1 << '\n';
    }
    else {
        for (int i: ans) {
            cout << i << ' ';
        }
    }
    return 0;
}
	

