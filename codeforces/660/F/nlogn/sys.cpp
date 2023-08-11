#include <bits/stdc++.h>
#define double double_t

using namespace std;

const int N = 1<<18;

int n;
long long a[N],s1[N],s2[N];
long long ans;
vector < pair < long long, long long > > v;

double get_x(double a1, double b1, double a2, double b2) {
	return (b2-b1)/(a1-a2);
}

double get_x(pair < long long, long long > a, pair < long long, long long > b) {
	return get_x(a.first,a.second,b.first,b.second);
}

long long evaluate(pair < long long, long long > a, long long x) {
	return (long long)(a.first*x+a.second);
}

void add_line(pair < long long, long long > a) {
	while(v.size()>=2 && get_x(a,v[v.size()-2])>get_x(v[v.size()-1],v[v.size()-2])) v.pop_back();
	v.push_back(a);
}

long long get_max(long long x) {
	int i,left,right,middle;
	if(v.size()==1) return evaluate(v[0],x);
	if(x<get_x(v[v.size()-1],v[v.size()-2])) return evaluate(v[v.size()-1],x);
	left=(-1);
	right=v.size()-2;
	while(right-left>1) {
		middle=(left+right)>>1;
		if(x>=get_x(v[middle],v[middle+1])) right=middle;
		else left=middle;
	}
	return evaluate(v[right],x);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int i;
	
	cin>>n;
	for(i=1;i<=n;i++) {
		cin>>a[i];
		s1[i]=a[i]+s1[i-1];
		s2[i]=a[i]*i+s2[i-1];
		ans=max(ans,s2[i]);
	}
	for(i=1;i<=n;i++) {
		add_line(make_pair(1ll-i,s1[i-1]*(i-1)-s2[i-1]));
		ans=max(ans,s2[i]+get_max(s1[i]));
	}
	cout<<ans<<endl;
	
	//fprintf(stderr, "Time: %d ms\n", (int)(clock()*1000.0/CLOCKS_PER_SEC));
	
	return 0;
}
