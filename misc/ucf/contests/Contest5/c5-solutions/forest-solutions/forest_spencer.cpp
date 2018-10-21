#include <bits/stdc++.h>
using namespace std;

double turn(pair<double, double> a, pair<double, double> b, pair<double, double> c){
	return (c.first-b.first)*(b.second-a.second) - (b.first-a.first)*(c.second-b.second);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	vector<pair<double, double> > xx;
	int n;
	double k;
	cin >> n >> k;
	double pii = atan(1)*4.0;
	for(int i = 0; i<n; i++){
		double x, y;
		cin >> x >> y;
		xx.push_back(make_pair(x,y));
	} 
	vector<pair<double,pair<double, double> > > li;
	sort(xx.begin(),xx.end());
	for(int i = 1; i<xx.size(); i++){
		double ang = atan2(xx[i].first-xx[0].first,xx[i].second-xx[0].second);
		li.push_back(make_pair(ang,make_pair(xx[i].first,xx[i].second)));
	}
	sort(li.begin(),li.end());
	vector<pair<int, int> > hull;
	hull.push_back(xx[0]);
	for(int i = 0; i<n-1; i++){
		pair<double, double> cur = li[i].second;
		while(hull.size()>=2 && turn(hull[hull.size()-2],hull[hull.size()-1],cur)<0){
			hull.pop_back();
		}
		hull.push_back(cur);
	}

	while(hull.size()>3 && turn(hull[hull.size()-2],hull[hull.size()-1],hull[0])<0){
		hull.pop_back();
	}
	double cir = 0.0;
	double area = 0.0;
	for(int i = 0; i<hull.size(); i++){
		int nxt = (i+1)%hull.size();
		area += (hull[i].first+hull[nxt].first)*(hull[i].second-hull[nxt].second)/2.0;
		cir += sqrt((hull[i].first-hull[nxt].first)*(hull[i].first-hull[nxt].first)+(hull[i].second-hull[nxt].second)*(hull[i].second-hull[nxt].second));
	}
	if(area<0){
		area = -area;
	}
	area += cir*k;
	area += pii*k*k;
	cir += 2.0*pii*k;
	cout << fixed << setprecision(2) << cir << " " << area << endl;
}