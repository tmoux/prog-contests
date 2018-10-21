#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int maxn = 100005;
int arr[maxn];
 
int cmpfunc(const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

int main()
{
	freopen("input.in","r",stdin);
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&arr[i]);
	}
	qsort(arr,n,sizeof(int),cmpfunc);
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
 	
 	
 	
 	return 0;
}